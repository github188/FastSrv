
typedef struct pool
{
	pthread_t tid;
	pthread_mutex_t tlock;
} pool;
std::list<pool*>* thread_pool;

int thread_pool_init()
{
	if((thread_pool = new std::list<pool*>) == NULL)
	{
		return -1;
	}

	thread_pool->clear();
	return 0;
}

void thread_pool_destroy()
{
	delete thread_pool;
}

int thread_pool_add(unsigned int size,void*(*event)(void*))
{
	for(unsigned int i = 0 ; i < size ; ++i)
	{
		pool *p = new pool;

		if(pthread_mutex_init(&p->tlock,NULL) != 0)
		{
			delete p;
			printf("\nthread ==============thread_mutex_init fail!");
			return -1;
		}

		pthread_t tid;
		if(pthread_create(&tid,NULL,event,NULL) == 0)
		{
			pthread_detach(tid);
			thread_pool->push_back(p);
			printf("\nthread ==============pthread_create success!");
		}
		else
		{
			delete p;
			printf("\nthread ==============pthread_create fail!");
			return -1;
		}

		usleep(1*1000*1000);
	}

	return 0;
}


/*
//
//
//封存减少线程功能，在下一版中实现
//
//
//
*/
// /*减少线程*/
// int del_thread_from_pool(thread_pool* the_pool,size_t size)
// {
// 	/*遍历这个池，找到空闲线程，然后释放。释放规定大小或者遍历完成以后，退出*/
// 	thread_pool::iterator iter = the_pool->begin();
// 	for( ; iter != thread_pool->end() ; ++iter )
// 	{
// 		if(iter->is_work == WAITING)
// 		{
// 			if(size > 0)
// 			{
// 				if(pthread_cancel(iter->tid) == 0)
// 				{
// 					std::cout << "cancel thread " << tid << " success " << std::endl;
// 				}
// 				else
// 				{
// 					std::cout << "cancel thread " << tid << " error " << std::endl;
// 				}
// 				the_pool->remove(*iter);
// 				--size;
// 			}
// 		}
// 	}
// 	return FUN_OK;
// }

