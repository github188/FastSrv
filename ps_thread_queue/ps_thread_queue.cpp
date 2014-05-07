
#include "ps_thread_queue_api.h"

pthread_mutex_t task_mutex;
std::list<void*>* task_pool;

int task_init()
{
	if((task_pool = new std::list<void*>) == NULL)
	{
		return -1;
	}

	if(pthread_mutex_init(&task_mutex,NULL))
	{
		task_destroy();
		return -1;
	}

	return 0;
}

void task_destroy()
{
	while(!task_pool->empty())
	{
		void* task = task_pool->front();
		task_pool->pop_front();
		/* 有待改进 */
		free(task);
	}

	delete task_pool;

	pthread_mutex_destroy(&task_mutex);
}

int task_push(void* task)
{
	pthread_mutex_lock(&task_mutex);
	task_pool->push_back(task);
	pthread_mutex_unlock(&task_mutex);

	return 0;
}

int task_pop(void** task)
{
	pthread_mutex_lock(&task_mutex);
	if(!task_pool->empty())
	{
		*task = task_pool->front();
		task_pool->pop_front();
	}
	else
	{
		pthread_mutex_unlock(&task_mutex);
		return -1;
	}
	pthread_mutex_unlock(&task_mutex);

	return 0;
}

