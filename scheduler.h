/*****************************************************   
 * Author : Avia Avikasis                            *
 * Reviewer: Assaf                                   *
 * Date : 26/06/2022                                 *
 * Description : imlementation of tasks scheduler    *
 *                                                   *
 *****************************************************/

#ifndef __ILRD_OL127_128_SCHEDULER_H__
#define __ILRD_OL127_128_SCHEDULER_H__

#include <stddef.h> /* size_t */
#include "uid.h"    /* uid_ty */


typedef int (*operation_func)(void *task_param);
typedef void (*cleanup_func)(void *cleanup_param);

typedef struct scheduler scheduler_ty;

/*
Description : the SchedulerCreate() function create new tasking scheduler.
return value : pointer to the new scheduler
time cpmlexity : O(1)
space complexity : O(n)
*/
scheduler_ty *SchedulerCreate(void);

/*
Description : the SchedulerDestroy() function destroy exist tasking scheduler.
Param : pointer to scheduler
return value : void
time cpmlexity : O(n)
*/
void SchedulerDestroy(scheduler_ty *scheduler); 

/*
Description : the SchedulerAddTask() function add new task to scheduler.
Params : pointer to scheduler , task operation func , param for operation func,
pointer to cleanup function , param for cleanup function ,time interval for task 
return value : uid of the new task
time cpmlexity : O(n)
*/
uid_ty SchedulerAddTask(scheduler_ty *scheduler, operation_func task,
                                    void *task_param, cleanup_func cleanup,
                                     void *cleanup_param, size_t time_interval);

/*
Description : the SchedulerRemoveTask() function remove task from scheduler.
Params : pointer to scheduler , uid of task 
return value : 0 on success , else 1 
time cpmlexity : O(n)
*/
int SchedulerRemoveTask(scheduler_ty *scheduler, uid_ty uid); 

/*
Description : the SchedulerRun() function run all tasks in scheduler.
Params : pointer to scheduler
return value : 0 on success , else 1 
time cpmlexity : O(n)
*/
int SchedulerRun(scheduler_ty *scheduler); 

/*
Description : the SchedulerStop() function stop the run of scheduler.
Params : pointer to scheduler
return value : void
time cpmlexity : O(1)
*/
void SchedulerStop(scheduler_ty *scheduler);

/*
Description : the SchedulerSize() function return the amount 
of tasks in scheduler.
Params : pointer to scheduler
return value : amount of tasks (size_t)
time cpmlexity : O(n)
*/
size_t SchedulerSize(const scheduler_ty *scheduler);

/*
Description : the SchedulerIsEmpty() function check if scheduler is empty.
Param :  scheduler pointer
return value : 1 if scheduler is empty , 0 otherwise
time cpmlexity : O(1)
*/
int SchedulerIsEmpty(const scheduler_ty *scheduler);

/*
Description : the SchedulerClear() function remove all elements in scheduler.
Param :  scheduler pointer
return value : void
time cpmlexity : O(n)
*/
void SchedulerClear(scheduler_ty *scheduler);

#endif /* __ILRD_OL127_128_SCHEDULER_H__ */ 








