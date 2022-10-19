#include <assert.h>
#include <stdio.h>
#include "uid.h"

/*const uid_ty bad_uid = {0};*/

void UidCreateTest(void);

void UidIsEqualTest(void);



int main()
{
	UidCreateTest();

	UidIsEqualTest();

	return 0;	
}



void UidCreateTest(void)
{
	uid_ty uid = {0,0,0};
	uid = UidCreate();
	printf("pid is :%d\n" , uid.pid);
	printf("time is :%ld\n" , uid.time);
	printf("counter is :%ld\n" , uid.counter);
}

void UidIsEqualTest(void)
{
	uid_ty uid1 = {0,0,0};
	uid_ty uid2 = {0,0,0};
	uid1 = UidCreate();
	uid2 = UidCreate();	
	assert(UidIsEqual(uid1 , uid2) == 0);
}














