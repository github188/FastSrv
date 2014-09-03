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

#include "connection_manager.h"

namespace PS_FW
{
	ConnectionManager::ConnectionManager(SocketManager* pSocketManager)
	{
		if(pthread_mutex_init(&m_mxLock,NULL) == 0)
		{
			m_pSocketManager = pSocketManager;
			m_pSocketManager->Attach(this);
		}
	}

	ConnectionManager::~ConnectionManager()
	{
		m_pSocketManager->Detach(this);

		pthread_mutex_destroy(&m_mxLock);
	}


	void ConnectionManager::Update(Subject* pSubject)
	{
		if(m_pSocketManager == pSubject)
		{
			// when new socket coming
			printf("[PS_FW::ThreadManager]: receive socket from socketmanager ! ");
			int sockId = 0;
			if(m_pSocketManager->getNewSock(sockId) == 0)
			{
				printf("[PS_FW::ThreadManager]: receive socket ok ! ");
			}
		}
	}
}	//PS_FW

