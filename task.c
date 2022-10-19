#include <stdlib.h> /* malloc */
#include <assert.h>
#include "task.h"


struct task
{
    uid_ty uid;
    operation_func_task task_func;
    cleanup_func_task cleanup;
    void *cleanup_param;
    size_t time_interval;
    size_t priority;
    void *param;
};


/*==========================================*/


task_ty *TaskCreate(operation_func_task task_func ,
                                 void *task_param ,
                                 cleanup_func_task cleanup,
                                 void *cleanup_param, 
                                 size_t time_interval)
{
	task_ty *task = (task_ty*)malloc(sizeof(task_ty));
	if(NULL == task)
	{
		return NULL;
	}
	
	task->uid = UidCreate();
	if(UidIsEqual(bad_uid , task->uid))
	{
		free(task);
		return NULL;
	}
	
	task->task_func = task_func;
	task->param = task_param;
	task->cleanup = cleanup;
	task->cleanup_param = cleanup_param;
	task->time_interval = time_interval;
	task->priority = time_interval;

	return task;
}

void TaskDestroy(task_ty *task)
{
	assert(NULL != task);
	free(task);
	task = NULL;
}


uid_ty TaskGetUid(task_ty *task)
{
	assert(NULL != task);
	return task->uid;
}


size_t TaskGetInterval(task_ty *task)
{
	assert(NULL != task);
	return task->time_interval;
}


size_t TaskGetPriority(task_ty *task)
{
	assert(NULL != task);
	return task->priority;
}


void TaskSetPriority(task_ty *task , size_t priority)
{
	assert(NULL != task);
	task->priority = priority;
}

operation_func_task TaskGetOperationFunc(task_ty *task)
{
	assert(NULL != task);
	return task->task_func;
}

cleanup_func_task TaskGetCleanupFunc(task_ty *task)
{
	assert(NULL != task);
	return task->cleanup;
}

void *TaskGetCleanUpParam(task_ty *task)
{
	assert(NULL != task);
	return task->cleanup_param; 
}

void *TaskGetParam(task_ty *task)
{
	assert(NULL != task);
	return task->param;
}





