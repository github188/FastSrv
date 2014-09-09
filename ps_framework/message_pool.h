#ifndef __PS_FW_MESSAGE_POOL__
#define __PS_FW_MESSAGE_POOL__
////////////////////////////////////////////////////////////////////////////////////////
//
//	Creater : zengpw
//	Create Date : 2014年8月21日
//	Modify history :
//					2014年8月21日 zengpw 重新设计
//					2014年9月9日 zengpw 重新设计
//	File Property : private
//	Description :
//				I. 消息队列头文件
//				III. 目前我们采用 v1.3 版的 std::list ，以后会改用 std::queue ，性能会有提升
//				IV. 消息队列会主动通知其处理线程，因此它需要继承自 subject
//
////////////////////////////////////////////////////////////////////////////////////////

#include "sys_include.h"
#include "subject.h"

namespace PS_FW
{
	typedef std::list<void*> Pool;

	class MessagePool : public Subject
	{
	public:
		MessagePool();
		virtual ~MessagePool();
	public:
		int pushByChar(char* szMessage);
		int popByChar(char* szMessage);
	private:
		int push(void* msg);
		int pop(void** msg);
	private:
		Pool* m_pPool;
		//消息池内部锁
		pthread_mutex_t m_mxLock;
	};
}	//PS_FW

#endif //__PS_FW_MESSAGE_POOL__
