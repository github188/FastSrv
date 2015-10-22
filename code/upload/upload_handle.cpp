/*
//
//	Last Modify Date: 2015-10-22
//	Author: zengpw
//	History:
//					2015-10-09 zengpw created
//	File Property: private
//	Future:
//					I. 消息分析和入库
//
//
*/

#include "upload_handle.h"

session::HANDLE_RTN UploadHandle::cidDataGps(const protocol::PacketIn* in, protocol::PacketOut* out)
{
	bool error = false;

	TlvHandle th;
	DbInterface di;

	TLVGroupPtr pTlvGrp = in->getTLVGroup();
	LOG_DEBUG("========= cidDataGps processing, pTlvGrp->size() = " << pTlvGrp->size() << " =========");

	for(TLVGroupIter iter = pTlvGrp->begin(); iter != pTlvGrp->end(); ++iter)
	{
		if(iter->type _EQ_ TID_GPS)
		{
			TLV_GPS gps;
			TLV_HANDLE_GPS gps_handle;

			memcpy(&gps, iter->value, iter->len);

			int rtn = th.tlv_gps_handle(gps, gps_handle);

			if(rtn _NEQ_ THR_OK)
			{
				error = true;
				continue;
			}

			rtn = di.gps_update(db, gps_handle);

			if(rtn _NEQ_ THR_TRUE)
			{
				error = true;
				continue;
			}
		}
	}

	#if 1
		//单次调试用，程序接收包处理后即退出
		return session::HANDLE_RTN_STOP;
	#else
		//正常逻辑
		if(error)
			return session::HANDLE_RTN_CONTINUE;
		else
			return session::HANDLE_RTN_REMOVE;
	#endif
}


session::HANDLE_RTN UploadHandle::cidDataLbs(const protocol::PacketIn* in, protocol::PacketOut* out)
{
	bool error = false;

	TlvHandle th;
	DbInterface di;

	TLVGroupPtr pTlvGrp = in->getTLVGroup();
	LOG_DEBUG("========= cidDataLbs processing, pTlvGrp->size() = " << pTlvGrp->size() << " =========");

	for(TLVGroupIter iter = pTlvGrp->begin(); iter != pTlvGrp->end(); ++iter)
	{
		if(iter->type _EQ_ TID_LBS)
		{
			TLV_LBS lbs;
			TLV_HANDLE_LBS lbs_handle;

			memcpy(&lbs, iter->value, iter->len);

			int rtn = th.tlv_lbs_handle(lbs, lbs_handle);

			if(rtn _NEQ_ THR_OK)
			{
				error = true;
				continue;
			}

			rtn = di.lbs_update(db, lbs_handle);

			if(rtn _NEQ_ THR_TRUE)
			{
				error = true;
				continue;
			}
		}
	}

	#if 1
		//单次调试用，程序接收包处理后即退出
		return session::HANDLE_RTN_STOP;
	#else
		//正常逻辑
		if(error)
			return session::HANDLE_RTN_CONTINUE;
		else
			return session::HANDLE_RTN_REMOVE;
	#endif
}
