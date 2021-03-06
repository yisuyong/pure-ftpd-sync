#include <config.h>
#include <stdio.h>
#include <stdlib.h>

#include <errno.h> 
#include <string.h> 
#include <netdb.h> 
#include <sys/types.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <unistd.h>

#include <arpa/inet.h>

#include <sys/mman.h>

#include "ftpd.h"

#include "node_list.h"


void init_list(synclist* lptr){
	//initialize the list
	lptr->count=0;
	lptr->head=NULL;
}

void init_syncnode(syncnode *node)
{
	node->value=-1;
	node->ip=NULL;
	node->dip=NULL;
	node->port=21;
	node->dport=-1;
	node->passive=1;
	node->nat=0;

	node->isEnable=1;
	node->sockfd=-1;
	node->n_datafd=-1;
	node->readMesg[0]='\0';
	node->lastCode=0;
        bzero((char*)&node->node_addr,sizeof(node->node_addr));
        bzero((char*)&node->node_data_addr,sizeof(node->node_data_addr));

	node->ip=NULL;
	node->dip=NULL;

}


void insertNode(synclist *lptr,int position,unsigned char *ip,unsigned char *port){
	syncnode *new_nptr;

	if(position<1 || position>(lptr->count)+1){
		die(421, LOG_ERR, "Nodes position OOB");
	}
	new_nptr=(syncnode*)malloc(sizeof(syncnode));

	if(new_nptr == NULL)
	{
		die(421, LOG_ERR, "Can't malloc for node");
	}
	init_syncnode(new_nptr);

	new_nptr->ip = (char *)malloc(strlen(ip)+1);
	if(new_nptr->ip == NULL)
	{
		die(421, LOG_ERR, "Can't malloc for node ip");
	}

	memset(new_nptr->ip,0x00,strlen(ip)+1);

	strncpy(new_nptr->ip,ip,strlen(ip));
	new_nptr->port = atoi(port);

	init_node_socket(new_nptr,1);

	connect_node(new_nptr,2,0,1);

	new_nptr->value=position;


	if(position==1){
		new_nptr->next=lptr->head;
		lptr->head=new_nptr;
	}
	else{
		syncnode *tmp=lptr->head;
		int i;
		for(i=1;i<position-1;i++){
			tmp=tmp->next;
		}
		new_nptr->next=tmp->next;
		tmp->next=new_nptr;
	}
	lptr->count++;
}


int check_all_node_code(synclist *lptr,int isRun,unsigned int code)
{
	int i=1;
	int x=1;

	syncnode *snode=lptr->head;

	if(!isRun) return 0;

	while(snode!=NULL)
	{
		if(snode->isEnable)
		{
			if(code == snode->lastCode)
			{
				i++;
			}
			x++;
		}
		snode=snode->next;
	}
	if(i == x){
		return 0;
	}
	else{
		return x-i;
	}
}


void disableSynclist(synclist *lptr,char *ip)
{
	syncnode *snode=lptr->head;

	while(snode!=NULL){

		if(!strcmp(snode->ip,ip))
		{
			snode->isEnable=0;
                	logfile(LOG_DEBUG,"My IP : %s:%d disabled" ,snode->ip,snode->port);
		}
		snode=snode->next;
	}
}



void print_Synclist(synclist *lptr)
{
	syncnode *snode=lptr->head;


	while(snode!=NULL){
//                logfile(LOG_DEBUG,"IP : %s - %s Passvie : %d Port : %d - %d",snode->ip,inet_ntoa(snode->node_addr.sin_addr),snode->passive,snode->port,htons(snode->node_addr.sin_port));
                logfile(LOG_DEBUG,"IP : %s Passvie : %d Port : %d",snode->ip,snode->passive,snode->port);
		snode=snode->next;
	}
	logfile(LOG_DEBUG,"Total: %d Server(s)",lptr->count);
}

void node_free(synclist *lptr){
	syncnode *snode=lptr->head;
	syncnode *snode_next;

	while(snode!=NULL){
		if(snode->ip!=NULL) free(snode->ip);
		if(snode->dip!=NULL) free(snode->dip);

		close(snode->sockfd);	
		close(snode->n_datafd);	

		snode_next=snode->next;
		free(snode);
		snode=snode_next;
	}

	if(lptr != NULL) free(lptr);
}



