#include <math.h>
#include "ds.h"
float calc_lag (task* t, int cur_time){
	float temp1 = ((float)(t->t_e)/(float)(t->t_p))*(cur_time - t->t_start);
	float temp2 = t->t_e - t->t_re;
	float lag = temp1-temp2;
	return lag; 
}

int calc_ERfair (task* t,int cur_time){
	if(calc_lag(t,cur_time) < 1)
		return 1; 		//return 1 if erfair is satisfied
	else
		return 0;
}

int calc_naf (task* t){
	int naf = (t->t_rp)/(t->t_re * G);			//should define G somewhere
	return naf;
}


int calc_shr (task* t){
	float shr = ((float)(t->t_e)/(float)(t->t_p)) * (t->t_naf + 1)* G ;
	return (int)shr;
}

int calc_shr_1 (task* t,int fst){
	float temp1 = ((float)(t->t_e)/(float)(t->t_p)) * (t->t_naf + 2)* G ;
	float temp2 = fst - t->t_start;
	float temp3 = t->t_e - t->t_re;
	int shr = ceil(temp1 + temp2) - temp3;
	return shr;
}

float calc_wt(task* t){
	return ((float)t->t_shr / (float)G); 
}

float calc_sc(proc* p){

}

int calc_pd(task* t,int k){
	return ((int)ceil((float)k / (float)t->t_wt));
}









