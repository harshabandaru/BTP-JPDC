#include "ds.h"
//heap is maintained by the spare capacities of the processors

p_heap* p_createHeap (int);
int p_parent (p_heap*,int);
int p_leftChild (p_heap*, int);
int p_rightChild (p_heap*, int);
proc* p_getMinimum (p_heap*);
void p_heapify (p_heap*, int);
proc* p_deleteMin(p_heap* );
void p_insert(p_heap* ,proc*);
void p_resizeHeap(p_heap*);

p_heap* p_createHeap(int capacity){
	p_heap* h = (p_heap*) malloc(sizeof(p_heap));
	if(h == NULL){
		printf("Memory error");
		return;
	}
	h->p_h_count = 0;
	h->p_h_capacity = capacity;
	h->p_h_array = (proc**)malloc(capacity*sizeof(proc*));
	return h;
}

int p_parent(p_heap* h,int i){
	if(i<=0 || i>=h->p_h_count)
		return;
	return (i-1)/2;
}

int p_leftChild (p_heap* h, int i){
	int left = 2*i + 1;
	if(left >= h->p_h_count)
		return -1;
	return left;
}

int p_rightChild (p_heap* h, int i){
	int right = 2*i;
	if(right >= h->p_h_count)
		return -1;
	return right;
}

proc* p_getMinimum(p_heap* h){
	if(h->p_h_count == 0)
		return -1;
	return h->p_h_array[0];
}

proc* p_deleteMin(p_heap* h){
	proc* procNode;
	if(h->p_h_count == 0)
		return -1;

	procNode = h->p_h_array[0];
	h->p_h_array[0] = h->p_h_array[h->p_h_count-1];
	h->p_h_count--;
	p_heapify(h,0);
	return procNode;
}

void p_heapify(p_heap* h, int i){  
	int l,r,min;
	proc* temp;
	l = p_leftChild(h,i);
	r = p_rightChild(h,i);
	if(l!=-1 && (h->p_h_array[l]->p_sc) < h->p_h_array[i]->p_sc)
		min = l;
	
	if(r!=-1 && (h->p_h_array[r]->p_sc) < h->p_h_array[min]->p_sc)
		min = l;

	if(min!=i){
		//swap ith node and minth node
		temp = h->p_h_array[i];
		h->p_h_array[i] = h->p_h_array[min];
		h->p_h_array[min] = temp;
	}
	p_heapify(h,min);
}

void p_insert(p_heap* h,proc* p){
	if(h->p_h_count == h->p_h_capacity)
		p_resizeHeap(h);

	h->p_h_count++;

	int i = h->p_h_count;
	while(i > 1 && p->p_sc < h->p_h_array[(i-1)/2]->p_sc){
		h->p_h_array[i] = h->p_h_array[(i-1)/2];
		i = (i-1)/2;
	}

	h->p_h_array[i] = p;
}

void p_resizeHeap(p_heap* h){
	int i;
	proc** array_old = h->p_h_array;
	h->p_h_array = (proc **) malloc(sizeof(proc*) * h->p_h_capacity * 2);

	if(h->p_h_array == NULL){
		printf("Memory Error");
		return;
	}

	for(i = 0;i < h->p_h_capacity;i++){
		h->p_h_array[i] = array_old[i];
	}
	
	h->p_h_capacity *= 2;
	free(array_old); 
}

