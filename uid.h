#ifndef __ILRD_OL127_128_UID_H__
#define __ILRD_OL127_128_UID_H__

#include <unistd.h> /* pid_t */
#include <time.h> /* time_t */
#include <stddef.h> /* size_t */
#include <sys/types.h>

struct uid
{
    pid_t pid;
    time_t time;
    size_t counter;
};

typedef struct uid uid_ty;

extern const uid_ty bad_uid;

/*
Description : the UidCreate() function create new uid of proccess.
return value : new uid
time cpmlexity : O(1)
*/
uid_ty UidCreate(void);

/*
Description : the UidIsEqual() function check if two uids are equal.
Param :  two uids
return value : 1 if they are equal , 0 otherwise
time cpmlexity : O(1)
*/
int UidIsEqual(const uid_ty uid1, const uid_ty uid2);

#endif /* __ILRD_OL127_128_UID_H__ */
