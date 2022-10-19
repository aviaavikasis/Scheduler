/*****************************************************   
 * Author : Avia Avikasis                            *
 * Reviewer: Assaf                                   *
 * Date : 26/06/2022                                 *
 * Description : imlementation of tasks scheduler    *
 *                                                   *
 *****************************************************/

#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include "scheduler.h"
#include "pqueue.h" /* all pqueue functions */
#include "task.h"   /* all task functions */

struct scheduler
{
    pqueue_ty *pqueue;
    unsigned int stop;
};

/*------------- static functions ----------------*/

/* add task to pqueue */
static void AddTask(scheduler_ty *scheduler , task_ty *task);
/* equal priority between two elements */
static int InsertPriorityFunc(void *data1, void *data2, void *params);
static int StopScheduler(void *scheduler);
/* check match between tasks and given uid */
static int IsMatchUid(const void *data , void *param);
/* calculate sleep time before execute task */
static size_t SleepTime(task_ty *task , time_t start_time);

/*------------------------------------------------*/


scheduler_ty *SchedulerCreate(void)
{
	scheduler_ty *scheduler  = (scheduler_ty*)malloc(sizeof(scheduler_ty));
	if(NULL == scheduler)
	{
		return NULL;
	}
	
	scheduler->pqueue = PQueueCreate(&InsertPriorityFunc, NULL);
	if(NULL == scheduler->pqueue)
	{
		free(scheduler);
		return NULL;
	}
	scheduler->stop = 0;
	
	return scheduler;
}


void SchedulerDestroy(scheduler_ty *scheduler)
{
	assert(NULL != scheduler);
	PQueueDestroy(scheduler->pqueue);
	free(scheduler);
}


uid_ty SchedulerAddTask(scheduler_ty *scheduler, operation_func task,
                                    void *task_param, cleanup_func cleanup,
                                     void *cleanup_param, size_t time_interval)
{
	task_ty *new_task = NULL;
	assert(NULL != scheduler);
	assert(NULL != task);
	
	new_task = TaskCreate(task , task_param ,cleanup , cleanup_param , time_interval);
	PQueueEnqueue(scheduler->pqueue, new_task);
	return TaskGetUid(new_task);
}                                     


int SchedulerRemoveTask(scheduler_ty *scheduler, uid_ty uid)
{
	is_data_match_ty is_match_uid = NULL;
	task_ty *remove_task = NULL;
	
	assert(NULL != scheduler);
	
	is_match_uid = &IsMatchUid;
	remove_task = PQueueErase(scheduler->pqueue, is_match_uid , (void*)&uid);
	
	if(NULL == remove_task)
	{
		TaskDestroy(remove_task);
		return 1;
	}
	
	TaskDestroy(remove_task);
		
	return 0;
}


int SchedulerRun(scheduler_ty *scheduler)
{
	int ret_func_value = 0;
	task_ty *curr_task = NULL;
	time_t start_time = 0;
	int sleep_time = 0;
	time_t curr_time = 0;
	
	assert(NULL != scheduler);
	
	scheduler->stop = 0;
	start_time = time(0);

	
	while(0 == scheduler->stop && !SchedulerIsEmpty(scheduler))
	{
		curr_task = (task_ty*)PQueuePeek(scheduler->pqueue);
		PQueueDequeue(scheduler->pqueue);
		
		sleep_time = SleepTime(curr_task , start_time);
		if(-1 == sleep_time)
		{
			return 1;
		}		
		sleep(sleep_time);	
		ret_func_value = (*TaskGetOperationFunc(curr_task))(TaskGetParam(curr_task));
		
		if(0 == ret_func_value)
		{
			AddTask(scheduler , curr_task);
			curr_time = time(0);
			if(-1 == curr_time)
			{
				return 1;
			}	
            TaskSetPriority(curr_task , curr_time - start_time + 
            							TaskGetInterval(curr_task));
		}
		else 
		{
			(*TaskGetCleanupFunc(curr_task))(TaskGetCleanUpParam(curr_task));
			TaskDestroy(curr_task);
		}
	}
	return 0;
}


void SchedulerStop(scheduler_ty *scheduler)
{
	task_ty *stop_task = NULL;
	operation_func stop_scheduler = NULL;
	assert(NULL != scheduler);
	
	stop_scheduler = &StopScheduler;
	stop_task = TaskCreate(stop_scheduler , NULL , NULL , NULL , 0);
	AddTask(scheduler , stop_task);
}


size_t SchedulerSize(const scheduler_ty *scheduler)
{
	assert(NULL != scheduler);
	return PQueueSize(scheduler->pqueue);
}


int SchedulerIsEmpty(const scheduler_ty *scheduler)
{
	assert(NULL != scheduler);
	return PQueueIsEmpty(scheduler->pqueue);
}

void SchedulerClear(scheduler_ty *scheduler)
{
	task_ty *remove_task = NULL;
	assert(NULL != scheduler);
	
	while(!SchedulerIsEmpty(scheduler))
	{
		remove_task = PQueuePeek(scheduler->pqueue);
		SchedulerRemoveTask(scheduler , TaskGetUid(remove_task));
	}
}




/*======================= static functions ============================*/


static int InsertPriorityFunc(void *data1, void *data2, void *params)
{
	if(NULL == params)
	{
		(void)params;
	}
	return (TaskGetPriority((task_ty*)data1) < TaskGetPriority((task_ty*)data2));
}

static void AddTask(scheduler_ty *scheduler , task_ty *task)
{
	assert(NULL != scheduler);
	PQueueEnqueue(scheduler->pqueue, task);	
}


static int StopScheduler(void *scheduler)
{
	assert(NULL != scheduler);
	
	((scheduler_ty*)scheduler)->stop = 1;
	return 0;
}

static int IsMatchUid(const void *data , void *param)
{
	return (UidIsEqual(TaskGetUid((task_ty*)data) , *(uid_ty*)param));
}

static size_t SleepTime(task_ty *task , time_t start_time)
{
	time_t curr_time = 0;
	assert(NULL != task);
	
	curr_time = time(0);
	if(-1 == curr_time)
	{
		return -1;
	}
	return ((int)TaskGetPriority(task)-((int)curr_time-(int)start_time) < 0) ? 0 :
								TaskGetPriority(task) - (curr_time - start_time);
}










