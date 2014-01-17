#ifndef _THREAD_POOL_HPP_
#define _THREAD_POOL_HPP_

#include <sys/types.h>
#include <time.h>
#include <pthread.h>
#include <list>

#include "thread_task_pool.hpp"

/*函数返回值*/
enum function
{
	FUN_OK = 0,
	FUN_EXCEPTION = 1
};

/*工作状态*/
enum work
{
	WAITING = 0,
	WORKING = 1
};

/*线程池basic结构*/
typedef struct pool
{
	pthread_t t_id;
	pthread_mutex_t t_lock;
	void* (*fun)(void* task);
	int is_work;
} pool;
typedef std::list<pool> thread_pool;

/*线程池*/
thread_pool* w_pool;
thread_pool* r_pool;

/*增加线程*/
int add_thread_to_pool(int type,size_t size,void* (*fun)())
{
	for(int i = 0 ; i < size ; ++i)
	{
		pool *p = new pool;

		p->is_work = WAITING;
		p->fun = fun;

		if(pthread_mutex_init(&p->t_lock,NULL) != 0)
		{
			delete p;
			std::cout << "pthread_mutex_init fail!" << std::endl;
			continue;
		}

		pthread_t tid;
		int iRe;

		if(type == 1)
		{
			iRe = pthread_create(&tid,NULL,add_producer_to_pool,(void*)p);
			++w_pool_control->working;
			++w_pool_control->current_num;
		}
		else if(type == 2)
		{
			iRe = pthread_create(&tid,NULL,add_consumer_to_pool,(void*)p);
			++r_pool_control->working;
			++r_pool_control->current_num;
		}

		if(iRe == 0)
		{
			std::cout << "pthread_create success!" << std::endl;
		}
		else
		{
			delete p;
			std::cout << "pthread_create fail!" << std::endl;
			continue;
		}

		pthead_detach(tid);
	}

	return FUN_OK;
}

/*减少线程*/
int del_thread_from_pool(thread_pool* the_pool,size_t size)
{
	/*遍历这个池，找到空闲线程，然后释放。释放规定大小或者遍历完成以后，退出*/
	thread_pool::iterator iter = the_pool->begin();
	for( ; iter != thread_pool->end() ; ++iter )
	{
		if(iter->is_work == WAITING)
		{
			if(size > 0)
			{
				if(pthread_cancel(iter->tid) == 0)
				{
					std::cout << "cancel thread " << tid << " success " << std::endl;
				}
				else
				{
					std::cout << "cancel thread " << tid << " error " << std::endl;
				}
				the_pool->remove(*iter);
				--size;
			}
		}
	}
	return FUN_OK;
}

/*_THREAD_POOL_HPP_*/
#endif
