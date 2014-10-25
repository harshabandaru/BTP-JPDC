#pragma once
#include "ds.h"
#include <stdio.h>
//heap is maintained by the pseudo deadlines of the tasks

t_heap* t_createHeap (int);
int t_parent (t_heap*,int);
int t_leftChild (t_heap*, int);
int t_rightChild (t_heap*, int);
task* t_getMinimum (t_heap*);
void t_heapify (t_heap*, int);
task* t_deleteMin(t_heap* );
void t_insert(t_heap* ,task*);
void t_resizeHeap(t_heap*);

t_heap* t_createHeap(int capacity){
	t_heap* h = (t_heap*) malloc(sizeof(t_heap));
	if(h == NULL){
		printf("Memory error");
		return;
	}
	h->t_h_count = 0;
	h->t_h_capacity = capacity;
	h->t_h_array = (task**)malloc(capacity*sizeof(task*));
	return h;
}

int t_parent(t_heap* h,int i){
	if(i<=0 || i>=h->t_h_count)
		return;
	return (i-1)/2;
}

int t_leftChild (t_heap* h, int i){
	int left = 2*i + 1;
	if(left >= h->t_h_count)
		return -1;
	return left;
}

int t_rightChild (t_heap* h, int i){
	int right = 2*i;
	if(right >= h->t_h_count)
		return -1;
	return right;
}

task* t_getMinimum(t_heap* h){
	if(h->t_h_count == 0)
		return NULL;
	return h->t_h_array[0];
}

task* t_deleteMin(t_heap* h){
	task* taskNode;
	if(h->t_h_count == 0)
		return NULL;

	taskNode = h->t_h_array[0];
	h->t_h_array[0] = h->t_h_array[h->t_h_count-1];
	h->t_h_count--;
	t_heapify(h,0);
	return taskNode;
}

void t_heapify(t_heap* h, int i){  
	int l,r,min;
	task* temp;
	l = t_leftChild(h,i);
	r = t_rightChild(h,i);
	if(l!=-1 && (h->t_h_array[l]->t_pd) < h->t_h_array[i]->t_pd)
		min = l;
	else
		min = i;
	if(r!=-1 && (h->t_h_array[r]->t_pd) < h->t_h_array[min]->t_pd)
		min = l;

	if(min!=i){
		//swap ith node and minth node
		temp = h->t_h_array[i];
		h->t_h_array[i] = h->t_h_array[min];
		h->t_h_array[min] = temp;
		t_heapify(h,min);
	}
	
}

void t_insert(t_heap* h,task* t){
	if(h->t_h_count == h->t_h_capacity)
		t_resizeHeap(h);

	h->t_h_count++;

	int i = h->t_h_count;
	while(i > 0 && t->t_pd < h->t_h_array[(i-1)/2]->t_pd){
		h->t_h_array[i] = h->t_h_array[(i-1)/2];
		i = (i-1)/2;
	}

	h->t_h_array[i] = t;
}

void t_resizeHeap(t_heap* h){
	int i;
	task** array_old = h->t_h_array;
	h->t_h_array = (task **) malloc(sizeof(task*) * h->t_h_capacity * 2);

	if(h->t_h_array == NULL){
		printf("Memory Error");
		return;
	}

	for(i = 0;i < h->t_h_capacity;i++){
		h->t_h_array[i] = array_old[i];
	}
	h->t_h_capacity *= 2;
	free(array_old); 
}

