#include <stdio.h>
#include <stdlib.h>
// #include "t_heap.h"
// #include "p_heap.h"
#include "calc.h"

void pofbfs(){
	FILE* fp;
	int n;		//no. of tasks
	int m;		//no. of processors
	int i;
	fp = fopen("input","r");
	fscanf(fp,"%d",&n);
	fscanf(fp,"%d",&m);
	
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
		t->t_naf = calc_naf(t);
		t->t_shr = calc_shr(t);
		t->t_wt = calc_wt(t);
		t->t_count = t->t_shr;
		//printf("%d %d %f \n",t->t_naf,t->t_shr ,t->t_wt);

	}
}