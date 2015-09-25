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

#ifndef _PROTOCOL_DATA_H_
#define _PROTOCOL_DATA_H_

#include <vector>

using namespace std;

namespace protocol
{
	namespace data
	{
		typedef struct DateTime
		{
			char year;
			char mon;
			char day;
			char hour;
			char min;
			char sec;
		}DateTime;
		typedef DateTime* DateTimePtr;
		typedef vector<DateTime> DateTimeVec;
		typedef vector<DateTimePtr> DateTimePtrVec;
		DateTimePtr cDateTime(char year, char mon, char day, char hour, char min, char sec);
	}// namespace data
};// namespace protocol

#endif