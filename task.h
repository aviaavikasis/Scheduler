/*****************************************************   
 * Author : Avia Avikasis                            *
 * Reviewer: Assaf                                   *
 * Date : 26/06/2022                                 *
 * Description : imlementation of task               *
 *                                                   *
 *****************************************************/
#ifndef __TASK_H__
#define __TASK_H__

#include "uid.h"

typedef struct task task_ty;

typedef int (*operation_func_task)(void *task_param);
typedef void (*cleanup_func_task)(void *cleanup_param);

/*
Description : the TaskCreate() function create new task.
return value : pointer to the new task
time cpmlexity : O(1)
*/
task_ty *TaskCreate(operation_func_task task_func, 
                                     void *task_param,
                                     cleanup_func_task cleanup,
                                     void *cleanup_param, 
                                     size_t time_interval);

/*
Description : the TaskDestroy() function destroy exist task.
Param : pointer to task
return value : void
time cpmlexity : O(1)
*/
void TaskDestroy(task_ty *task);

/*
Description : the TaskGetUid() function get uid of task.
Param : pointer to task
return value : uid_ty
time cpmlexity : O(1)
*/
uid_ty TaskGetUid(task_ty *task);

/*
Description : the TaskGetInterval() function get time interval of task.
Param : pointer to task
return value : time interval(size_t)
time cpmlexity : O(1)
*/
size_t TaskGetInterval(task_ty *task);

/*
Description : the TaskGetPriority() function get the priority of task.
Param : pointer to task
return value : priority(size_t)
time cpmlexity : O(1)
*/
size_t TaskGetPriority(task_ty *task);

/*
Description : the TaskSetPriority() function set new priority in task.
Param : pointer to task , priority(size_t)
return value : void
time cpmlexity : O(1)
*/
void TaskSetPriority(task_ty *task , size_t priority);

/*
Description : the TaskGetOperationFunc() function get the
operation function of task.
Param : pointer to task
return value : pointer to operation func
time cpmlexity : O(1)
*/
operation_func_task TaskGetOperationFunc(task_ty *task);

/*
Description : the TaskGetCleanupFunc() function get the
cleanup function of task.
Param : pointer to task
return value : pointer to cleanup func
time cpmlexity : O(1)
*/
cleanup_func_task TaskGetCleanupFunc(task_ty *task);

/*
Description : the TaskGetCleanUpParam() function get the cleanup param of task.
Param : pointer to task
return value : void pointer
time cpmlexity : O(1)
*/
void *TaskGetCleanUpParam(task_ty *task);

/*
Description : the TaskGetParam() function get the operation param of task.
Param : pointer to task
return value : void pointer
time cpmlexity : O(1)
*/
void *TaskGetParam(task_ty *task);


#endif
