int init_node_socket(syncnode *snode,int type)
{
        int sockopt=1;
        struct hostent *he=NULL;

        char *ip;
        int  sockfd;
        int  port;
        struct sockaddr_in *addr;
        char buf[5];

        if(type==1) //1=command socket
        {
                ip=snode->ip;
                port=snode->port;
                bzero((char*)&snode->node_addr,sizeof(snode->node_addr));
                addr=(struct sockaddr *)&snode->node_addr;
                sprintf(buf,"CMD");
        }
        else //passive data socket
        {
                ip=snode->dip;
                port=snode->dport;
                bzero((char*)&snode->node_data_addr,sizeof(snode->node_data_addr));
                addr=(struct sockaddr *)&snode->node_data_addr;
                sprintf(buf,"DATA");
        }

        if((he=gethostbyname(ip))==NULL)
        {
                die(421, LOG_ERR,"%s: %s Port %d Address error.",buf,ip,port);
        }
        if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)
        {
                die(421,"%s: %s Port %d socket error",buf,ip,port);
        }

        if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR,(char*) &sockopt, sizeof(sockopt)) == -1)
        {
                die(421,"%s: %s Port %d, Socket option : REUSEADDR",buf,ip,port);
        }

        addr->sin_family=AF_INET;
        addr->sin_port=htons(port);

        memcpy(&addr->sin_addr,&(*((struct in_addr *)he->h_addr)),sizeof(he->h_addr));


        if(type) //1=command socket
        {
                snode->sockfd=sockfd;
        }
        else
        {
                snode->n_datafd=sockfd;
        }

        return 0;
}


int connect_node(syncnode *snode,int timeout,int block,int type)
{
        //소켓 헬스 체크후 reconnect 기능 구현해야함
        // 컨피그에서 읽어야할 변수 (임시)
        int keep=1;
        int fodder=1;

        int  sockfd;
        char *ip;
        int  *port;
        struct sockaddr_in *addr;
        fd_set *rset,*wset;
        char buf[5];

        if(type) //1=command socket
        {
                ip=snode->ip;
                port=&snode->port;
                addr=(struct sockaddr *)&snode->node_addr;
                sockfd=snode->sockfd;
                rset=&snode->rset;
                wset=&snode->wset;
                sprintf(buf,"CMD");
        }
        else //data socket
        {
                ip=snode->dip;
                port=&snode->dport;
                addr=(struct sockaddr *)&snode->node_data_addr;
                sockfd=snode->n_datafd;
                rset=&snode->drset;
                wset=&snode->dwset;
                sprintf(buf,"DATA");
        }

        if(connect_nonb(sockfd,addr,sizeof(struct sockaddr),rset,wset,timeout,block) == -1)
        {
                if(type) //1=command socket
                {
                        snode->isEnable=0;
                }
                logfile(LOG_ERR,"%s: %s Port %d. Connect fail.This server check plz %s",buf,ip,*port,strerror(errno));
                return -1;
        }
        else
        {
                setsockopt(sockfd, SOL_SOCKET, SO_KEEPALIVE, (char *) &keep, sizeof keep);
                #ifdef IPTOS_LOWDELAY
                fodder = IPTOS_LOWDELAY;
                setsockopt(sockfd, SOL_IP, IP_TOS, (char *) &fodder, sizeof fodder);
                #endif
                #ifdef SO_OOBINLINE
                fodder = 1;
                setsockopt(sockfd, SOL_SOCKET, SO_OOBINLINE,(char *) &fodder, sizeof fodder);
                #endif
                #ifdef TCP_NODELAY
                fodder = 1;
                setsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY,(char *) &fodder, sizeof fodder);
                #endif
                logfile(LOG_DEBUG,"%s: %s Port %d. Connect node. OK!!",buf,ip,*port);
        }

        if(type) //1=command socket
        {
                snode->isEnable=1;
        }

        return 0;
}

