typedef struct taskNode task;
typedef struct llNode ll;
typedef struct procNode proc;
typedef struct t_h t_heap;		//minheap of taskpointers
typedef struct p_h p_heap;		//minheap of procpointers
typedef struct ll_TaskNode ll_task;
typedef struct frameList frame;
typedef struct FA_node FA;

struct t_h {
	task** t_h_array;		//array of task pointers			
	int t_h_count;				//number of elements in heap
	int t_h_capacity;			//size of heap
};

struct p_h {
	proc** p_h_array;		//array of processor pointers
	int p_h_count;				//number of elements in heap
	int p_h_capacity;			//size of heap
};

struct procNode {
	int p_id;
	int p_sc;					//spare capacity
	int p_migr;
	int p_prev_migr;
	t_heap* p_RH;				//RHi->ready heap pointer
};

struct llNode{						//linked list
	proc* p;				//processor node
	ll* next;
};

struct task {
	int t_id;
	int t_e;
	int t_p;
	int t_re;
	int t_pe;
	int t_start;
	int t_wt;
	int t_shr;
	int t_naf;
	int t_wt_me;
	int t_wt_mpe;
	int t_count;
	int t_pd;
	ll* t_TP;			//TPj->linked list of processors
};

//Main DataStructure FA

struct ll_TaskNode {		//Linked list of tasks
	task* t;
	ll_task* next;
};

struct frameList {
	ll_task* arrayNodes[G];
};

struct FA_node{
	frame* arrayFrames[FSZ]; //need to define FSZ
};

