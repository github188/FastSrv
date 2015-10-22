/*
//
//	Last Modify Date: 2015-10-22
//	Author: zengpw
//	History:
//					2015-09-24 zengpw created
//	File Property: public
//	Future:
//					I. tlv 子协议结构
//
//
*/

#include "protocol_tlv_data.h"

namespace protocol
{
	namespace tlv
	{
		//公共结构体 - 时间
		DateTime buildDateTime2k()
		{
			struct timeval tv;
			gettimeofday(&tv, NULL);

			struct tm* pst;
			pst = localtime(&tv.tv_sec);

			DateTime dt;

			dt.year = pst->tm_year - 100;
			dt.mon = pst->tm_mon + 1;
			dt.day = pst->tm_mday;
			dt.hour = pst->tm_hour;
			dt.min = pst->tm_min;
			dt.sec = pst->tm_sec;

			return dt;
		}

		DateTime buildDateTime(char year, char mon, char day, char hour, char min, char sec)
		{
			DateTime dt;

			dt.year = year;
			dt.mon = mon;
			dt.day = day;
			dt.hour = hour;
			dt.min = min;
			dt.sec = sec;

			return dt;
		}

		void printDateTime2k(DateTime& dt)
		{
			char buf[36];
			memset(buf, 0, sizeof(buf));
			sprintf(buf, "DateTime = 20%02d%02d%02d%02d%02d%02d", dt.year, dt.mon, dt.day, dt.hour, dt.min, dt.sec);
			LOG_DEBUG(buf);
		}

		string DateTime2String2k(DateTime& dt)
		{
			string sdt;

			char buf[36];
			memset(buf, 0, sizeof(buf));
			sprintf(buf, "20%02d%02d%02d%02d%02d%02d", dt.year, dt.mon, dt.day, dt.hour, dt.min, dt.sec);

			stringstream ss;

			ss << buf;
			sdt = ss.str();
			ss.str("");
			ss.clear();

			return sdt;
		}
	}// namespace tlv
};// namespace protocol