#pragma once
#include "p_heap.h" 		//p_heap api test codes
int main(){
	p_heap* h = p_createHeap(2);
	proc* p1 = createProc();
	p1->p_sc = 5;
	p_insert(h,p1);
	
	proc* p2 = createProc();
	p_insert(h,p2);

	proc* p3 = createProc();
	p3->p_sc = 2;
	p_insert(h,p3);	

	proc* p4 = createProc();
	p4->p_sc = 7;
	p_insert(h,p4);	

	proc* p5 = createProc();
	p5->p_sc = 1;
	p_insert(h,p5);	
	int i;
	for(i=0;i<5;i++){
		printf("%d ",h->p_h_array[i]->p_sc);
	}
	printf("\n");
	p_deleteMin(h);
	p_deleteMin(h);
	proc* minp = p_getMinimum(h);
	printf("%d\n",minp->p_sc);
	proc* p6 = createProc();
	p_insert(h,p6);
	minp = p_getMinimum(h);
	printf("%d\n",minp->p_sc);
	return 0;
}

/*


10 12
9 12
9 12
4 12
4 12


*/