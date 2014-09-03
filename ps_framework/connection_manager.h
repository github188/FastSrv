#ifndef __PS_FW_CONNECTION_MANAGER__
#define __PS_FW_CONNECTION_MANAGER__
////////////////////////////////////////////////////////////////////////////////////////
//
//	Creater : zengpw
//	Create Date : 2014年9月3日
//	Modify history :
//					2014年9月3日 zengpw 连接管理
//	File Property : private
//	Description :
//					I.这个类的对象的生命周期是全局的，随着进程退出而消亡
//					II.它是 SocketManager 类的观察者
//
//
////////////////////////////////////////////////////////////////////////////////////////

#include "sys_include.h"
#include "socket_manager.h"
#include "observer.h"

namespace PS_FW
{
	class ConnectionManager : public Observer
	{
	public:
		ConnectionManager(SocketManager* pSocketManager);
		virtual ~ConnectionManager();
	public:
		virtual void Update(Subject* pSubject);
	private:
		SocketManager* m_pSocketManager;
		pthread_mutex_t m_mxLock;
	};
}	//PS_FW

#endif //__PS_FW_CONNECTION_MANAGER__
