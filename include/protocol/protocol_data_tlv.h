/*
//
//	Last Modify Date: 2015-08-28
//	Author: zengpw
//	History:
//					2015-08-24 zengpw created
//	File Property: public
//	Future:
//					I. 协议的一部分
//
//
*/

#ifndef _PROTOCOL_DATA_TLV_H_
#define _PROTOCOL_DATA_TLV_H_

#include <vector>

using namespace std;

namespace protocol
{
	namespace data
	{
		typedef struct TLV
		{
			char type;
			char len;
			char* value;

			TLV()
			{
				value = NULL;
			}
		}TLV;
		typedef TLV* TLVPtr;
		typedef vector<TLV> TLVVec;
		typedef vector<TLVPtr> TLVPtrVec;
	}// namespace data
};// namespace protocol

#endif