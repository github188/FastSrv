
pthread_mutex_t task_pool_mutex;

std::list<void*>* task_pool;

/*初始化任务队列*/
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

/*销毁任务队列*/
void destroy()
{
	delete task_pool;

	pthread_mutex_destroy(&task_pool_mutex);
}

/*存放任务到任务队列*/
int push(void* task)
{
	pthread_mutex_lock(&task_pool_mutex);
	task_pool->push_back(task);
	pthread_mutex_unlock(&task_pool_mutex);

	return 0;
}

/*从任务队列取出任务*/
void* pop()
{
	pthread_mutex_lock(&task_pool_mutex);
	void* task = NULL;
	task = task_pool->front();
	task_pool->pop_front();
	pthread_mutex_unlock(&task_pool_mutex);

	return task;
}


