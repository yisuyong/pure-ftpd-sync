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
        int *isEnable;
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

typedef syncnode* snptr;

typedef struct _synclist{
        int count;
        snptr head;
}synclist;

void init_list(synclist *lptr);
void init_syncnode(snptr node);
void insertSynclist(synclist *lptr,snptr new_nptr,int position);
void deleteSynclist(synclist *lptr,int position);
int check_all_node_code(snptr snode,int code);
void modifySynclist(synclist *lptr,int value,int position);
void print_Synclist(synclist *lptr);
void node_free(synclist *lptr);

#endif
