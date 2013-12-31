#ifndef _THREAD_POOL_HPP_
#define _THREAD_POOL_HPP_

#include <sys/types.h>
#include <time.h>
#include <pthread.h>
#include <list>

#include "thread_task_pool.hpp"

namespace TASK_POOL = PURE_SERVER::TASK_POOL;

/*函数返回值*/
enum function
{
	FUN_OK = 0;
	FUN_EXCEPTION = 1;
}

/*工作状态*/
enum work
{
	WAITING = 0;
	WORKING = 1;
}

namespace PURE_SERVER
{
	namespace THREAD_POOL
	{
		//--------------------------------------
		/*
		**MODULE 1 定义基本数据结构和操作
		*/
		//--------------------------------------

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

		/*线程池管理者*/
		class control
		{
		private:
			int minimum;
			int maximum;
			int current_num;
			int working;
		public:
			/*设置池的下限*/
			int set_minimum(int minimum_t):minimum(minimum_t){};

			/*设置池的上限*/
			int set_maximum(int maximum_t):maximum(maximum_t){};

			/*设置线程工作状态*/
			void set_work()
			{
				++this->working;
			}

			/*设置线程等待状态*/
			void set_unwork()
			{
				--this->working;
			}

			/*判断是否“初始化/扩充”线程，返回扩充的线程数量*/
			int is_add_thread()
			{
				if(this->current_num == 0)
				{
					return this->minimum;
				}

				if(this->current_num <= this->maximum*0.95)
				{
					if(this->working >= this->current_num*0.8)
					{
						return this->maximum*0.05;
					}
					return 0;
				}
				return 0;
			}

			/*判断是否缩减线程，返回缩减的线程数量*/
			int is_del_thread()
			{
				if(this->current_num >= this->minimum)
				{
					if(this->working <= this->current_num*0.5)
					{
						return this->maximum*0.05;
					}
					return 0;
				}
				return 0;
			}
		};
		control *w_pool_control,*r_pool_control;

		//--------------------------------------
		/*
		**MODULE 2 线程调用函数，需要线程安全
		*/
		//--------------------------------------

		/*生产者线程启动函数*/
		void* add_producer_to_pool(void* p)
		{
			(pool)p->t_id = pthread_self();
			w_pool.push_back((pool)p);

			while(1)
			{
				pthread_mutex_lock((pool)p->t_lock);
				(pool)p->is_work = WORKING;
				/*插入任务队列*/
				void* task = (pool)p->fun(NULL);
				if(TASK_POOL::push(task) != 0)
				{
					std::cout << "TASK_POOL::push error" << std::endl;
				}
				(pool)p->is_work = WAITING;
				pthread_mutex_unlock((pool)p->t_lock);
				usleep(100);
			}
		}

		/*消费者线程启动函数*/
		void* add_consumer_to_pool(void* p)
		{
			(pool)p->t_id = pthread_self();
			r_pool.push_back((pool)p);

			while(1)
			{
				pthread_mutex_lock((pool)p->t_lock);
				(pool)p->is_work = WORKING;
				/*从任务队列取数据，然后执行*/
				void* task = TASK_POOL::pop();
				(pool)p->fun(task);
				if(&(int*)(pool)p->fun(task) != 0)
				{
					std::cout << "TASK_POOL::pop error" << std::endl;
				}
				(pool)p->is_work = WAITING;
				pthread_mutex_unlock((pool)p->t_lock);
				usleep(100);
			}
		}

		//--------------------------------------
		/*
		**MODULE 3
		**线程池维护函数，只能由管理线程使用，
		**所以不需要线程安全。
		*/
		//--------------------------------------

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
						the_pool->remove(*iter);
						--size;
					}
				}
			}

			if(pthread_cancel(tid) == 0)
			{
				std::cout << "cancel thread " << tid << " success " << std::endl;
			}
			else
			{
				std::cout << "cancel thread " << tid << " error " << std::endl;
				return FUN_EXCEPTION;
			}

			return FUN_OK;
		}

		/*管理者线程，动态调整线程池大小*/
		void* thread_admin(void* arg)
		{
			/*动态“初始化/扩充”线程池*/
			add_thread_to_pool(1,w_pool_control->is_add_thread(),arg);
			usleep(100000);
			add_thread_to_pool(2,r_pool_control->is_add_thread(),arg);
			usleep(100000);

			/*动态缩减线程池*/
			del_thread_from_pool(w_pool,w_pool_control->is_del_thread());
			usleep(100000);
			del_thread_from_pool(r_pool,r_pool_control->is_del_thread());
			usleep(100000);
		}

		//--------------------------------------
		/*
		**MODULE 4 线程池对外接口
		*/
		//--------------------------------------
		int launch(void* (*producer_fun)(),void* (*consumer)())
		{
			/*初始化任务队列*/
			if(TASK_POOL::init() == 0)
			{
				std::cout << "init task pool success " << std::endl;
			}
			else
			{
				std::cout << "init task pool error " << std::endl;
			}

			while(1)
			{
				usleep(100);
			}

			return FUN_OK;
		}
	}
}

/*_THREAD_POOL_HPP_*/
#endif
