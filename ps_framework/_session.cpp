////////////////////////////////////////////////////////////////////////////////////////
//
//	Creater : zengpw
//	Create Date : 2014年9月3日
//	Modify history :
//					2014年9月3日 zengpw 创建
//					2014年9月9日 zengpw 增加消息处理循环，提供接口
//	File Property : private
//	Description :
//					I. 控制连接，编写交互规则
//					II. session 要做到线程安全
//
//
////////////////////////////////////////////////////////////////////////////////////////

#include "sys_include.h"
#include "_session.h"

namespace PS_FW
{
	int Session::setMessageIn(const char* pMessageIn)
	{
		memset(m_szMessageIn,'\0',10240);
		strncpy(m_szMessageIn,pMessageIn,10240);

		return 0;
	}


	int Session::dealMessage()
	{
		memset(m_szMessageOut,'\0',10240);

		char szType[64];

		if (getMessageType(szType) == 0)
		{
			if (strncmp(szType,"PS_FW_LOGON",strlen("PS_FW_LOGON")) == 0)
			{
				dealLogon();
			}
			else if (strncmp(szType,"PS_FW_LOGOUT",strlen("PS_FW_LOGOUT")) == 0)
			{
				dealLogout();
			}
			else
			{
				printf("\n[PS_FW::Session]: unknown message type ! \n");
			}
		}

		return 0;
	}


	int Session::getMessageOut(char* pMessageOut,int len)
	{
		strncpy(pMessageOut,m_szMessageOut,10240);
		len = strlen(m_szMessageOut);

		return 0;
	}


	int Session::getMessageType(char* szType)
	{
		memset(szType,'\0',64);

		if (strncmp(m_szMessageIn,"ps_framework logon",strlen("ps_framework logon")) == 0)
		{
			printf("\n[PS_FW::Session]: request logon message ! \n");
			strncpy(szType,"PS_FW_LOGON",strlen("PS_FW_LOGON"));

			return 0;
		}

		if (strncmp(m_szMessageIn,"ps_framework logout",strlen("ps_framework logout")) == 0)
		{
			printf("\n[PS_FW::Session]: request logout message ! \n");
			strncpy(szType,"PS_FW_LOGOUT",strlen("PS_FW_LOGOUT"));

			return 0;
		}

		return 0;
	}


	int Session::dealLogon()
	{
		strncpy(m_szMessageOut,"allow logon",10240);

		return 0;
	}


	int Session::dealLogout()
	{
		//TODO : DISCONNECTION

		return 0;
	}
}	//PS_FW

