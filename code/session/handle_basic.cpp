/*
//
//	Last Modify Date: 2015-11-12
//	Author: zengpw
//	History:
//					2015-09-15 zengpw created
//	File Property: public
//	Future:
//					I. TLV 公共消息处理基类
//
//
*/

#include "handle_basic.h"

namespace session
{
	HandleBasic::HandleBasic()
	{
		db = NULL;
	}

	HandleBasic::HandleBasic(string db_conn_info)
	{
		db = new common::DB(db_conn_info);

		if(db->getConn() == NULL)
		{
			LOG_DEBUG("connect database error : " << db_conn_info);
		}
	}

	HANDLE_RTN HandleBasic::dispatch(const protocol::PacketIn* in, protocol::PacketOut* out)
	{
		LOG_DEBUG("--------------- dispatch message, command id = 0x" << hex << setiosflags(ios::uppercase) << setfill('0') << setw(4) << in->getCID() << " ---------------");

		out->copy(in);

		if(in->getCID() == protocol::tlv::CID_LOGIN)
			return cidLogin(in, out);

		if(in->getCID() == protocol::tlv::CID_DEV_MSG)
			return cidDevMsg(in, out);

		if(in->getCID() == protocol::tlv::CID_UNBAND)
			return cidUnband(in, out);

		if(in->getCID() == protocol::tlv::CID_DEV_UNBAND)
			return cidDevUnband(in, out);

		if(in->getCID() == protocol::tlv::CID_DEV_BAND)
			return cidDevband(in, out);

		if(in->getCID() == protocol::tlv::CID_PARAMETER)
			return cidParameter(in, out);

		if(in->getCID() == protocol::tlv::CID_PARAMETER_REQUEST)
			return cidParameterRequest(in, out);

		if(in->getCID() == protocol::tlv::CID_PARAMETER_VERSION)
			return cidParameterVersion(in, out);

		if(in->getCID() == protocol::tlv::CID_DEV_INIT)
			return cidDevInit(in, out);

		if(in->getCID() == protocol::tlv::CID_DEV_TIME)
			return cidDevTime(in, out);

		if(in->getCID() == protocol::tlv::CID_DATA_GPS)
			return cidDataGps(in, out);

		if(in->getCID() == protocol::tlv::CID_DATA_LBS)
			return cidDataLbs(in, out);

		if(in->getCID() == protocol::tlv::CID_DATA_TH)
			return cidDataTh(in, out);

		if(in->getCID() == protocol::tlv::CID_MANAGE_LBS)
			return cidManageLbs(in, out);

		return HANDLE_RTN_CONTINUE;
	}

	HANDLE_RTN HandleBasic::dispatch_origin_msg(const char* value, const unsigned int len, protocol::PacketIn* in, protocol::PacketOut* out)
	{
		if(in->buildFromString(value, len) != 0)
			return HANDLE_RTN_CONTINUE;

		return this->dispatch(in, out);
	}

	HANDLE_RTN HandleBasic::conn(protocol::PacketOut* out)
	{
		return HANDLE_RTN_CONTINUE;
	}

	HANDLE_RTN HandleBasic::reject(const protocol::PacketIn* in, protocol::PacketOut* out)
	{
		return HANDLE_RTN_CONTINUE;
	}

	HANDLE_RTN HandleBasic::sending(const protocol::PacketIn* in, vector<protocol::PacketOut> &vp)
	{
		return HANDLE_RTN_CONTINUE;
	}

	HANDLE_RTN HandleBasic::cidLogin(const protocol::PacketIn* in, protocol::PacketOut* out)
	{
		return HANDLE_RTN_CONTINUE;
	}

	HANDLE_RTN HandleBasic::cidDevMsg(const protocol::PacketIn* in, protocol::PacketOut* out)
	{
		return HANDLE_RTN_CONTINUE;
	}

	HANDLE_RTN HandleBasic::cidUnband(const protocol::PacketIn* in, protocol::PacketOut* out)
	{
		return HANDLE_RTN_CONTINUE;
	}

	HANDLE_RTN HandleBasic::cidDevUnband(const protocol::PacketIn* in, protocol::PacketOut* out)
	{
		return HANDLE_RTN_CONTINUE;
	}

	HANDLE_RTN HandleBasic::cidDevband(const protocol::PacketIn* in, protocol::PacketOut* out)
	{
		return HANDLE_RTN_CONTINUE;
	}

	HANDLE_RTN HandleBasic::cidParameter(const protocol::PacketIn* in, protocol::PacketOut* out)
	{
		return HANDLE_RTN_CONTINUE;
	}

	HANDLE_RTN HandleBasic::cidParameterRequest(const protocol::PacketIn* in, protocol::PacketOut* out)
	{
		return HANDLE_RTN_CONTINUE;
	}

	HANDLE_RTN HandleBasic::cidParameterVersion(const protocol::PacketIn* in, protocol::PacketOut* out)
	{
		return HANDLE_RTN_CONTINUE;
	}

	HANDLE_RTN HandleBasic::cidDevInit(const protocol::PacketIn* in, protocol::PacketOut* out)
	{
		return HANDLE_RTN_CONTINUE;
	}

	HANDLE_RTN HandleBasic::cidDevTime(const protocol::PacketIn* in, protocol::PacketOut* out)
	{
		return HANDLE_RTN_CONTINUE;
	}

	HANDLE_RTN HandleBasic::cidDataGps(const protocol::PacketIn* in, protocol::PacketOut* out)
	{
		return HANDLE_RTN_CONTINUE;
	}

	HANDLE_RTN HandleBasic::cidDataLbs(const protocol::PacketIn* in, protocol::PacketOut* out)
	{
		return HANDLE_RTN_CONTINUE;
	}

	HANDLE_RTN HandleBasic::cidDataTh(const protocol::PacketIn* in, protocol::PacketOut* out)
	{
		return HANDLE_RTN_CONTINUE;
	}

	HANDLE_RTN HandleBasic::cidManageLbs(const protocol::PacketIn* in, protocol::PacketOut* out)
	{
		return HANDLE_RTN_CONTINUE;
	}
};// namespace session