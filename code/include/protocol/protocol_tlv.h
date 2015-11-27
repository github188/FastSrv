/*
//
//	Last Modify Date: 2015-11-06
//	Author: zengpw
//	History:
//					2015-08-24 zengpw created
//	File Property: public
//	Future:
//					I. 协议
//
//
*/

#ifndef _PROTOCOL_TLV_H_
#define _PROTOCOL_TLV_H_

#include <sys/time.h>
#include "common/log.h"
#include "common/util.h"
#include "putil.h"
#include "protocol_tlv_sys.h"
#include "protocol_tlv_data.h"

using namespace std;
using namespace protocol::tlv;

namespace protocol
{
	class PacketIn
	{
	public:
		//读取数据缓冲区设置为最大 10KB
		char data[10240];
		unsigned int len;
	public:
		tlv::HeadPtr ptrHead;
		tlv::TLVGroup vecTLV;
		unsigned short* crc;
	public:
		int buildFromString(const char* value, const unsigned int len);
		PacketIn();
	public:
		char* setHead();
		char* setBody();
		int parseHead();
		int parseBody();
	public:
		void printDetail();
		const char* getMsg() const;
		unsigned short getMsgLen() const;
		string getDevId() const;
		unsigned short getCID() const;
		long int getTime() const;
		TLVGroupPtr getTLVGroup() const;
	};


	class PacketOut
	{
	public:
		char data[10480];
		unsigned int len;
	public:
		char tlvCache[10240];
		unsigned int tlvLen;
	public:
		tlv::HeadPtr ptrHead;
		tlv::TLVGroup vecTLV;
		unsigned short crc;
	public:
		PacketOut();
	public:
		void copy(const PacketIn* pi);
		int add(char type, int len, char* value = NULL);
		void build();
	public:
		void setDevId(string dev_id);
		void setCID(unsigned short cid);
		void setTimeNow();
	public:
		void printDetail();
		const char* getMsg() const;
		unsigned short getMsgLen() const;
		string getDevId() const;
		unsigned short getCID() const;
	};
};// namespace protocol

#endif