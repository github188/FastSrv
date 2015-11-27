/*
//
//	Last Modify Date: 2015-11-06
//	Author: zengpw
//	History:
//					2015-09-09 zengpw created
//	File Property: public
//	Future:
//					I. 基于 google protocol buffer 协议
//
//
*/

#ifndef _PROTOCOL_PB_H_
#define _PROTOCOL_PB_H_

#include "common/log.h"
#include "common/util.h"
#include "protocol_pb_sys.h"
#include "protocol_pb_heartbeat.pb.h"
#include "putil.h"

using namespace std;

namespace protocol
{
	namespace pb
	{
		class PacketPB
		{
		public:
			//读取数据缓冲区设置为最大 10KB
			char data[10240];
			int len;
		public:
			HeadPtr ptrHead;
			unsigned short crc;
		public:
			char* setHead();
			char* setBody(unsigned int length);
			int parseHead();
			int parseBody(string& strPb);
		public:
			void build(string& strPb, unsigned int length);
		public:
			const char* getMsg();
			unsigned int getMsgLen();
		public:
			void printDetail();
		};
	}// namespace pb
};// namespace protocol

#endif