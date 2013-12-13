#ifndef _THREAD_TASK_POOL_HPP_
#define _THREAD_TASK_POOL_HPP_

#include <list>
#include <pthread.h>

namespace PURE_SERVER
{
	namespace THREAD_TASK_POOL
	{
		pthread_mutex_t task_pool_mutex;

		std::list<void*>* task_pool;

		int init()
		{
			if((task_pool = new std::list<void*>) == NULL)
			{
				return -1;
			}

			if(pthread_mutex_init(&task_pool_mutex,NULL))
			{
				return -1;
			}

			return 0;
		}

		void destroy()
		{
			delete task_pool;

			pthread_mutex_destroy(&task_pool_mutex);
		}

		template<typename T>
		int push(T task)
		{
			pthread_mutex_lock(&task_pool_mutex);
			task_pool->push_back(task);
			pthread_mutex_unlock(&task_pool_mutex);

			return 0;
		}

		template<typename T>
		T pop()
		{
			pthread_mutex_lock(&task_pool_mutex);
			T task = NULL;
			task = task_pool->front();
			task_pool->pop_front();
			pthread_mutex_unlock(&task_pool_mutex);

			return task;
		}
	}
}

/*_THREAD_TASK_POOL_HPP_*/
#endif
