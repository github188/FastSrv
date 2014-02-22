
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
		return -1;
	}

	return 0;
}

void task_destroy()
{
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

int task_pop(void* task)
{
	pthread_mutex_lock(&task_mutex);
	if(!task_pool->empty())
	{
		task = task_pool->front();
		task_pool->pop_front();
	}
	else
	{
		return -1;
	}
	pthread_mutex_unlock(&task_mutex);

	return 0;
}


