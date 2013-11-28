#ifndef _THREAD_INTERFACE_H_
#define _THREAD_INTERFACE_H_

#include "thread_pool.h"

/*thread interface*/
class thread_interface
{
public:
	int create(int reserve = 32);
	int destory(int wait = 0);
	int work();
};

/*_THREAD_INTERFACE_H_*/
#endif
