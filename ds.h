#pragma once
#include <stdlib.h>

#define G 12
#define FSZ 50
int p_id_counter = -1;
int t_id_counter = -1;
struct procNode {
	int p_id;
	int p_sc;					//spare capacity
	int p_migr;
	int p_prev_migr;
	struct t_h* p_RH;				//RHi->ready heap pointer
};
typedef struct procNode proc;

struct llNode{						//linked list
	proc* p;				//processor node
	struct llNode * next;
};
typedef struct llNode ll_p;

struct taskNode {
	int t_id;
	int t_e;
	int t_p;
	int t_re;
	int t_rp;
	int t_start;
	float t_wt;
	int t_shr;
	int t_naf;
	int t_wt_me[50];
	int t_wt_mpe[50];
	int t_count;
	int t_pd;
	ll_p* t_TP;			//TPj->linked list of processors
};
typedef struct taskNode task;



struct t_h {
	task** t_h_array;		//array of task pointers			
	int t_h_count;				//number of elements in heap
	int t_h_capacity;			//size of heap
};
typedef struct t_h t_heap;		//minheap of taskpointers


struct p_h {
	proc** p_h_array;		//array of processor pointers
	int p_h_count;				//number of elements in heap
	int p_h_capacity;			//size of heap
};
typedef struct p_h p_heap;		//minheap of procpointers


//Main DataStructure FA

struct ll_TaskNode {		//Linked list of tasks
	task* t;
	struct ll_TaskNode * next;
};
typedef struct ll_TaskNode ll_task;

struct frameList {
	ll_task* arrayNodes[G];
};
typedef struct frameList frame;

struct FA_ds{
	frame* arrayFrames[FSZ]; //need to define FSZ
};
typedef struct FA_ds FA;

//end of declaration of structs


task* createTask(){
	task* newTask = (task*)malloc(sizeof(task));
	newTask->t_id = ++t_id_counter;
	newTask->t_start = 0;
	newTask->t_TP = NULL;
	return newTask;
}

proc* createProc(){
	proc* newProc = (proc*)malloc(sizeof(proc));
	newProc->p_id = ++p_id_counter;
	newProc->p_sc = G;
	newProc->p_RH = NULL;
	return newProc;
}

ll_task* createllTask(task* t){
	ll_task* newllTask = (ll_task*)malloc(sizeof(ll_task));
	newllTask->next = NULL;
	newllTask->t = t;
	return newllTask;
}

ll_p* createllProc(proc* p){
	ll_p* newllProc = (ll_p*)malloc(sizeof(ll_p));
	newllProc->p = p;
	newllProc->next = NULL;
}

frame* createFrame(){
	int i;
	frame* newFrame = (frame*)malloc(sizeof(frame));
	for(i=0;i<G;i++){
		newFrame->arrayNodes[i] = NULL;
	}
	return newFrame;
}

FA* createFA(){
	int i;
	FA* newFA = (FA*)malloc(sizeof(FA));
	for(i=0;i<FSZ;i++){
		frame* newFrame = createFrame();
		newFA->arrayFrames[i] = newFrame;
	}
	return newFA;
}

