/*
//
//	Last Modify Date: 2015-11-12
//	Author: zengpw
//	History:
//					2015-08-24 zengpw created
//	File Property: public
//	Future:
//					I. 协议
//
//
*/

#include "protocol_tlv.h"

namespace protocol
{
	PacketIn::PacketIn()
	{
		len = 0;
		memset(data, 0, sizeof(data));
	}


	int PacketIn::buildFromString(const char* value, const unsigned int len)
	{
		memcpy(data, value, len);
		parseHead();
		parseBody();

		return 0;
	}


	char* PacketIn::setHead()
	{
		return data;
	}


	char* PacketIn::setBody()
	{
		return data + sizeof(tlv::Head);
	}


	int PacketIn::parseHead()
	{
		LOG_DEBUG("parseHead : size = " << sizeof(tlv::Head) << ", context = " << common::printByHex(data, sizeof(tlv::Head)));

		ptrHead = (tlv::HeadPtr)data;
		len = sizeof(tlv::Head);

		if (ptrHead->xcode[0] != 0xF1 || ptrHead->xcode[1] != 0xE2 || ptrHead->xcode[2] != 0xD3 || ptrHead->xcode[3] != 0xC4)
		{
			return -1;
		}

		return ptrHead->len;
	}


	int PacketIn::parseBody()
	{
		LOG_DEBUG("parseBody : size = " << ptrHead->len << ", context = " << common::printByHex(data + sizeof(tlv::Head), ptrHead->len));

		len += ptrHead->len;
		unsigned int index = sizeof(tlv::Head);
		unsigned int end = len - sizeof(unsigned short);

		// TLV 组限制，超过 100 组则返回错误
		LOG_DEBUG("decode begin : index = " << index << ", end = " << end);
		int grp = 0;

		//不能使用 <= ，因为会多计算一组数据
		while(index < end)
		{
			LOG_DEBUG("decoding..... : index = " << index << ", end = " << end);

			tlv::TLV t;

			t.type = data[index++];
			t.len = data[index++];
			t.value = &data[index];

			if(t.len < 0)
			{
				return -1;
			}

			index += t.len;
			vecTLV.push_back(t);

			if(++grp > 100)
			{
				return -1;
			}
		}

		crc = (unsigned short*)&data[index];

		if(*crc != protocol::createCRC(data, len - sizeof(unsigned short)))
		{
			LOG_DEBUG("decoding..... : crc verify error!");
			return -1;
		}

		printDetail();

		return 0;
	}


	void PacketIn::printDetail()
	{
		LOG_DEBUG("All : size = " << len << ", context = " << common::printByHex(data, len));
		LOG_DEBUG("Head : size = " << sizeof(tlv::Head) << ", context = " << common::printByHex((char*)ptrHead, sizeof(tlv::Head)));
		LOG_DEBUG("TLV group : size = " << vecTLV.size());
		for(unsigned int i = 0; i < vecTLV.size(); i++)
		{
			LOG_DEBUG("tlv type : 0x" << common::printByHex(&vecTLV[i].type, 1));
			LOG_DEBUG("tlv len : 0x" << common::printByHex(&vecTLV[i].len, 1));
			LOG_DEBUG("tlv value : size = " << (int)vecTLV[i].len << ", context = " << common::printByHex(vecTLV[i].value, (int)vecTLV[i].len));
		}
		LOG_DEBUG("CRC : " << common::printByHex((char*)crc, sizeof(unsigned short)));
	}


	const char* PacketIn::getMsg() const
	{
		return data;
	}


	unsigned short PacketIn::getMsgLen() const
	{
		return len;
	}


	string PacketIn::getDevId() const
	{
		string dev_id = "";
		dev_id.assign((char*)ptrHead->dev_id, 12);

		return dev_id;
	}


	unsigned short PacketIn::getCID() const
	{
		return ptrHead->cid;
	}


