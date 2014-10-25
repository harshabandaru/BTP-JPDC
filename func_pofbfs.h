#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "t_heap.h"
#include "p_heap.h"
#include "calc.h"
#include "func_gta.h"
void insertNode(FA* ,int ,int, ll_task*);
int NonEmptyFrame(FA* , int );
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
		//printf("%d %d %f \n",t->t_naf,t->t_shr ,t->t_wt);
		ll_task* nodealpha = createllTask(t);		//line 5
		insertNode(fa_ds,t->t_naf,t->t_shr,nodealpha);	//line 6

		while(1){
			int frameIndex = 0;
			int count = 0; 		//to maintain if all frames are empty
			int i;
			if(NonEmptyFrame(fa_ds,frameIndex)){
				ll_task* sortedlist_head = NULL;
				ll_task* temp=sortedlist_head;		//sorted list of tasks
				count = 0;		//reset count
				frame* curFrame = fa_ds->arrayFrames[frameIndex];
				for(i=0;i<G;i++){
					ll_task* t_node = curFrame -> arrayNodes[i];
					while(t_node!=NULL){
						if(temp==NULL){
							sortedlist_head = t_node;
							temp = sortedlist_head;
							t_node = t_node -> next;
						}
						else{
							temp->next = t_node;
							t_node = t_node->next;
							temp = temp->next;
						}
					}
				}
				temp->next = NULL;  //put the next pointer of last node to NULL
				GlobalTaskAllocator(sortedlist_head,m);
			}
			else{
				count ++;
			}
			frameIndex = (frameIndex+1)%FSZ;	//maintain circular array
			if(count == FSZ)
				break;
		}

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
