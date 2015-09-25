/*
//
//	Last Modify Date: 2015-09-15
//	Author: zengpw
//	History:
//					2015-09-09 zengpw created
//	File Property: public
//	Future:
//					I. 协议
//
//
*/

#include "protocol_pb.h"

namespace protocol
{
	namespace pb
	{
		PacketPB::PacketPB()
		{
			pb = new PacketBuffer;
		}


		PacketPB::~PacketPB()
		{
			delete pb;
		}


		char* PacketPB::setBuffer(unsigned int length)
		{
			return pb->setBuffer(length);
		}


		int PacketPB::parseHead()
		{
			// LOG_DEBUG("PB parseHead : ");
			// common::printByHex(pb->data, pb->vecPos[1]);

			ptrHead = (protocol::pb::HeadPtr)pb->data;

			if (ptrHead->xcode[0] != 0xA1 ||
				ptrHead->xcode[1] != 0xB2 ||
				ptrHead->xcode[2] != 0xC3 ||
				ptrHead->xcode[3] != 0xD4)
			{
				return -1;
			}

			return ptrHead->len - pb->vecPos[1];
		}


		int PacketPB::parse()
		{
			unsigned int index = pb->vecPos[1];
			pbSize = pb->vecPos[2] - pb->vecPos[1];

			// LOG_DEBUG("PB parseData : ");
			// common::printByHex(&pb->data[index], pbSize);

			ptrPB = (protocol::pb::PBPtr)&pb->data[index];
			ptrCRC = (protocol::pb::CRCPtr)&pb->data[pb->vecPos[2] - 2];

			pbSize -= sizeof(protocol::pb::CRC);

			return 0;
		}


		void PacketPB::getPB(string& in)
		{
			in.assign(this->ptrPB, this->pbSize);
		}


		char* PacketPB::setHead()
		{
			ptrHead = (protocol::pb::HeadPtr)setBuffer(sizeof(protocol::pb::Head));

			ptrHead->xcode[0] = 0xA1;
			ptrHead->xcode[1] = 0xB2;
			ptrHead->xcode[2] = 0xC3;
			ptrHead->xcode[3] = 0xD4;
			ptrHead->name = PB_HEARTBEAT;
			return pb->data;
		}


		char* PacketPB::setPB(const char* in, unsigned int length)
		{
			pbSize = length;
			ptrPB = (protocol::pb::PBPtr)setBuffer(pbSize);
			memcpy(ptrPB, in, pbSize);
			return pb->data;
		}


		char* PacketPB::setCRC()
		{
			ptrCRC = (protocol::pb::CRCPtr)setBuffer(sizeof(protocol::pb::CRC));
			ptrHead->len = pb->vecPos.back();
			*ptrCRC = protocol::createCRC(pb->data, pb->vecPos.back() - sizeof(protocol::pb::CRC));
			printData();
			return pb->data;
		}


		char* PacketPB::raw()
		{
			return pb->data;
		}


		unsigned int PacketPB::len()
		{
			return pb->vecPos.back();
		}


		void PacketPB::printData()
		{
			// LOG_DEBUG("PB Head : ");
			// common::printByHex(pb->data, pb->vecPos[1]);
			// LOG_DEBUG("PB Data : ");
			// common::printByHex(pb->data + pb->vecPos[1], pbSize);
			// LOG_DEBUG("PB All Data : ");
			// common::printByHex(pb->data, pb->vecPos.back());
		}
	}// namespace pb
};// namespace protocol
