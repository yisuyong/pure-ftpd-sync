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


int check_all_node_code(syncnode *snode,unsigned int code)
{
	int i=1;
	int x=1;
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


void print_Synclist(synclist *lptr){
	syncnode *snode=lptr->head;
	while(snode!=NULL){
//                logfile(LOG_DEBUG,"IP : %s - %s Passvie : %d Port : %d - %d \n",snode->ip,inet_ntoa(snode->node_addr.sin_addr),snode->passive,snode->port,htons(snode->node_addr.sin_port));
                logfile(LOG_DEBUG,"IP : %s Passvie : %d Port : %d\n",snode->ip,snode->passive,snode->port);
		snode=snode->next;
	}
	logfile(LOG_DEBUG,"Total: %d Server(s)\n",lptr->count);
}

void node_free(synclist *lptr){
	syncnode *snode=lptr->head;
	syncnode *snode_next=lptr->head;

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
                logfile(LOG_DEBUG,"%s: %s Port %d. Connect fail.This server check plz %s",buf,ip,*port,strerror(errno));
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
           logfile(LOG_DEBUG,"connect soket non-block error : %s",strerror(errno));
            return -1;
    }

    error = 0;
    if ( (n = connect(sockfd, (struct sockaddr *) saptr, salen)) < 0)
    {
        if (errno != EINPROGRESS)
        {
           logfile(LOG_DEBUG,"connect soket error : %s",strerror(errno));
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
        logfile(LOG_DEBUG,"connect timeout error : %s",strerror(errno));
        return(-1);
    }

    if (FD_ISSET(sockfd, rset) || FD_ISSET(sockfd, wset)) {
        len = sizeof(error);
        if (getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &error, &len) < 0)
        {
                logfile(LOG_DEBUG,"get connect socket opt error : %s",strerror(errno));
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
