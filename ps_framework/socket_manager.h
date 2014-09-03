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
//					IV. ThreadManager 类负责观察 SocketManager ，当新的连接到来时，就新建线程处理
//
//
////////////////////////////////////////////////////////////////////////////////////////

#include "sys_include.h"
#include "channel.h"
#include "subject.h"
#include "observer.h"

namespace PS_FW
{
	typedef int SocketId;
	typedef int SocketStatus;
	typedef std::list<SocketId> SocketList;
	typedef std::map<SocketId,SocketStatus> SocketMap;

	class SocketManager : public Observer,public Subject
	{
	public:
		SocketManager(Channel* pChannel);
		virtual ~SocketManager();
	public:
		virtual void Update(Subject* pSubject);
		/* 目前只提供入池方法 */
		int push(int sockId);
		/* 提供给主线程获取连接 */
		int getNewSock(int& sockId);
	private:
		Channel* m_pChannel;
		/* 管理的 socket */
		SocketMap* m_pMapSocket;
		/* 还未建立连接的 socket */
		SocketList* m_pListSocket;
		/* 锁 */
		pthread_mutex_t m_mxMapLock;
		pthread_mutex_t m_mxListLock;
	};
}	//PS_FW

#endif //__PS_FW_SOCKET_MANAGER__
