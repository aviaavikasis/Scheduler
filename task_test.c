#include "task.h"
#include <assert.h>
#include <stdio.h>

void TaskCreateTest(void);
void TaskDestroyTest(void);

static int PrintHello(void *param);

int main()
{
	TaskCreateTest();
	/*TaskDestroyTest();*/
	printf("\n\n->->->->->->->->-> success!!! <-<-<-<-<-<-<-<-<-<\n\n\n");
	
	return 0;
}



void TaskCreateTest(void)
{
	operation_func task_func = &PrintHello;
	int a = 5;
	task_ty *task = TaskCreate(task_func , (void*)&a);
	TaskDestroy(task);
}




void TaskDestroyTest(void){}




static int PrintHello(void *param)
{
	printf("\nHello World %d\n" , *((int*)param));
	return 0;
}













