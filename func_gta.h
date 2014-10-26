#pragma once
#include "p_heap.h"
#include "t_heap.h"

void printmigrlist(ll_task* migrlist_head){
	ll_task* temp = migrlist_head;
	while(temp!=NULL){
		task* ti = temp->t;
		printf("in migr list:%d %d %d %f \n",ti->t_id,ti->t_naf,ti->t_shr ,ti->t_wt);
		temp = temp->next;
	}
}

void GlobalTaskAllocator(ll_task* sortedlist_head,int m){
	printf("----------------------In GTA function ----------------\n");
	int i;	
	int tshr;
	task* taski;
	proc* max_sc_p;
	//create a heap for maintaining processor spare capacities at all time 
	p_heap* p_sc_h = p_createHeap(m); 	
	for(i=0;i<m;i++){		
		proc* p = createProc();
		p_insert(p_sc_h,p);
	}

	ll_task* migrlist_head =NULL;//= (ll_task*)malloc(sizeof(ll_task)); //list of migrating tasks
	//migrlist_head->next = NULL;	
	ll_task* tempmigr=NULL;
	//printf("11\n");
	//---------------------------------------------------------------------
	//allocate fixed tasks starting with the heaviest task
	ll_task* templlTask = sortedlist_head;
	printf("---------------allocation of fixed tasks------------\n");
	while(templlTask!=NULL){
		taski = templlTask->t;
		max_sc_p = p_deleteMin(p_sc_h);

		//insert into migrating task list if proc cannot hold the task
		printf("Spare capacity of max proc with proc id %d:%d\n",max_sc_p->p_id, max_sc_p->p_sc);
		if(taski->t_shr > max_sc_p->p_sc){	
			printf("task %d is migrating task\n",taski->t_id );
			if(migrlist_head==NULL){	
				migrlist_head = createllTask(taski);	
				tempmigr = migrlist_head;
			}         
			else{
				//insert at the end of the migrating list
				tempmigr = migrlist_head;
				while(tempmigr->next != NULL){
					tempmigr = tempmigr->next;
				}
				tempmigr->next = createllTask(taski);
			}
		p_insert(p_sc_h,max_sc_p);
		} 

		else{
			//create readyheap if not created
			printf("task %d is fixed task with shr :%d\n",taski->t_id,taski->t_shr );
			if(max_sc_p->p_RH == NULL){ 
				max_sc_p->p_RH = t_createHeap(10);
			}
			//printf("1\n");
			taski->t_pd = tshr;		//for now initialising pd to share of task
			t_insert(max_sc_p->p_RH,taski);	//insert into readyheap of processor
			//printf("2\n");
			max_sc_p->p_sc = max_sc_p->p_sc - taski->t_shr;

			//insert processor back into its place
			if(max_sc_p->p_sc > 0)
				p_insert(p_sc_h,max_sc_p);	
			//printf("3\n"); 
		}

		templlTask=templlTask->next;
	}

	p_printheap(p_sc_h);
	printf("---------End of allocation of fixed tasks--------------\n");

	//---------debugging info

	//printf("%d\n", );
	for(i=0;i<p_sc_h->p_h_count;i++){	
		printf("Processor id:%d\n", p_sc_h->p_h_array[i]->p_id);	
		if(p_sc_h->p_h_array[i]->p_RH!=NULL)
			t_printheap(p_sc_h->p_h_array[i]->p_RH);
	}

	//----------debugging info

	//end of allocation of fixed tasks
//--------------------------------------------------------------------------------
	//Now allocate for migrating tasks
	tempmigr = migrlist_head;
	while(tempmigr!=NULL){
		taski = tempmigr->t;
		tshr = taski->t_shr;
		ll_p* temp_TP;
		//if tshr > 0 and there are more processors in the heap of processors P
		jump_stmt:
		if(tshr > 0 && p_sc_h->p_h_count > 0){
			//Extract the next processor with highest sc from list P
			max_sc_p = p_deleteMin(p_sc_h);
			temp_TP = taski->t_TP;
			if(temp_TP==NULL){
				taski->t_TP = createllProc(max_sc_p) ;
			}
			else{
				while(temp_TP->next != NULL){
					temp_TP = temp_TP -> next;
				}
				temp_TP->next = createllProc(max_sc_p);
			}

			//calculate wt_me and wt_mpe for all fixed tasks
			t_heap* t_rh = max_sc_p->p_RH;
			task** t_array = t_rh -> t_h_array;
			task* t_fixed;
			for(i=0; i < t_rh->t_h_count; i++){
				t_fixed = t_array[i];
				if(t_fixed->t_TP == NULL){ //t_temp is a fixed task
					calc_wt_me(max_sc_p,t_fixed,taski);
					calc_wt_mpe(max_sc_p,t_fixed);
				}

			}

			/*Set migr flag of V pc k to indicate that the
migrating task T j will execute in V pc k from the start of
the next frame. and update wts of fixed tasks*/
			
			if(taski->t_TP->next == NULL){//if(|TPj|=1) ie.only 1 processor in the list
				max_sc_p->p_migr = 1;
			}

			for(i=0; i < t_rh->t_h_count; i++){
				t_fixed = t_array[i];
				if(t_fixed->t_TP == NULL){ //t_temp is a fixed task
					t_fixed->t_wt = t_fixed->t_wt_me[max_sc_p->p_id];
				}

			}
			//Insert T j in the ready heap RH pc k
			t_insert(max_sc_p->p_RH,taski);

		}

		/*
		if tshr > sc k then
		tshr ← tshr − sc k ; sc k ← 0; Goto Step 10.
		*/	
		if(tshr > max_sc_p->p_sc){
			tshr = tshr - (max_sc_p->p_sc);
			max_sc_p->p_sc = 0;
			goto jump_stmt;
		}
		//sc k ← sc k − tshr; tshr ← 0.
		else{
			max_sc_p->p_sc = max_sc_p->p_sc - tshr;
			//Delete the first processor from list TP j
			taski->t_TP = taski->t_TP->next;
		}
		p_insert(p_sc_h,max_sc_p);
		tempmigr=tempmigr->next;
	}

	
	


}
