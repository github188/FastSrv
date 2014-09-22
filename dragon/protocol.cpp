////////////////////////////////////////////////////////////////////////////////////////
//
//	Creater : zengpw
//	Create Date : 2014年8月21日
//	Modify history :
//					2014年9月9日 zengpw 明确安全要求
//					2014年9月10日 zengpw 修改设计，增加数据初始化接口
//					2014年9月11日 zengpw 现在一个 session 对象会持有一个 protocol 对象
//	File Property : public
//	Description :	
//					I. 控制数据，编写数据交互规则
//					II. 要求是线程安全的
//					III. protocol 的输入输出都是字符串
//					IV. protocol 可以缓存部分数据
//					V. protocol的 virtual 函数都是基于字符串处理的
//	Future :
//					I. 优化缓冲区算法
//
//
////////////////////////////////////////////////////////////////////////////////////////

#include "sys_include.h"
#include "_protocol.h"

namespace PS_FW
{
	Protocol::Protocol()
	{
		m_pos = 0;
		memset(m_szDataA,'\0',30960);
		memset(m_szDataB,'\0',30960);
		m_pData = m_szDataA;
		m_pDataNext = m_szDataB;
	}


	int Protocol::messageInit(const char* pMessageIn,const int lenIn,char* pMessageOut,int& lenOut)
	{
		int flag = 0;
		int pos = 0;

		//清空输出
		memcpy(pMessageOut,'\0',lenOut);
		//写本地缓冲区
		memcpy(m_pData + m_pos,pMessageIn,lenIn);
		m_pos += lenIn;
		// flag 取值： 1（整包） || 2（整包 + 部分包） || 3（部分包） || 4（错误包）
		// pos 当 flag = 2 时，返回 包偏移地址
		this->verifyPacket(m_pData,m_pData + m_pos,flag,pos);

		if(flag == 1)
		{
			lenOut = m_pos;
			memcpy(pMessageOut,m_pData,lenOut);
			/* 最简单的情况，清空当前数据区，将缓存的位移置0 */
			memset(m_pData,'\0',30960);
			m_pos = 0;
		}
		else if (flag == 2)
		{
			lenOut = pos;
			memcpy(pMessageOut,m_pData,lenOut);
			/* 将当前数据区数据未读取的部分，存储到 Next 数据区，然后 Current 和 Next 指针交换 */
			/* Next 数据区将在下次发生交换时被清空 */
			memset(m_pDataNext,'\0',30960);
			memcpy(m_pDataNext,m_pData + pos,m_pos - pos);
			char* m_pDataTemp = m_pData;
			m_pData = m_pDataNext;
			m_pDataNext = m_pDataTemp;
			m_pos -= pos;
		}
		else if (flag == 3)
		{
			lenOut = 0;
		}
		else if (flag == 4)
		{
			/* 将缓存的位移置0，并清空所有缓冲区 */
			m_pos = 0;
			memset(m_pData,'\0',30960);
			memset(m_pDataNext,'\0',30960);
			lenOut = 0;
		}
		else
		{
			/* 实际上不允许发生 */
			m_pos = 0;
			memset(m_pData,'\0',30960);
			memset(m_pDataNext,'\0',30960);
			lenOut = 0;
		}

		return 0;
	}


	int Protocol::verifyPacket(const char* szBegin,const char* szEnd,int& flag,int& pos)
	{
		/* 在协议的基类里，所有包都是完整包 */
		flag = 1;

		return 0;
	}
}	//PS_FW
