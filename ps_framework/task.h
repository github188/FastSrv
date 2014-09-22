#ifndef __PS_FW_TASK__
#define __PS_FW_TASK__
////////////////////////////////////////////////////////////////////////////////////////
//
//	Creater : zengpw
//	Create Date : 2014-8-21
//	Modify history :
//					2014-9-18 zengpw 重新设计
//	File Property : private
//	Description :
//					I. 消息队列头文件
//					II. 采用 queue 做容器
//					III. 它提供的接口中，task 是基础数据类型（因为内部要支持free()函数）
//	Future :
//					I. 提供双队列（输入和输出）
//
//
////////////////////////////////////////////////////////////////////////////////////////

#include "_include.h"

namespace PS_FW
{
	class Task
	{
	public:
		Task();
		virtual ~Task();
	public:
		int push(void* task);
		int pop(void** task);
	private:
		std::queue<void*>* m_queue;
		pthread_mutex_t m_queueLock;
	};
}	//PS_FW

#endif //__PS_FW_TASK__
