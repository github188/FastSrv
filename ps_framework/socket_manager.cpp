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

#include "socket_manager.h"

namespace PS_FW
{
	SocketManager::SocketManager(Channel* pChannel)
	{
		m_pMapSocket = new SocketMap;
		m_pListSocket = new SocketList;

		if(pthread_mutex_init(&m_mxMapLock,NULL))
		{
			delete m_pMapSocket;
		}

		if(pthread_mutex_init(&m_mxListLock,NULL))
		{
			delete m_pListSocket;
		}

		m_pChannel = pChannel;
		m_pChannel->Attach(this);
	}

	SocketManager::~SocketManager()
	{
		m_pChannel->Detach(this);
		delete m_pMapSocket;
		delete m_pListSocket;

		pthread_mutex_destroy(&m_mxMapLock);
		pthread_mutex_destroy(&m_mxListLock);
	}


	void SocketManager::Update(Subject* pSubject)
	{
		if(m_pChannel == pSubject)
		{
			//如果被观察的 Channel 发送了通知
			printf("[PS_FW::SocketManager]: receive notify from channel ! ");
			this->push(m_pChannel->m_sockP);
		}
	}


	int SocketManager::push(int sockId)
	{
		pthread_mutex_lock(&m_mxMapLock);
		m_pMapSocket->insert(std::make_pair(sockId,0));
		pthread_mutex_unlock(&m_mxMapLock);

		pthread_mutex_lock(&m_mxListLock);
		m_pListSocket->push_back(sockId);
		pthread_mutex_unlock(&m_mxListLock);

		//通知观察者，取走最新的 socket
		Notify();

		return 0;
	}


	int SocketManager::getNewSock(int& sockId)
	{
		pthread_mutex_lock(&m_mxListLock);
		if(!m_pListSocket->empty())
		{
			sockId = m_pListSocket->front();
			m_pListSocket->pop_front();
		}
		else
		{			
			pthread_mutex_unlock(&m_mxListLock);
			return -1;
		}
		pthread_mutex_unlock(&m_mxListLock);

		return 0;
	}
}	//PS_FW

