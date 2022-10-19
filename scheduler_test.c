#include <assert.h>  /* assert */
#include <stdio.h>   /* printf */
#include "scheduler.h"
#include "uid.h"

#define UNUSED(x) (void)x

struct params
{
	scheduler_ty *scheduler;
	uid_ty uid1;
	uid_ty uid2;
	uid_ty uid3;
	uid_ty uid4;	
};

void SchedulerCreateAndDestroyTest(void);
void SchedulerAddTaskTest(void);
void SchedulerRemoveTaskTest(void); 
void SchedulerRunTest(void); 
void SchedulerStopTest(void);
void SchedulerIsEmptyTest(void);
void TaskDeleteOtherTaskTest(void);

int PrintTask1(void *null);
int PrintTask2(void *null);
int PrintTask3(void *null);
int PrintTask4(void *null);
int PrintTask5(void *scheduler);
int StopTask(void *scheduler);
int RemoveOtherTask(void *params_struct);
void CleanScheduler(void *scheduler);



int main(void)
{
	SchedulerCreateAndDestroyTest();
	SchedulerAddTaskTest();
	SchedulerRemoveTaskTest(); 
	SchedulerRunTest(); 
	SchedulerStopTest();
	SchedulerIsEmptyTest();
	TaskDeleteOtherTaskTest();
	printf("\n\n->->->->->->->->-> success!!! <-<-<-<-<-<-<-<-<-<\n\n\n");
	
	return 0;
}



void SchedulerCreateAndDestroyTest(void)
{
	scheduler_ty *scheduler = SchedulerCreate();
	SchedulerDestroy(scheduler);
}

 
void SchedulerAddTaskTest(void)
{
	scheduler_ty *scheduler = SchedulerCreate();
	operation_func stop_scheduler1 = &PrintTask1;
	operation_func stop_scheduler2 = &PrintTask2;
	operation_func stop_scheduler3 = &PrintTask3;
	operation_func stop_scheduler4 = &PrintTask4;
	
	SchedulerAddTask(scheduler, stop_scheduler1 , NULL, NULL, NULL, 3);
	SchedulerAddTask(scheduler, stop_scheduler2 , NULL, NULL, NULL, 5);
	SchedulerAddTask(scheduler, stop_scheduler3 , NULL, NULL, NULL, 7);
	SchedulerAddTask(scheduler, stop_scheduler4 , NULL, NULL, NULL, 9);
	
	assert(SchedulerSize(scheduler) == 4);
	
	SchedulerClear(scheduler);
	SchedulerDestroy(scheduler);
}



void SchedulerRemoveTaskTest(void)
{
	uid_ty uid_add1 = {0};
	uid_ty uid_add2 = {0};
	scheduler_ty *scheduler = SchedulerCreate();
	operation_func stop_scheduler1 = &PrintTask1;
	operation_func stop_scheduler2 = &PrintTask2;
	operation_func stop_scheduler3 = &PrintTask3;
	operation_func stop_scheduler4 = &PrintTask4;
	
	uid_add1 = SchedulerAddTask(scheduler, stop_scheduler1 , NULL, NULL, NULL, 3);
	uid_add2 = SchedulerAddTask(scheduler, stop_scheduler2 , NULL, NULL, NULL, 5);
	SchedulerAddTask(scheduler, stop_scheduler3 , NULL, NULL, NULL, 7);
	SchedulerAddTask(scheduler, stop_scheduler4 , NULL, NULL, NULL, 9);
	
	assert(SchedulerSize(scheduler) == 4);
	SchedulerRemoveTask(scheduler , uid_add1);
	assert(SchedulerSize(scheduler) == 3);
	SchedulerRemoveTask(scheduler , uid_add2);
	assert(SchedulerSize(scheduler) == 2);
	
	SchedulerClear(scheduler);
	SchedulerDestroy(scheduler);

} 



void SchedulerRunTest(void)
{
/*
	scheduler_ty *scheduler = SchedulerCreate();
	operation_func stop_scheduler1 = &PrintTask1;
	operation_func stop_scheduler2 = &PrintTask2;
	operation_func stop_scheduler3 = &PrintTask3;
	operation_func stop_scheduler4 = &PrintTask4;
	
	SchedulerAddTask(scheduler, stop_scheduler1 , NULL, NULL, NULL, 1);
	SchedulerAddTask(scheduler, stop_scheduler2 , NULL, NULL, NULL, 4);
	SchedulerAddTask(scheduler, stop_scheduler3 , NULL, NULL, NULL, 3);
	SchedulerAddTask(scheduler, stop_scheduler4 , NULL, NULL, NULL, 4);
	
	SchedulerRun(scheduler);
	
	SchedulerDestroy(scheduler);
*/
}




