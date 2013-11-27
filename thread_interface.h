#ifndef _THREAD_INTERFACE_H_
#define _THREAD_INTERFACE_H_

#include "thread.h"

namespace PUS
{
	/*thread interface*/
	class thread_interface
	{
	public:
		int create(int reserve = 32);
		int destory(int wait = 0);
		int work();
	};
}

/*_THREAD_INTERFACE_H_*/
#endif