int connect_nonb(int sockfd,const struct sockaddr *saptr, int salen,fd_set *rset,fd_set *wset, int nsec,int block)
{
    int             flags, n, error;
    socklen_t       len;
    struct timeval  tval;

    flags = fcntl(sockfd, F_GETFL, 0);
    if(fcntl(sockfd, F_SETFL, flags | O_NONBLOCK)==-1)
    {
           logfile(LOG_ERR,"connect soket non-block error : %s",strerror(errno));
            return -1;
    }

    error = 0;
    if ( (n = connect(sockfd, (struct sockaddr *) saptr, salen)) < 0)
    {
        if (errno != EINPROGRESS)
        {
           logfile(LOG_ERR,"connect soket error : %s",strerror(errno));
            return -1;
        }
    }
    /* Do whatever we want while the connect is taking place. */

    if (n == 0)
        goto done;  /* connect completed immediately */

    FD_ZERO(rset);
    FD_SET(sockfd, rset);
    wset = rset;
    tval.tv_sec = nsec;
    tval.tv_usec = 0;

    if ( (n = select(sockfd+1, rset, wset, NULL,
                     nsec ? &tval : NULL)) == 0) {
        close(sockfd);      /* timeout */
        errno = ETIMEDOUT;
        logfile(LOG_ERR,"connect timeout error : %s",strerror(errno));
        return(-1);
    }

    if (FD_ISSET(sockfd, rset) || FD_ISSET(sockfd, wset)) {
        len = sizeof(error);
        if (getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &error, &len) < 0)
        {
                logfile(LOG_ERR,"get connect socket opt error : %s",strerror(errno));
                return(-1);         /* Solaris pending error */
        }
    } 
    else
    {
        die(421, LOG_ERR,"select error: sockfd not set");
    }

done:

        if(block)
        {
                fcntl(sockfd, F_SETFL, flags);  /* restore file status flags */
        }

        if (error)
        {
                close(sockfd);      /* just in case */
                errno = error;
                return(-1);
        }
        return(0);
}


int node_write_message(synclist *lptr,int isRun,char *cmd,char *arg,syncnode *jnode)
{
	if(!isRun) return 9999;


        int cmd_len=strlen(cmd);
        int arg_len=strlen(arg);
        int i=0;

        char up_cmd[cmd_len+1];
        char sendMesg[cmd_len + arg_len + 4];


        for(i=0; i < cmd_len; i++)
        {
                up_cmd[i] = (char)toupper( cmd[i]);
        }
        up_cmd[i]='\0';

        snprintf(sendMesg,cmd_len+arg_len + 4,"%s %s\r\n",up_cmd,arg);

        if((jnode!=NULL) && (jnode->isEnable))
        {
                int bytes=0;
                int flags;

                flags=fcntl(jnode->sockfd, F_GETFL, 0);
                fcntl(jnode->sockfd, F_SETFL, (flags & (~O_NONBLOCK)));

                bytes=write(jnode->sockfd,sendMesg,sizeof(sendMesg)-1);
                logfile(LOG_DEBUG,"Node : %s Port %d. sendBytes : %d Message : %s",jnode->ip,jnode->port,bytes,sendMesg);

                fcntl(jnode->sockfd, F_SETFL,flags);
                return 0;
        }
        else
        {
		syncnode *snode=lptr->head;
	
                while(snode!=NULL)
                {
                        int bytes=0;
                        int flags;

                        if(snode->isEnable)
                        {

                                flags=fcntl(snode->sockfd, F_GETFL, 0);
                                fcntl(snode->sockfd, F_SETFL, (flags & (~O_NONBLOCK)));

                                bytes=write(snode->sockfd,sendMesg,sizeof(sendMesg)-1);
                                logfile(LOG_DEBUG,"Node : %s Port %d. sendBytes : %d Message : %s",snode->ip,snode->port,bytes,sendMesg);

                                fcntl(snode->sockfd, F_SETFL,flags);
                        }
                        snode=snode->next;
                }
        }
	return 0;

}



