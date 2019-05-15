#ifndef __NODE_LIST_H__
#define __NODE_LIST_H__ 1

#define MAXDATASIZE 1024

typedef struct _syncnode
{
        int value;
        char *ip,*dip;
        unsigned int port,dport;
        unsigned char passive;
        unsigned char nat;

        /* sock */
        int isEnable;
        int sockfd;
        int n_datafd;

        fd_set rset,drset;
        fd_set wset,dwset;

        char readMesg[MAXDATASIZE];
        unsigned int lastCode;

        struct sockaddr_in node_addr;
        struct sockaddr_in node_data_addr;

        struct _syncnode *next;
}syncnode;

typedef struct _synclist{
        int count;
        syncnode *head;
}synclist;

void init_list(synclist *lptr);
void init_syncnode(syncnode *node);
void insertNode(synclist *lptr,int position,unsigned char *ip,unsigned char *port);
int check_all_node_code(synclist *lptr,int isRun,unsigned int code);
void print_Synclist(synclist *lptr);
void node_free(synclist *lptr);
void disableSynclist(synclist *lptr,char *ip);

int init_node_socket(syncnode *snode,int type);
int connect_node(syncnode *snode,int timeout,int block,int type);
int connect_nonb(int sockfd,const struct sockaddr *saptr, int salen,fd_set *rset,fd_set *wset, int nsec,int block);


int node_write_message(synclist *lptr,int isRun,char *cmd,char *arg,syncnode *jnode);
int read_code_from_client(int fds,fd_set *rset,char *str);
int read_from_client(int fds,fd_set *rset,char *str,int maxlen);
unsigned int check_code_message(char *message);
int node_read_message(synclist *lptr,int isRun,char *cmd,char *arg,int code,int action);

void onenode_read_message(syncnode *snode);
int onenode_pasv_send(syncnode *snode);
void node_opendata(synclist *lptr,int isRun);
void node_closedata(synclist *lptr,int isRun);

int init_node_data_sock(synclist *lptr);

int read_data_from_client(int fds,syncnode *snode,int timeout);
int node_read_data(synclist *lptr,int isRun,int action);
int node_socket_close(int fd);

int node_data_write(synclist *lptr,int isRun,unsigned char *buf,off_t chunk_size);
int node_dir_chk(synclist *lptr,int isRun,char *cur_dir);
int node_cwd_chk(synclist *lptr,int isRun,char *cddir,int reqcode);
int node_mkdir_chk(synclist *lptr,int isRun,char *cddir,int reqcode);






#endif
