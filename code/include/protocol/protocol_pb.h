/*
//
//	Last Modify Date: 2015-09-11
//	Author: zengpw
//	History:
//					2015-09-09 zengpw created
//	File Property: public
//	Future:
//					I. 协议
//
//
*/

#ifndef _PROTOCOL_PB_H_
#define _PROTOCOL_PB_H_

#include "protocol.h"
#include "protocol_pb_data.h"
#include "protocol_pb_heartbeat.pb.h"

using namespace std;

namespace protocol
{
	namespace pb
	{
		class PacketPB
		{
		public:
			protocol::PacketBuffer* pb;
			unsigned int pbSize;
		public:
			protocol::pb::HeadPtr ptrHead;
			protocol::pb::PBPtr ptrPB;
			protocol::pb::CRCPtr ptrCRC;
		public:
			PacketPB();
			~PacketPB();
		public:
			char* setBuffer(unsigned int length);
			int parseHead();
			int parse();
			void getPB(string& in);
		public:
			char* setHead();
			char* setPB(const char* in, unsigned int length);
			char* setCRC();
			char* raw();
			unsigned int len();
			void printData();
		};
	}// namespace pb
};// namespace protocol

#endif