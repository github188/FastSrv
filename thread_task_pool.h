#ifndef _THREAD_TASK_POOL_H_
#define _THREAD_TASK_POOL_H_

#include <list>
#include <pthread.h>

template<class T>
class threadTaskPool
{
public:
	threadTaskPool()
	{
		init();
	}

	~threadTaskPool()
	{
		destroy();
	}

private:
	/*the pool*/
	std::list<T*> m_pool;
	pthread_mutex_t m_mutex;
public:
	/*not thread safe,so you must use init()/destroy() in single(master) thread*/
	int init();
	void destroy();

	/*manipulating pool*/
	int push(T* task);
	T* pop();
};

/*_THREAD_TASK_POOL_H_*/
#endif