int read_from_client(int fds,fd_set *rset,char *str,int maxlen)
{

   int n;
   char c;

   int  offset=0;
   int  nBytes=0;

   bzero(str,MAXDATASIZE);



   //for (n = 1; n < maxlen; n++)
   while(1)
   {
      nBytes = read(fds, &c, 1);
      if(nBytes == -1)
      {
         if(errno == EINTR || errno == EAGAIN)
         {
                continue;
         }
         else if(errno == ECONNRESET ) /* TCP CONN RESET */
         {
            logfile(LOG_ERR,"[sds = %d] peer connect reset",fds);
            close(fds);
            FD_CLR(fds, rset);
            return -1;
         }
         else
         {
            logfile(LOG_ERR,"[sds = %d] read error",fds);
            close(fds);
            FD_CLR(fds, rset);
            return -1;
         }
      }
      else if(nBytes == 0)
      {
          if(n==1)
          {
                return 0;
          }
          else
          {
                break;
          }
      }
      else //nBytes=1
      {
                *str = c;      /* copy character to buffer */
                str++;         /* increment buffer index */
                if (c == '\n') /* is it a newline character? */
                break;      /* then exit for loop */
      }
   }
   *str=0;
   return n;
}

unsigned int check_code_message(char *message)
{
        char code[6];
        char str_num[6];
        int codenum;
        int i=0;
        int flag=0;

        strncpy(code,message,6);

        bzero(str_num,sizeof(str_num));

        for(i=0;i<sizeof(code);i++)
        {
                if(code[i]==0x20) //space
                {
                        str_num[i]=0x00;
                        codenum=atoi(str_num);
                        flag=1;
                        break;
                }
                str_num[i]=code[i];
        }

        if(flag)
        {
                // https://en.wikipedia.org/wiki/List_of_FTP_server_return_codes
                if(codenum >= 100 && codenum <= 10068)
                {
                        return codenum;
                }
        }

        return 0;
}


int read_code_from_client(int fds,fd_set *rset,char *str)
{
        int byte=0;
        unsigned int code=0;
        int flags;

        flags = fcntl(fds, F_GETFL, 0);
        fcntl(fds, F_SETFL, flags | O_NONBLOCK);

        do
        {
                byte=read_from_client(fds,rset,str,1);
                if(byte<0)
                {
                        return -1;
                }
                code=check_code_message(str);
        }while(!code);
        return code;
}

int node_read_message(synclist *lptr,int isRun,char *cmd,char *arg,int code,int action)
{
	if(!isRun) return 9999;

        syncnode *snode = lptr->head;
        int error_flag=0;


        while(snode!=NULL)
        {
                if(snode->isEnable)
                {
                                snode->lastCode=read_code_from_client(snode->sockfd,&snode->rset,snode->readMesg);
                                if(!code && (snode->lastCode != code))
                                {
                                        logfile(LOG_ERR,"Node Read error : %s ,Port %d. Message :%d  = %s",snode->ip,snode->port,snode->lastCode,snode->readMesg);
                                        if(action)
                                        {
                                                die(421, LOG_ERR,"COMMAND ERROR : %s ,Port %d. Message :%d  = %s",snode->ip,snode->port,snode->lastCode,snode->readMesg);
                                        }
                                        error_flag++;
                                }

                                if(snode->lastCode==421)
                                {
                                        die(421, LOG_ERR,"COMMAND ERROR : %s ,Port %d. Message :%d  = %s",snode->ip,snode->port,snode->lastCode,snode->readMesg);
                                }
                                logfile(LOG_DEBUG,"Node Read OK : %s ,Port %d. Message :%d  = %s",snode->ip,snode->port,snode->lastCode,snode->readMesg);
                }
                snode=snode->next;
        }
        return error_flag;
}

int init_node_data_sock(synclist *lptr)
{
        int timeout=2;
        syncnode *snode = lptr->head;

        while(snode!=NULL)
        {
          if(snode->isEnable)
          {
            if(snode->passive)
            {
              if(init_node_socket(snode,0)==0)
              {
                  connect_node(snode,timeout,1,0);
              }
              else
              {
                 logfile(LOG_ERR,"Node %s,passive data socket init errror",snode->ip);
                 return -1;
                 //에러처리
               }
            }
            else
            {
                   //active mode
            }
          }
          snode=snode->next;
         }

        return 0;
}


void onenode_read_message(syncnode *snode)
{
        snode->lastCode=read_code_from_client(snode->sockfd,&snode->rset,snode->readMesg);
        logfile(LOG_DEBUG,"Node : %s Port %d. Message :%d  = %s",snode->ip,snode->port,snode->lastCode,snode->readMesg);
}


