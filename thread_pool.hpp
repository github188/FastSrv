#ifndef _THREAD_POOL_HPP_
#define _THREAD_POOL_HPP_

#include <sys/types.h>
#include <pthread.h>
#include <deque>
#include <queue>

#include "thread_task_pool.hpp"

namespace TASK_POOL = PURE_SERVER::THREAD_TASK_POOL;

namespace PURE_SERVER
{
	namespace THREAD_POOL
	{
		struct basic
		{
			pthread_t thread_id;
			pthread_mutex_t thread_lock;
			int thread_status;
			int work_state;
		};
		typedef std::deque<struct basic> read_pool;
		typedef std::deque<struct basic> dispose_pool;

		typedef std::queue<gid_t> free_queue;
		typedef std::queue<gid_t> busy_queue;

		int read()
		{

		}

		int dispose()
		{

		}

		int launch()
		{
			int iReturn = TASK_POOL::init();
		}
	}
}

/*_THREAD_POOL_HPP_*/
#endif
