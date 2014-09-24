////////////////////////////////////////////////////////////////////////////////////////
//
//	Creater : zengpw
//	Create Date : 2014年9月3日
//	Modify history :
//					2014年9月3日 zengpw 创建
//					2014年9月9日 zengpw 增加消息处理循环，提供接口
//	File Property : public
//	Description :
//					I. 控制连接和数据，编写交互规则
//					II. 要求是线程安全的
//					III. session 的 virtual 函数都是基于事件的，但是会预先对数据做处理
//					IV. session 可以缓存部分数据
//	Future :
//					I. 实现更多基本控制
//					II. 实现一个查找比较快的数据结构
//
//
////////////////////////////////////////////////////////////////////////////////////////

#include "sys_include.h"
#include "_session.h"

namespace PS_FW
{
	Session::Session()
	{
		isStart = 0;
	}


	int Session::init(Protocol* pProtocol)
	{
		if(isStart == 0)
		{
			m_pProtocol = pProtocol;
			m_lenIn = 30960;
			memcpy(m_szMessageIn,'\0',m_lenIn);
			
			m_mapMsgTypeMap.insert(std::make_pair("<logon>1</logon>","PS_FW_LOGON"));
			m_mapMsgTypeMap.insert(std::make_pair("<logout>1</logout>","PS_FW_LOGOUT"));

			if(this->onInitMsgTypeMap(m_mapMsgTypeMap) != 0)
			{
				printf("\n[PS_FW::Session]: onInit fail ! \n");
				return -1;
			}

			isStart = 1;
		}

		return 0;
	}


	void Session::receive(const char* pMessageIn)
	{
		this->m_pProtocol->messageInit(pMessageIn,strlen(pMessageIn),m_szMessageIn,m_lenIn);
		this->onReceive(m_szMessageIn,m_lenIn);
	}
}	//PS_FW

