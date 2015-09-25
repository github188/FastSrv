/*
//
//	Last Modify Date: 2015-09-25
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
	SESSION_RTN SessionHandle::dispatch(const protocol::Packet* in, protocol::Packet* out)
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

		return SESSION_RTN_CONTINUE;
	}


	SESSION_RTN SessionHandle::conn(protocol::Packet* out)
	{
		return SESSION_RTN_CONTINUE;
	}


	SESSION_RTN SessionHandle::msg_cutover(const protocol::Packet* in, protocol::Packet* out)
	{
		return SESSION_RTN_CONTINUE;
	}


	SESSION_RTN SessionHandle::msg_time(const protocol::Packet* in, protocol::Packet* out)
	{
		out->ptrHead->command_id = protocol::data::MSG_TIME_REP;

		protocol::data::TLVPtrVec::const_iterator iter = in->vecTLVPtr.begin();

		for(; iter != in->vecTLVPtr.end(); iter++)
		{
			if((*iter)->type == protocol::data::DATA_UPLOAD_TIME)
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

				LOG_DEBUG("COMMAND : MSG_TIME ");
				LOG_DEBUG("COMMAND : TYPE = 1 ");
				LOG_DEBUG("COMMAND : VALUE = " << buf);

				time_t tt = mktime(&st);

				LOG_DEBUG("OFFSET TIME - CLIENT(S) : " << tt);

				//生成本地时间
				struct timeval tv;
				gettimeofday(&tv, NULL);

				struct tm* pst;
				pst = localtime(&tv.tv_sec);

				memset(buf,0,sizeof(buf));
				strftime(buf, sizeof(buf), "%Y %m %d %H %M %S", pst);

				LOG_DEBUG("LOCAL TIME : " << buf);
				LOG_DEBUG("OFFSET TIME - SERVER(S) : " << tv.tv_sec);

				//大于一定时间就发送时间包
				time_t time_diff = abs(tt - tv.tv_sec);

				LOG_DEBUG("abs(CLIENT - SERVER) : " << time_diff);

				if(time_diff > 10)
				{
					LOG_DEBUG("push time packet to client");

					// 发送时间
					protocol::data::DateTimePtr ptrDateTime = protocol::data::cDateTime(pst->tm_year - 100, pst->tm_mon + 1, pst->tm_mday, pst->tm_hour, pst->tm_min, pst->tm_sec);
					out->setTLV(protocol::data::DATA_SENDING_TIME, sizeof(protocol::data::DateTime), (char*)ptrDateTime);
				}
			}
		}

		out->setCRC();

		return SESSION_RTN_SEND;
	}


	SESSION_RTN SessionHandle::msg_upload(const protocol::Packet* in, protocol::Packet* out)
	{
		return SESSION_RTN_CONTINUE;
	}
};// namespace session