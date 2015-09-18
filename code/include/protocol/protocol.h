/*
//
//	Last Modify Date: 2015-09-17
//	Author: zengpw
//	History:
//					2015-08-24 zengpw created
//	File Property: public
//	Future:
//					I. 协议
//
//
*/

#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_

#include <vector>
#include "putil.h"
#include "protocol_data_head.h"
#include "protocol_data_tlv.h"

using namespace std;

namespace protocol
{
	typedef unsigned int Pos;
	typedef vector<Pos> PosVec;

	class PacketBuffer
	{
	public:
		char data[10240];
		PosVec vecPos;
	public:
		PacketBuffer();
	public:
		char* setBuffer(unsigned int length);
	};


	class Packet
	{
	public:
		PacketBuffer* pb;
	public:
		protocol::data::HeadPtr ptrHead;
		protocol::data::TLVPtrVec vecTLVPtr;
		unsigned short* crc;
	public:
		Packet();
		~Packet();
	public:
		char* setBuffer(unsigned int length);
		int parseHead();
		int parse();
		void copyHead(const protocol::Packet* in);
		protocol::data::TLVPtr setTLV(int type, int length);
		char* setCRC();
	public:
		char* raw();
		char* rawTLV();
		unsigned int len();
		unsigned int lenTLV();
		void printTLV();
		void printData();
	};
};// namespace protocol

#endif