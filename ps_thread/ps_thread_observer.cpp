
/* 
//
//
//封存动态调整线程池功能，该功能在下一版中实现
//
//
*/


// class control
// {
// private:
// 	int minimum;
// 	int maximum;
// 	int current_num;
// 	int working;
// public:
// 	control(int minimum_t,int maximum_t):minimum(minimum_t),maximum(maximum_t)
// 	{
// 	}
// public:
// 	/*设置池的下限*/
// 	int set_minimum(int minimum_t)
// 	{
// 		minimum = minimum_t;
// 	};

// 	/*设置池的上限*/
// 	int set_maximum(int maximum_t)
// 	{
// 		maximum = maximum_t;
// 	};

// 	/*设置线程工作状态*/
// 	void set_work()
// 	{
// 		++this->working;
// 	}

// 	/*设置线程等待状态*/
// 	void set_unwork()
// 	{
// 		--this->working;
// 	}

// 	/*判断是否“初始化/扩充”线程，返回扩充的线程数量*/
// 	int is_add_thread()
// 	{
// 		if(this->current_num == 0)
// 		{
// 			return this->minimum;
// 		}

// 		if(this->current_num <= this->maximum*0.95)
// 		{
// 			if(this->working >= this->current_num*0.8)
// 			{
// 				return this->maximum*0.05;
// 			}
// 			return 0;
// 		}
// 		return 0;
// 	}

// 	/*判断是否缩减线程，返回缩减的线程数量*/
// 	int is_del_thread()
// 	{
// 		if(this->current_num >= this->minimum)
// 		{
// 			if(this->working <= this->current_num*0.5)
// 			{
// 				return this->maximum*0.05;
// 			}
// 			return 0;
// 		}
// 		return 0;
// 	}
// };
// control *w_pool_control,*r_pool_control;

// /*生产者线程启动函数*/
// void* add_producer_to_pool(void* p)
// {
// 	(pool)p->t_id = pthread_self();
// 	w_pool.push_back((pool)p);

// 	while(1)
// 	{
// 		pthread_mutex_lock((pool)p->t_lock);
// 		(pool)p->is_work = WORKING;
// 		/*插入任务队列*/
// 		void* task = (pool)p->fun(NULL);
// 		if(TASK_POOL::push(task) != 0)
// 		{
// 			std::cout << "TASK_POOL::push error" << std::endl;
// 		}
// 		(pool)p->is_work = WAITING;
// 		pthread_mutex_unlock((pool)p->t_lock);
// 		usleep(100);
// 	}
// }

// /*消费者线程启动函数*/
// void* add_consumer_to_pool(void* p)
// {
// 	(pool)p->t_id = pthread_self();
// 	r_pool.push_back((pool)p);

// 	while(1)
// 	{
// 		pthread_mutex_lock((pool)p->t_lock);
// 		(pool)p->is_work = WORKING;
// 		/*从任务队列取数据，然后执行*/
// 		void* task = TASK_POOL::pop();
// 		(pool)p->fun(task);
// 		if(&(int*)(pool)p->fun(task) != 0)
// 		{
// 			std::cout << "TASK_POOL::pop error" << std::endl;
// 		}
// 		(pool)p->is_work = WAITING;
// 		pthread_mutex_unlock((pool)p->t_lock);
// 		usleep(100);
// 	}
// }

// /*管理者线程，动态调整线程池大小*/
// void* thread_admin(void* arg)
// {
// 	/*动态“初始化/扩充”线程池*/
// 	add_thread_to_pool(1,w_pool_control->is_add_thread(),arg);
// 	usleep(100000);
// 	add_thread_to_pool(2,r_pool_control->is_add_thread(),arg);
// 	usleep(100000);

// 	/*动态缩减线程池*/
// 	del_thread_from_pool(w_pool,w_pool_control->is_del_thread());
// 	usleep(100000);
// 	del_thread_from_pool(r_pool,r_pool_control->is_del_thread());
// 	usleep(100000);
// }

// int launch(void* (*producer_fun)(),void* (*consumer)())
// {
// 	/*初始化任务队列*/
// 	if(TASK_POOL::init() == 0)
// 	{
// 		std::cout << "init task pool success " << std::endl;
// 	}
// 	else
// 	{
// 		std::cout << "init task pool error " << std::endl;
// 	}

// 	while(1)
// 	{
// 		usleep(100);
// 	}

// 	return FUN_OK;
// }


