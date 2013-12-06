#ifndef _THREAD_TASK_POOL_H_
#define _THREAD_TASK_POOL_H_

#include <list>

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
public:
	/*not thread safe,so you must use init()/destroy() in single(master) thread*/
	int init();
	int destroy();

	/*manipulating pool*/
	int push(T* task);
	T* pop();
};

/*_THREAD_TASK_POOL_H_*/
#endif
