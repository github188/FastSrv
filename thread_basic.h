#ifndef _THREAD_H_
#define _THREAD_H_

#include <pthread.h>
#include <deque>
#include <queue>

namespace PUS
{
	/*thread pool*/
	typedef int pthread_status;
	typedef int state;

	struct thread_unit
	{
		pthread_t thread_id;
		pthread_mutex_t thread_lock;
		pthread_status thread_status;
		state work_state;
	};
	typedef deque<thread_unit> thread_deque;

	/*thread task allocation*/
	typedef unsigned int thread_subscript;
	typedef queue<thread_subscript> thread_free;
	typedef queue<thread_subscript> thread_busy;
}

/*_THREAD_H*/
#endif
