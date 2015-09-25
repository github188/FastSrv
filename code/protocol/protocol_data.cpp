/*
//
//	Last Modify Date: 2015-09-24
//	Author: zengpw
//	History:
//					2015-09-24 zengpw created
//	File Property: public
//	Future:
//					I. 协议的一部分
//
//
*/


#include "protocol_data.h"
#include "protocol_data_head.h"
#include "protocol_data_tlv.h"

namespace protocol
{
	namespace data
	{
		DateTimePtr cDateTime(char year, char mon, char day, char hour, char min, char sec)
		{
			DateTimePtr p = new DateTime;

			p->year = year;
			p->mon = mon;
			p->day = day;
			p->hour = hour;
			p->min = min;
			p->sec = sec;
		}
	}// namespace data
};// namespace protocol