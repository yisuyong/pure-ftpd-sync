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


#include "node_list.h"


void init_list(synclist* lptr){
	//initialize the list
	lptr->count=0;
	lptr->head=NULL;
}

void init_syncnode(snptr node)
{
	node->value=-1;
	node->ip=NULL;
	node->dip=NULL;
	node->port=21;
	node->dport=-1;
	node->passive=1;
	node->nat=0;

	node->sockfd=-1;
	node->n_datafd=-1;
	node->readMesg[0]='\0';
	node->lastCode=0;
        bzero((char*)&node->node_addr,sizeof(node->node_addr));
        bzero((char*)&node->node_data_addr,sizeof(node->node_data_addr));

	node->isEnable = mmap(NULL, sizeof *node->isEnable, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*(node->isEnable)=1;

}


void insertSynclist(synclist *lptr,snptr new_nptr,int position){
	//insert value to proper position
	if(position<1 || position>(lptr->count)+1){
		printf("Position Out of Bound\n");
		return;
	}
//	snptr new_nptr=(syncnode*)malloc(sizeof(syncnode));
	new_nptr->value=position;

	if(position==1){
		new_nptr->next=lptr->head;
		lptr->head=new_nptr;
	}
	else{
		snptr tmp=lptr->head;
		int i;
		for(i=1;i<position-1;i++){
			tmp=tmp->next;
		}
		new_nptr->next=tmp->next;
		tmp->next=new_nptr;
	}
	lptr->count++;
}

void deleteSynclist(synclist *lptr,int position){
	//delete an item on the position
	if(position<1 || position>(lptr->count)){
		printf("Position Out of Bound\n");
		return;
	}
	snptr tmp=lptr->head;

	if(position==1){
		lptr->head=tmp->next;
		free(tmp);
	}
	else{
		int i;
		for(i=1;i<position-1;i++){
			tmp=tmp->next;
		}
		snptr tmp2=tmp->next;
		tmp->next=tmp2->next;
		free(tmp2);
	}
	lptr->count--;
}

int check_all_node_code(snptr snode,int code)
{
	int i=1;
	int x=1;
	while(snode!=NULL)
	{
		if(*(snode->isEnable))
		{
			if(code==snode->lastCode)
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

void modifySynclist(synclist *lptr,int value,int position){
	if(position<1 || position>(lptr->count)){
		printf("Position Out of Bound\n");
		return;
	}
	snptr tmp=lptr->head;

	int i;
	for(i=1;i<position;i++){
		tmp=tmp->next;
	}
	tmp->value=value;
}

void print_Synclist(synclist *lptr){
	snptr snode=lptr->head;
	while(snode!=NULL){
                printf("IP : %s - %s Passvie : %d Port : %d - %d \n",snode->ip,inet_ntoa(snode->node_addr.sin_addr),snode->passive,snode->port,htons(snode->node_addr.sin_port));
		snode=snode->next;
	}
	printf("Total: %d value(s)\n",lptr->count);
}

void node_free(synclist *lptr){
	snptr snode=lptr->head;
	snptr snode_next=lptr->head;

	while(snode!=NULL){
		if(snode->ip!=NULL) free(snode->ip);
		if(snode->dip!=NULL) free(snode->dip);
		munmap(snode->isEnable, sizeof *snode->isEnable);

		close(snode->sockfd);	
		close(snode->n_datafd);	

		snode_next=snode->next;
		free(snode);
		snode=snode_next;
	}
}
