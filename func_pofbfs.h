#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "t_heap.h"
#include "p_heap.h"
#include "calc.h"
#include "func_gta.h"
void insertNode(FA* ,int ,int, ll_task*);
int NonEmptyFrame(FA* , int );

void printlist(ll_task* sortedlist_head){
	ll_task* temp = sortedlist_head;
	while(temp!=NULL){
		task* ti = temp->t;
		printf("in list:%d %d %d %f \n",ti->t_id,ti->t_naf,ti->t_shr ,ti->t_wt);
		temp = temp->next;
	}
}

void pofbfs(){
	FILE* fp;
	int n;		//no. of tasks
	int m;		//no. of processors
	int i;
	fp = fopen("input","r");
	fscanf(fp,"%d",&n);
	fscanf(fp,"%d",&m);
	
	FA* fa_ds = createFA();
	for(i=0;i<n;i++){			//for each active task Ti (Initialise FA)
		int ei,pi,rei,rpi;
		fscanf(fp,"%d",&ei);
		fscanf(fp,"%d",&pi);
		rei = ei;
		rpi = pi;
		task* t = createTask();
		t->t_e = ei;
		t->t_re = rei;
		t->t_p = pi;
		t->t_rp = rpi;
		t->t_naf = calc_naf(t);			//line 2-4
		t->t_shr = calc_shr(t);
		t->t_wt = calc_wt(t);
		t->t_count = t->t_shr;
		printf("%d %d %f \n",t->t_naf,t->t_shr ,t->t_wt);
		ll_task* nodealpha = createllTask(t);		//line 5
		insertNode(fa_ds,t->t_naf,t->t_shr,nodealpha);	//line 6
	}
    int frameIndex = 0;
    int count = 0; 		//to maintain if all frames are empty
	while(1){
		
		
		int i;
		printf("frameIndex:%d\n",frameIndex );
		if(NonEmptyFrame(fa_ds,frameIndex)){
			printf("insideif:%d\n",frameIndex );
			ll_task* sortedlist_head = NULL;
			ll_task* temp=sortedlist_head;		//sorted list of tasks
			count = 1;		//reset count
			frame* curFrame = fa_ds->arrayFrames[frameIndex];
			//printf("1\n");
			for(i=0;i<G;i++){
				ll_task* t_node = curFrame -> arrayNodes[i];
				//printf("2\n");
				while(t_node!=NULL){
					//printf("3\n");
					if(temp==NULL){
						//printf("4\n");
						sortedlist_head = t_node;
						temp = sortedlist_head;
						t_node = t_node -> next;
					}
					else{
						//printf("5\n");
						temp->next = t_node;
						t_node = t_node->next;
						temp = temp->next;
					}
				}
			}
			temp->next = NULL;  //put the next pointer of last node to NULL

			//clear the tasks in the frame after storing in sortedlist
			for(i=0;i<G;i++){
				curFrame->arrayNodes[i] = NULL;
			}

			printlist(sortedlist_head);
			GlobalTaskAllocator(sortedlist_head,m);
			//count++;
		}
		else{
			count ++;
			printf("count:%d\n",count );
		}
		//printf("3\n");
		frameIndex = (frameIndex+1)%FSZ;	//maintain circular array
		if(count == FSZ)
			break;
	}

	
}

void insertNode(FA* fa_ds,int naf,int shr,ll_task* nodealpha){
	frame* curFrame = fa_ds->arrayFrames[naf+1];
	ll_task* tempnode = curFrame -> arrayNodes[G-shr];
	if(tempnode==NULL){
		curFrame -> arrayNodes[G-shr] = nodealpha;
	}
	else{
		while(tempnode->next!=NULL){
			tempnode = tempnode->next;
		}
		tempnode->next = nodealpha;
	}
}
/*return 1 if frame is nonempty*/
int NonEmptyFrame(FA* fa_ds, int frameIndex){
	int i;
	int flag = 0;
	frame* curFrame = fa_ds->arrayFrames[frameIndex];
	for(i=0;i<G;i++){
		if(curFrame->arrayNodes[i]!=NULL){
			flag = 1;
			break;
		}
	}
	return flag;
}

void printFA(FA* fa_ds){
	int i,j;
	for(i=0;i<FSZ;i++){
		frame* curFrame = fa_ds->arrayFrames[i];
		for(j=0;j<G;j++){

			if(curFrame->arrayNodes[i]!=NULL){
				
			
			}
		}
	}
}