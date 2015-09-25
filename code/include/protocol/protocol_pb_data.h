/*
//
//	Last Modify Date: 2015-09-10
//	Author: zengpw
//	History:
//					2015-09-09 zengpw created
//	File Property: public
//	Future:
//					I. 协议的一部分
//
//
*/

#ifndef _PROTOCOL_PB_DATA_H_
#define _PROTOCOL_PB_DATA_H_

using namespace std;

namespace protocol
{
	namespace pb
	{
		enum MSG_PB
		{
			PB_HEARTBEAT = 0x01
		};

		// head
		typedef struct Head
		{
			unsigned char	xcode[4];
			unsigned short	len;
			unsigned char	name;
		}Head;
		typedef Head* HeadPtr;

		// protobuf field
		typedef char* PBPtr;

		// crc
		typedef unsigned short CRC;
		typedef CRC* CRCPtr;
	}// namespace pb
};// namespace protocol

#endif