/*
//
//	Last Modify Date: 2015-10-16
//	Author: zengpw
//	History:
//					2015-09-09 zengpw created
//	File Property: public
//	Future:
//					I. 基于 google protocol buffer 协议
//
//
*/

#ifndef _PROTOCOL_PB_SYS_H_
#define _PROTOCOL_PB_SYS_H_

using namespace std;

namespace protocol
{
	namespace pb
	{
		#pragma pack(push, 1)

		typedef struct Head
		{
			unsigned char	xcode[3];
			unsigned short	len;
		}Head;
		typedef Head* HeadPtr;

		#pragma pack(pop)
	}// namespace pb
};// namespace protocol

#endif