void SchedulerIsEmptyTest(void)
{
	scheduler_ty *scheduler = SchedulerCreate();
	operation_func stop_scheduler1 = &PrintTask1;
	operation_func stop_scheduler2 = &PrintTask2;
	operation_func stop_scheduler3 = &PrintTask3;
	operation_func stop_scheduler4 = &PrintTask4;
	
	SchedulerAddTask(scheduler, stop_scheduler1 , NULL, NULL, NULL, 3);
	SchedulerAddTask(scheduler, stop_scheduler2 , NULL, NULL, NULL, 5);
	SchedulerAddTask(scheduler, stop_scheduler3 , NULL, NULL, NULL, 7);
	SchedulerAddTask(scheduler, stop_scheduler4 , NULL, NULL, NULL, 9);
	
	assert(SchedulerIsEmpty(scheduler) == 0);
	SchedulerClear(scheduler);
	assert(SchedulerIsEmpty(scheduler) == 1);
			
	SchedulerDestroy(scheduler);
}




void SchedulerStopTest(void)
{
/*
	scheduler_ty *scheduler = SchedulerCreate();
	operation_func stop_scheduler1 = &PrintTask1;
	operation_func stop_scheduler2 = &PrintTask2;
	operation_func stop_scheduler3 = &PrintTask3;
	operation_func stop_scheduler4 = &PrintTask4;
	operation_func stop_scheduler5 = &StopTask;
	cleanup_func clean_scheduler = &CleanScheduler;
	
	SchedulerAddTask(scheduler, stop_scheduler1 , NULL, NULL, NULL, 1);
	SchedulerAddTask(scheduler, stop_scheduler2 , NULL, NULL, NULL, 2);
	SchedulerAddTask(scheduler, stop_scheduler3 , NULL, NULL, NULL, 3);
	SchedulerAddTask(scheduler, stop_scheduler4 , NULL, NULL, NULL, 4);
	SchedulerAddTask(scheduler, stop_scheduler5 , scheduler, clean_scheduler, scheduler, 10);
	
	SchedulerRun(scheduler);
	SchedulerDestroy(scheduler);
*/
}


void TaskDeleteOtherTaskTest(void)
{

	uid_ty uid1 = {0};
	uid_ty uid2 = {0};
	uid_ty uid3 = {0};
	uid_ty uid4 = {0};
	

	struct params remove_params = {0};
	scheduler_ty *scheduler = SchedulerCreate();
	operation_func stop_scheduler1 = &PrintTask1;
	operation_func stop_scheduler2 = &PrintTask2;
	operation_func stop_scheduler3 = &PrintTask3;
	operation_func stop_scheduler4 = &PrintTask4;
	operation_func remove_other_task = &RemoveOtherTask;
	cleanup_func clean_scheduler = &CleanScheduler;
	
	
	uid1 = SchedulerAddTask(scheduler, stop_scheduler1 , NULL, NULL, NULL, 1);
	uid2 = SchedulerAddTask(scheduler, stop_scheduler2 , NULL, NULL, NULL, 4);
	uid3 = SchedulerAddTask(scheduler, stop_scheduler3 , NULL, NULL, NULL, 3);
	uid4 = SchedulerAddTask(scheduler, stop_scheduler4 , NULL, NULL, NULL, 4);
	
	remove_params.scheduler = scheduler;
	remove_params.uid1 = uid1;	
	remove_params.uid2 = uid2;
	remove_params.uid3 = uid3;	
	remove_params.uid4 = uid4;		

	
	SchedulerAddTask(scheduler, remove_other_task , &remove_params, clean_scheduler, scheduler, 10);
	
	SchedulerRun(scheduler);
	
	SchedulerDestroy(scheduler);	

}


int PrintTask1(void *null)
{
	UNUSED(null);
	printf("\nHi , i'm task 1\n");
	return 0;
}

int PrintTask2(void *null)
{
	UNUSED(null);
	printf("\nHi , i'm task 2\n");
	return 0;
}

int PrintTask3(void *null)
{
	UNUSED(null);
	printf("\nHi , i'm task 3\n");
	return 0;
}

int PrintTask4(void *null)
{
	UNUSED(null);
	printf("\nHi , i'm task 4\n");
	return 0;
}

int StopTask(void *scheduler)
{
	printf("\nHi , i'm task stop\n");
	SchedulerStop(scheduler);
	return 1;
}


int RemoveOtherTask(void *params_struct)
{	
	SchedulerRemoveTask((*(struct params*)params_struct).scheduler , (*(struct params*)params_struct).uid1);
	SchedulerRemoveTask((*(struct params*)params_struct).scheduler , (*(struct params*)params_struct).uid2);
	SchedulerRemoveTask((*(struct params*)params_struct).scheduler , (*(struct params*)params_struct).uid3);
	SchedulerRemoveTask((*(struct params*)params_struct).scheduler , (*(struct params*)params_struct).uid4);
	printf("\nHi , i'm remove all oteher tasks \n");
	return 1;
}

void CleanScheduler(void *scheduler)
{
	SchedulerClear(scheduler);
}



















