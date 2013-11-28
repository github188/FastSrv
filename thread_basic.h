#ifndef _THREAD_BASIC_H_
#define _THREAD_BASIC_H_

#include <sys/types.h>
#include <pthread.h>
#include <deque>
#include <queue>

/*thread pool*/
struct thread_unit
{
	pthread_t thread_id;
	pthread_mutex_t thread_lock;
	int thread_status;
	int work_state;
};
typedef std::deque<struct thread_unit> thread_deque;

/*thread task allocation*/
typedef std::queue<gid_t> thread_free;
typedef std::queue<gid_t> thread_busy;

/*initialization*/
int thread_pool_init(thread_deque& pool,size_t size);



/*_THREAD_BASIC_H_*/
#endif
