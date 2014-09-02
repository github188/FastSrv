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

#include "socket_manager.h"

namespace PS_FW
{
	SocketManager::SocketManager(Channel* pChannel)
	{
		m_pMapSocket = new SocketMap;

		if(pthread_mutex_init(&m_mxLock,NULL))
		{
			delete m_pMapSocket;
		}
		else
		{
			m_pChannel = pChannel;
			m_pChannel->Attach(this);
		}
	}

	SocketManager::~SocketManager()
	{
		m_pChannel->Detach(this);
		delete m_pMapSocket;

		pthread_mutex_destroy(&m_mxLock);
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


	int SocketManager::push(SocketId socketId)
	{
		pthread_mutex_lock(&m_mxLock);
		//TODO 通知 app 类创建 读取、处理 线程
		pthread_mutex_unlock(&m_mxLock);

		return 0;
	}
}	//PS_FW