int onenode_pasv_send(syncnode *snode)
{
        int i=0;
	
	synclist *lptr;

	
        node_write_message(lptr,1,"PASV","",snode);
        onenode_read_message(snode);

        if(snode->lastCode!=227)
        {
                logfile(LOG_ERR,"PASV mode error.(%s / %d)",snode->ip,snode->lastCode);
		return -1;
        }
        else
        {
                int b[6]={0,0,0,0,0,0};
                int len,i,x=0;
                char *port_str=snode->readMesg+4;
                len = strlen(port_str += 4);

                len=strlen(snode->readMesg);

                for (i = 0; i < len; i++)
                {
                        if(!isdigit(port_str[i])) port_str[i] = ' ';
                }
                if (sscanf(port_str, "%u %u %u %u %u %u",
                        b, b + 1, b + 2, b + 3, b + 4, b + 5) != 6)
                {
                        die(421, LOG_ERR,"PASV Port error.(%s / %d)",snode->ip,snode->lastCode);
                }
                snode->dport=(b[4] * 256) + b[5];
                if(snode->nat)
                {
                        snode->dip=(char *)malloc(strlen(snode->ip)+1);
                        memcpy(snode->dip,snode->ip,strlen(snode->ip)+1);
                }
                else
                {

                        char temp[16];
                        sprintf(temp,"%d.%d.%d.%d",b[0],b[1],b[2],b[3]);
                        snode->dip=(char *)malloc(strlen(temp)+1);
                        memcpy(snode->dip,temp,strlen(temp)+1);
                }
                //logfile(LOG_DEBUG,"node %s : Data IP / Port : %s %d(= %d * 256 + %d)",
                //              snode->ip,snode->dip,snode->dport,b[4],b[5]);
        }

        return 0;
}

int node_socket_close(int fd)
{
	return shutdown(fd,SHUT_RDWR);
}

void node_closedata(synclist *lptr,int isRun)
{
        syncnode *snode = lptr->head;
        int i=0;
	
	if(!isRun) return;

        while(snode!=NULL)
        {
                if(snode->isEnable)
                {
                        if(snode->passive)
                        {
				if(node_socket_close(snode->n_datafd)<0)
				{
                			logfile(LOG_ERR,"Data socket close error.(%s)",snode->ip);
				}
				else
				{
                			logfile(LOG_DEBUG,"Data socket closed.(%s)",snode->ip);
				}
                        }
                        else
                        {
                                // active mode
                                ;
                        }
                }
                snode=snode->next;
        }

}

void node_opendata(synclist *lptr,int isRun)
{
        syncnode *snode = lptr->head;
        int i=0;
	
	if(!isRun) return;

        while(snode!=NULL)
        {
                if(snode->isEnable)
                {
                        if(snode->passive)
                        {
                                if(onenode_pasv_send(snode) != 0)
                                {
                			die(421, LOG_ERR, "Can't passive port");
                                }
                        }
                        else
                        {
                                // active mode
                                ;
                        }
                }
                snode=snode->next;
        }
 	if(init_node_data_sock(lptr)<0)
        {
                die(421, LOG_ERR, "Can't Connect data port");
        }

}



int read_data_from_client(int fds,syncnode *snode,int timeout)
{
        int bufsize=4096;

        int byte=0;
        char str[bufsize];
        fd_set readset;
        struct timeval tv;
        int select_fd;
        int flags;
        int chk=0;

        tv.tv_sec=timeout;
        tv.tv_usec=0;



        flags = fcntl(fds, F_GETFL, 0);
        fcntl(fds, F_SETFL, flags | O_NONBLOCK);

        do{
                FD_ZERO(&readset);
                FD_SET(fds,&readset);

                select_fd=select(fds + 1,&readset,(fd_set *)0,(fd_set *)0,&tv);

                if(select_fd <0)
                {
                        logfile(LOG_ERR,"DATA : %s select error.",snode->ip);
                        return -1;
                }
                else if(select_fd==0)
                {
                        logfile(LOG_ERR,"DATA : %s read timeout.",snode->ip);
                        return -1;
                }

                while(1)
                {
                        memset(str,0x00,bufsize);
                        byte = read(fds, str, bufsize-1);

                        if(byte<0)
                        {
                                logfile(LOG_ERR,"DATA : %s read error.",snode->ip);
                                return -1;
                        }
                        else if(byte==0)
                        {
                                chk=1;
                                break;
                        }

                        logfile(LOG_DEBUG,"DATA : %s",str);

                }
                if(chk) break;

        }while(1);
//      logfile(LOG_DEBUG,"data %s end : last byte=%d X %d: end :%d, last-1 : %d, last %d\n",snode->ip,byte,i,end,str[byte-2],str[byte-1]);

        return 0;
}


