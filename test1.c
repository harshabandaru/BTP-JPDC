#include <stdio.h>
#include <stdlib.h>
typedef struct task t;
struct task{
	int a;
	int b;
};

t* createTask(int a,int b){
	t* temp = (t*)malloc(sizeof(t));
	temp->a = a;
	temp->b = b;
	return temp;
}
int main(){
	t** aray;
	aray = (t**) malloc(3*sizeof(t*));
	aray[0] = createTask(1,2);
	aray[1] = createTask(2,3);
	aray[2] = createTask(1,4);
	//printf("%d",aray[0]->a);
	int x =9,y = 5;
	float fs = x + y;
	int ans = (float)x/(float)y + fs;
	printf("%d",ans);
	return 0;
}