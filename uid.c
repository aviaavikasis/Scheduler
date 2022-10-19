#include <assert.h>
#include "uid.h"

const uid_ty bad_uid = {0};

uid_ty UidCreate(void)
{
	uid_ty uid = {0,0,0};
	static size_t counter = 0;
	uid.pid = getpid();
	uid.time = time(0);
	if (-1 == uid.time)
	{
		return bad_uid;
	}
	uid.counter = counter + 1;
	++counter; 
	
	return uid;
}


int UidIsEqual(uid_ty uid1, uid_ty uid2)
{
	return (uid1.pid == uid2.pid   &&
			uid1.time == uid2.time &&
			uid1.counter == uid2.counter); 
}

