int node_read_data(synclist *lptr,int isRun,int action)
{                   
        syncnode *snode = lptr->head;
        int error_flag=0;

	if(!isRun) return 0;
                    
        while(snode!=NULL)
        {           
                if(snode->isEnable)
                {
                        if(read_data_from_client(snode->n_datafd,snode,2)<0)
                        {
                                if(action)
                                {
                                        die(421, LOG_ERR,"Sync Command error LIST. (%s / %d)",snode->ip,snode->lastCode);
                                }
                                error_flag++;
                        }
                        if(node_socket_close(snode->n_datafd)<0)
                        {
                                logfile(LOG_ERR,"Data socket close error.(%s)",snode->ip);
                        }
                        else
                        {
                                logfile(LOG_DEBUG,"Data socket closed.(%s)",snode->ip);
                        }
               }
               snode=snode->next;
        }           
        return error_flag;
}


int node_data_write(synclist *lptr,int isRun,unsigned char *buf,off_t chunk_size)
{
   syncnode *snode = lptr->head;

   if(!isRun) return 0;
   while(snode!=NULL)
   {
       if(snode->isEnable)
       {
           int bytes=0;
           int count=3;

           for(count;count>0;count--)
           {
                if(bytes=write(snode->n_datafd,buf,chunk_size)<0)
                {
                        logfile(LOG_ERR,"DATA write retry(%d)",count);
                        continue;
                }
                else
                {
                        break;
                }
           }

           if(count<0)
           {      
                  die(421, LOG_ERR,"Data write error. Connection closed.(%s)",snode->ip);
           }
       }
       snode=snode->next;
  }
  return 0;
}


int node_dir_chk(synclist *lptr,int isRun,char *cur_dir)
{                   
        syncnode *snode = lptr->head;
        int error_flag=0;

	if(!isRun) return 0;
                    
        while(snode!=NULL)
        {
                if(snode->isEnable)
                {
                        char dir_temp[1024];
                        int count=0,chk=0;
                        bzero(dir_temp,sizeof(dir_temp));

                        for(int i=0;i<strlen(snode->readMesg);i++)
                        {
                                if((snode->readMesg[i]=='"') && chk)
                                {
                                        dir_temp[count]='\0';
                                        break;

                                }
                                if(chk)
                                {
                                        dir_temp[count]=snode->readMesg[i];
                                        count++;
                                }
                                if((snode->readMesg[i]=='"') && !(chk))
                                {
                                        chk=1;
                                }
                        }
                        if(strncmp(cur_dir,dir_temp,strlen(dir_temp))!=0)
                        {
                                logfile(LOG_ERR,"Node %s,current dir different!!(M:%s,N:%s) \n",snode->ip,cur_dir,dir_temp);
                                error_flag++;

                        }
                }
                snode=snode->next;
        }
        return error_flag;
}

int node_cwd_chk(synclist *lptr,int isRun,char *cddir,int reqcode)
{
        int error_flag=0;
                
        if(check_all_node_code(lptr,isRun,reqcode)!=0)
        {       
                logfile(LOG_ERR,"Nodes Change directory directory fail");
                node_write_message(lptr,isRun,"CWD",cddir,NULL);
                node_read_message(lptr,isRun,"CWD",cddir,250,1);
                return -1;
        }       
                        
        return error_flag;
}
                
int node_mkdir_chk(synclist *lptr,int isRun,char *make_dir,int reqcode)
{               
        int error_flag=0;

	if(!isRun) return 0;
            
        if(check_all_node_code(lptr,isRun,reqcode)!=0)
        {   
                logfile(LOG_ERR,"Nodes Create directory fail");
                node_write_message(lptr,isRun,"RMD",make_dir,NULL);
                node_read_message(lptr,isRun,"RMD",make_dir,250,0);

                return -1;
        }

        return error_flag;
}
