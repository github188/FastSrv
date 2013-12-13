#ifndef _THREAD_TASK_POOL_HPP_
#define _THREAD_TASK_POOL_HPP_

#include <list>
#include <pthread.h>

template<class T>
std::list<T*> task_pool;

pthread_mutex_t task_pool_mutex;

template<class T>
int task_pool_init()
{
	if((task_pool = new std::list<T*>) == NULL)
	{
		return -1;
	}

	if((task_pool_mutex = new pthread_mutex_t) == NULL)
	{
		return -1;
	}

	if(pthread_mutex_init(&task_pool_mutex,NULL))
	{
		delete task_pool_mutex;
		return -1;
	}

	return 0;
}

template<class T>
void task_pool_destroy()
{
	delete task_pool;

	pthread_mutex_destroy(&task_pool_mutex);
}

template<class T>
int task_pool_push(T* task)
{
	pthread_mutex_lock(&task_pool_mutex);
	task_pool.push_back(task);
	pthread_mutex_unlock(&task_pool_mutex);

	return 0;
}

template<class T>
T* task_pool_pop()
{
	pthread_mutex_lock(&task_pool_mutex);
	T* task = NULL;
	task = task_pool.front();
	task_pool.pop_front();
	pthread_mutex_unlock(&task_pool_mutex);

	return task;
}

/*_THREAD_TASK_POOL_HPP_*/
#endif