	long int PacketIn::getTime() const
	{
		return ptrHead->build_time;
	}


	TLVGroupPtr PacketIn::getTLVGroup() const
	{
		return &vecTLV;
	}


	PacketOut::PacketOut()
	{
		memset(data, 0, sizeof(data));

		ptrHead = (tlv::HeadPtr)data;

		ptrHead->xcode[0] = 0xF1;
		ptrHead->xcode[1] = 0xE2;
		ptrHead->xcode[2] = 0xD3;
		ptrHead->xcode[3] = 0xC4;

		len = sizeof(tlv::Head);
		tlvLen = 0;
	}


	void PacketOut::copy(const PacketIn* pi)
	{
		memcpy(ptrHead, pi->ptrHead, sizeof(tlv::Head));
	}


	int PacketOut::add(char type, int length, char* value)
	{
		if(value == NULL)
		{
			return -1;
		}

		tlv::TLV t;

		memcpy(tlvCache + tlvLen, (char*)&type, 1);
		t.type = tlvCache[tlvLen];
		tlvLen++;

		memcpy(tlvCache + tlvLen, (char*)&length, 1);
		t.len = tlvCache[tlvLen];
		tlvLen++;

		memcpy(tlvCache + tlvLen, value, length);
		t.value = &tlvCache[tlvLen];
		tlvLen += length;

		vecTLV.push_back(t);

		return 0;
	}


	void PacketOut::build()
	{
		setTimeNow();

		memcpy(data + len, tlvCache, tlvLen);
		len += tlvLen;

		//长度必须要在计算 CRC 前面赋值，否则影响收到包以后的 CRC 校验
		//长度 = (Head + Body) - Head + CRC
		ptrHead->len = len - sizeof(tlv::Head) + sizeof(crc);

		//计算 CRC 时，计算的是 Head + Body 的 CRC
		crc = protocol::createCRC(data, len);
		memcpy(data + len, (char*)&crc, sizeof(crc));
		len += sizeof(crc);

		LOG_DEBUG("[hint] message build complete ");
		printDetail();
	}


	void PacketOut::setDevId(string dev_id)
	{
		memcpy(ptrHead->dev_id, dev_id.c_str(), dev_id.length() > 12 ? 12 : dev_id.length());
	}


	void PacketOut::setCID(unsigned short cid)
	{
		ptrHead->cid = cid;
	}


	void PacketOut::setTimeNow()
	{
		struct timeval tv;
		gettimeofday(&tv, NULL);

		ptrHead->build_time = tv.tv_sec;
	}


	void PacketOut::printDetail()
	{
		LOG_DEBUG("All : size = " << len << ", context = " << common::printByHex(data, len));
		LOG_DEBUG("Head : size = " << sizeof(tlv::Head) << ", context = " << common::printByHex((char*)ptrHead, sizeof(tlv::Head)));
		LOG_DEBUG("TLV group : size = " << vecTLV.size());
		for(unsigned int i = 0; i < vecTLV.size(); i++)
		{
			LOG_DEBUG("tlv type : 0x" << common::printByHex(&vecTLV[i].type, 1));
			LOG_DEBUG("tlv len : 0x" << common::printByHex(&vecTLV[i].len, 1));
			LOG_DEBUG("tlv value : size = " << (int)vecTLV[i].len << ", context = " << common::printByHex(vecTLV[i].value, (int)vecTLV[i].len));
		}
		LOG_DEBUG("CRC : " << common::printByHex((char*)&crc, sizeof(crc)));
	}


	const char* PacketOut::getMsg() const
	{
		return data;
	}


	unsigned short PacketOut::getMsgLen() const
	{
		return len;
	}


	string PacketOut::getDevId() const
	{
		string dev_id = "";
		dev_id.assign((char*)ptrHead->dev_id, 12);

		return dev_id;
	}


	unsigned short PacketOut::getCID() const
	{
		return ptrHead->cid;
	}
};// namespace protocol
