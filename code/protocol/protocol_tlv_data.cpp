/*
//
//	Last Modify Date: 2015-11-04
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

		DateTimeSec buildDateTimeSec()
		{
			struct timeval tv;
			gettimeofday(&tv, NULL);

			return tv.tv_sec;
		}

		void printDateTimeSec(DateTimeSec& dts)
		{
			LOG_DEBUG("Linux Time(second) : " << dts);

			time_t t = dts;
			struct tm* pst;
			pst = localtime(&t);

			DateTime dt;
			dt.year = pst->tm_year - 100;
			dt.mon = pst->tm_mon + 1;
			dt.day = pst->tm_mday;
			dt.hour = pst->tm_hour;
			dt.min = pst->tm_min;
			dt.sec = pst->tm_sec;

			printDateTime2k(dt);
		}

		string DateTime2StringSec(DateTimeSec& dts)
		{
			time_t t = dts;
			struct tm* pst;
			pst = localtime(&t);

			DateTime dt;
			dt.year = pst->tm_year - 100;
			dt.mon = pst->tm_mon + 1;
			dt.day = pst->tm_mday;
			dt.hour = pst->tm_hour;
			dt.min = pst->tm_min;
			dt.sec = pst->tm_sec;

			return DateTime2String2k(dt);
		}
	}// namespace tlv
};// namespace protocol