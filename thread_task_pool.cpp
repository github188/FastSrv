#include "thread_task_pool.h"

template<class T>
int threadTaskPool<T>::init()
{
	if((this->m_pool = new std::list<T*>) == NULL)
	{
		return -1;
	}

	if((this->m_mutex = new pthread_mutex_t) == NULL)
	{
		return -1;
	}

	if(pthread_mutex_init(&this->m_mutex,NULL))
	{
		delete this->m_mutex;
		return -1;
	}

	return 0;
}

template<class T>
void threadTaskPool<T>::destroy()
{
	delete this->m_pool;

	pthread_mutex_destroy(&this->m_mutex);
}

template<class T>
int threadTaskPool<T>::push(T* task)
{
	pthread_mutex_lock(&this->m_mutex);
	this->m_pool.push_back(task);
	pthread_mutex_unlock(&this->m_mutex);

	return 0;
}

template<class T>
T* threadTaskPool<T>::pop()
{
	pthread_mutex_lock(&this->m_mutex);
	T* task = NULL;
	task = this->m_pool.front();
	this->m_pool.pop_front();
	pthread_mutex_unlock(&this->m_mutex);

	return task;
}

