#ifndef __PS_FW_SOCKET_MANAGER__
#define __PS_FW_SOCKET_MANAGER__
////////////////////////////////////////////////////////////////////////////////////////
//
//	Creater : zengpw
//	Create Date : 2014年9月2日
//	Modify history :
//					2014年9月2日 zengpw 用于管理成功建立的 socket
//	File Property : private
//	Description :
//					I.必须是线程安全的
//					II.这个类的对象的生命周期是全局的，随着进程退出而消亡
//					III.它是 Channel 类的观察者（仅观察建立连接的 Channel）
//
//
////////////////////////////////////////////////////////////////////////////////////////

#include "sys_include.h"
#include "channel.h"
#include "observer.h"

namespace PS_FW
{
	typedef int SocketId;
	typedef int SocketStatus;
	typedef std::map<SocketId,SocketStatus> SocketMap;

	class SocketManager : public Observer
	{
	public:
		SocketManager(Channel* pChannel);
		virtual ~SocketManager();
	public:
		virtual void Update(Subject* pSubject);
		/* 目前只提供入池方法 */
		int push(SocketId socketId);
	private:
		Channel* m_pChannel;
		SocketMap* m_pMapSocket;
		pthread_mutex_t m_mxLock;
	};
}	//PS_FW

#endif //__PS_FW_SOCKET_MANAGER__
