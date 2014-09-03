#ifndef __PS_FW_MSG_QUEUE__
#define __PS_FW_MSG_QUEUE__
////////////////////////////////////////////////////////////////////////////////////////
//
//	Creater : zengpw
//	Create Date : 2014年8月21日
//	Modify history :
//					2014年8月21日 zengpw 重新设计
//	File Property : private （此头文件是私有的）
//	Description :
//				I. 消息队列头文件
//				II.  接收队列由 IO 线程 put ，处理线程 get ，发送队列只由 处理线程 put
//				III. 目前我们采用 v1.3 版的 std::list ，以后会改用 std::queue ，性能会有提升
//				IV. 消息队列会主动通知其处理线程，因此它需要继承自 Event
//
////////////////////////////////////////////////////////////////////////////////////////

#include "sys_include.h"
#include "subject.h"

namespace PS_FW
{
	typedef std::list<void*> MsgList;

	class MsgQueue : public Subject
	{
	public:
		MsgQueue();
		virtual ~MsgQueue(){}
	public:
		int put(void* msg);
		int get(void** msg);
		int destory();
	private:
		MsgList* m_queue;
		pthread_mutex_t m_mxLock;
	};
}	//PS_FW

#endif //__PS_FW_MSG_QUEUE__
