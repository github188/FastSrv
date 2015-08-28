/*
//
//	Last Modify Date: 2015-08-26
//	Author: zengpw
//	History:
//					2015-08-26 zengpw created
//	File Property: public
//	Future:
//					I. 消息处理（不涉及网络）
//
//
*/

#include "balance_handle.h"

void BalanceHandle::dispatch(const protocol::Packet* in, protocol::Packet* out)
{
	out->copyHead(in);

	if(in->ptrHead->command_id == protocol::data::MSG_LOGIN)
	{
		msgLogin(in, out);
	}

	if(in->ptrHead->command_id == protocol::data::MSG_CONNECT_CUTOVER)
	{
		msgCutover(in, out);
	}
}


void BalanceHandle::msgLogin(const protocol::Packet* in, protocol::Packet* out)
{
	out->ptrHead->command_id = protocol::data::MSG_LOGIN + 0x8000;

	if(in->vecTLVPtr.size() > 0)
	{
		if(in->vecTLVPtr[0]->type == 1)
		{
			// zengpw, 数据包里的时间
			struct tm st;
			st.tm_year = in->vecTLVPtr[0]->value[0] + 100;
			st.tm_mon = in->vecTLVPtr[0]->value[1] - 1;
			st.tm_mday = in->vecTLVPtr[0]->value[2];
			st.tm_hour = in->vecTLVPtr[0]->value[3];
			st.tm_min = in->vecTLVPtr[0]->value[4];
			st.tm_sec = in->vecTLVPtr[0]->value[5];
			st.tm_isdst = -1;

			char buf[64];
			memset(buf,0,sizeof(buf));
			strftime(buf, sizeof(buf), "%Y %m %d %H %M %S", &st);
			printf("\n COMMAND : MSG_LOGIN \n TYTPE : 1 \n VALUE(YYYYMMDDHH24MISS) : %s\n", buf);

			time_t tt = mktime(&st);
			printf("\n OFFSET TIME - CLIENT(S) : %ld\n", tt);

			// zengpw, 生成本地时间
			struct timeval tv;
			gettimeofday(&tv, NULL);

			struct tm* pst;
			pst = localtime(&tv.tv_sec);

			memset(buf,0,sizeof(buf));
			strftime(buf, sizeof(buf), "%Y %m %d %H %M %S", pst);
			printf("\n LOCAL TIME(YYYYMMDDHH24MISS) : %s\n", buf);
			printf("\n OFFSET TIME - SERVER(S) : %ld\n", tv.tv_sec);

			// zengpw, 大于一定时间就发送时间包
			time_t time_diff = abs(tt - tv.tv_sec);
			printf("\n abs(CLIENT - SERVER) : %ld\n", time_diff);

			if(time_diff > 10)
			{
				printf("\n push time packet to client \n");

				protocol::data::TLVPtr ptrTLV = out->setTLV(1, 6);

				ptrTLV->value[0] = pst->tm_year - 100;
				ptrTLV->value[1] = pst->tm_mon + 1;
				ptrTLV->value[2] = pst->tm_mday;
				ptrTLV->value[3] = pst->tm_hour;
				ptrTLV->value[4] = pst->tm_min;
				ptrTLV->value[5] = pst->tm_sec;
			}
		}
	}

	string key = protocol::createKey();
	protocol::data::TLVPtr ptrTLV = out->setTLV(2, key.length());
	memcpy(ptrTLV->value, key.c_str(), key.length());

	out->setCRC();
}


void BalanceHandle::msgCutover(const protocol::Packet* in, protocol::Packet* out)
{
}
