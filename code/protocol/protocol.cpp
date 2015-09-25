/*
//
//	Last Modify Date: 2015-09-22
//	Author: zengpw
//	History:
//					2015-08-24 zengpw created
//	File Property: public
//	Future:
//					I. 协议
//
//
*/

#include "protocol.h"

namespace protocol
{
	// class PacketBuffer
	PacketBuffer::PacketBuffer()
	{
		Pos p = 0;
		vecPos.push_back(p);
		memset(data, 0, sizeof(data));
	}


	char* PacketBuffer::setBuffer(unsigned int length)
	{
		Pos p = vecPos.back() + length;
		vecPos.push_back(p);

		return &data[vecPos[vecPos.size() - 2]];
	}


	// class Packet
	Packet::Packet()
	{
		pb = new PacketBuffer;
	}


	Packet::~Packet()
	{
		delete pb;
	}


	char* Packet::setBuffer(unsigned int length)
	{
		return pb->setBuffer(length);
	}


	int Packet::parseHead()
	{
		LOG_DEBUG("parseHead :");
		common::printByHex(pb->data, pb->vecPos[1]);

		ptrHead = (protocol::data::HeadPtr)pb->data;

		if (ptrHead->bcc_code[0] != 0xF1 ||
			ptrHead->bcc_code[1] != 0xE2 ||
			ptrHead->bcc_code[2] != 0xD3 ||
			ptrHead->bcc_code[3] != 0xC4 ||
			ptrHead->other != 0x00)
		{
			return -1;
		}

		return ptrHead->len - pb->vecPos[1];
	}


	int Packet::parse()
	{
		unsigned int index = pb->vecPos[1];

		LOG_DEBUG("parseData :");
		common::printByHex(&pb->data[index], pb->vecPos[2] - pb->vecPos[1]);

		while(index < pb->vecPos[2] - sizeof(unsigned short))
		{
			protocol::data::TLVPtr ptrTLV = new protocol::data::TLV;

			ptrTLV->type = pb->data[index++];
			ptrTLV->len = pb->data[index++];
			ptrTLV->value = &pb->data[index];
			index += ptrTLV->len;

			vecTLVPtr.push_back(ptrTLV);
		}

		crc = (unsigned short*)&pb->data[index];

		printTLV();

		return 0;
	}


	void Packet::copyHead(const protocol::Packet* in)
	{
		unsigned int len = sizeof(protocol::data::Head);
		setBuffer(len);
		memcpy(pb->data, in->ptrHead, sizeof(protocol::data::Head));
		this->ptrHead = (protocol::data::HeadPtr)pb->data;
	}


	void Packet::setHead()
	{
		unsigned int len = sizeof(protocol::data::Head);
		setBuffer(len);
		ptrHead = (protocol::data::HeadPtr)pb->data;
		ptrHead->bcc_code[0] = 0xF1;
		ptrHead->bcc_code[1] = 0xE2;
		ptrHead->bcc_code[2] = 0xD3;
		ptrHead->bcc_code[3] = 0xC4;
		ptrHead->other = 0x00;
	}


	protocol::data::TLVPtr Packet::setTLV(int type, int length, char* value)
	{
		pb->data[pb->vecPos.back()] = type;
		pb->data[pb->vecPos.back() + 1] = length;
		setBuffer(length + 2);

		protocol::data::TLVPtr ptrTLV = new protocol::data::TLV;

		ptrTLV->type = type;
		ptrTLV->len = length;
		ptrTLV->value = &pb->data[pb->vecPos[pb->vecPos.size() - 2] + 2];

		if(value != NULL)
		{
			memcpy(ptrTLV->value, value, length);
		}

		vecTLVPtr.push_back(ptrTLV);

		return ptrTLV;
	}


	char* Packet::setCRC()
	{
		crc = (unsigned short*)setBuffer(sizeof(unsigned short));
		ptrHead->len = pb->vecPos.back();
		*crc = protocol::createCRC(pb->data, pb->vecPos.back() - sizeof(unsigned short));

		printData();

		return pb->data;
	}


	char* Packet::raw() const
	{
		return pb->data;
	}


	unsigned int Packet::len() const
	{
		return pb->vecPos.back();
	}


	void Packet::printTLV()
	{
		LOG_DEBUG("TLV vector size : " << vecTLVPtr.size());

		for(unsigned int i = 0; i < vecTLVPtr.size(); i++)
		{
			LOG_DEBUG("TLV type :");
			common::printByHex(&vecTLVPtr[i]->type, 1);
			LOG_DEBUG("TLV len :");
			common::printByHex(&vecTLVPtr[i]->len, 1);
			LOG_DEBUG("TLV value :");
			common::printByHex(vecTLVPtr[i]->value, (int)vecTLVPtr[i]->len);
		}
	}


	void Packet::printData()
	{
		LOG_DEBUG("Head :");
		common::printByHex(pb->data, pb->vecPos[1]);
		printTLV();
		LOG_DEBUG("All Data :");
		common::printByHex(pb->data, pb->vecPos.back());
	}
};// namespace protocol
