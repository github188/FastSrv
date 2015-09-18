/*
//
//	Last Modify Date: 2015-09-18
//	Author: zengpw
//	History:
//					2015-09-15 zengpw created
//	File Property: public
//	Future:
//					I. TLV 公共消息处理
//
//
*/

#include "session_handle.h"

namespace session
{
	bool SessionHandle::dispatch(const protocol::Packet* in, protocol::Packet* out)
	{
		out->copyHead(in);

		if(in->ptrHead->command_id == protocol::data::MSG_CUTOVER)
		{
			return msg_cutover(in, out);
		}

		if(in->ptrHead->command_id == protocol::data::MSG_TIME)
		{
			return msg_time(in, out);
		}

		if(in->ptrHead->command_id == protocol::data::MSG_UPLOAD)
		{
			return msg_upload(in, out);
		}

		return false;
	}


	bool SessionHandle::msg_cutover(const protocol::Packet* in, protocol::Packet* out)
	{
		return false;
	}


	bool SessionHandle::msg_time(const protocol::Packet* in, protocol::Packet* out)
	{
		out->ptrHead->command_id = protocol::data::MSG_TIME_REP;

		protocol::data::TLVPtrVec::const_iterator iter = in->vecTLVPtr.begin();

		for(; iter != in->vecTLVPtr.end(); iter++)
		{
			if((*iter)->type == 1)
			{
				//数据包里的时间
				struct tm st;
				st.tm_year = (*iter)->value[0] + 100;
				st.tm_mon = (*iter)->value[1] - 1;
				st.tm_mday = (*iter)->value[2];
				st.tm_hour = (*iter)->value[3];
				st.tm_min = (*iter)->value[4];
				st.tm_sec = (*iter)->value[5];
				st.tm_isdst = -1;

				char buf[64];
				memset(buf,0,sizeof(buf));
				strftime(buf, sizeof(buf), "%Y %m %d %H %M %S", &st);
				printf("\n COMMAND : MSG_LOGIN \n TYTPE : 1 \n VALUE(YYYYMMDDHH24MISS) : %s \n", buf);

				time_t tt = mktime(&st);
				printf("\n OFFSET TIME - CLIENT(S) : %ld \n", tt);

				//生成本地时间
				struct timeval tv;
				gettimeofday(&tv, NULL);

				struct tm* pst;
				pst = localtime(&tv.tv_sec);

				memset(buf,0,sizeof(buf));
				strftime(buf, sizeof(buf), "%Y %m %d %H %M %S", pst);
				printf("\n LOCAL TIME(YYYYMMDDHH24MISS) : %s \n", buf);
				printf("\n OFFSET TIME - SERVER(S) : %ld \n", tv.tv_sec);

				//大于一定时间就发送时间包
				time_t time_diff = abs(tt - tv.tv_sec);
				printf("\n abs(CLIENT - SERVER) : %ld \n", time_diff);

				if(time_diff > 10)
				{
					printf("\n push time packet to client \n");

					// type = 1 , 时间报文
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

		out->setCRC();

		return true;
	}


	bool SessionHandle::msg_upload(const protocol::Packet* in, protocol::Packet* out)
	{
		return false;
	}
};// namespace session