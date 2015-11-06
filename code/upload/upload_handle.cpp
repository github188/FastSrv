/*
//
//	Last Modify Date: 2015-11-06
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

session::HANDLE_RTN UploadHandle::cidLogin(const protocol::PacketIn* in, protocol::PacketOut* out)
{
	bool error = false;

	stringstream ss;
	TlvHandle th;
	DbInterface di;

	TLVGroupPtr pTlvGrp = in->getTLVGroup();
	LOG_DEBUG("========= cidLogin processing begin, pTlvGrp->size() = " << pTlvGrp->size());

	for(TLVGroupIter iter = pTlvGrp->begin(); iter != pTlvGrp->end(); ++iter)
	{
		if(iter->type _EQ_ TID_DEV_FIRM)
		{
			TLV_DEV_FIRM firm;
			TLV_HANDLE_DEV_FIRM firm_handle;

			memcpy(&firm, iter->value, iter->len);

			firm_handle.dev_id = in->getDevId();
			int rtn = th.tlv_firm_handle(firm, firm_handle);

			if(rtn _NEQ_ THR_OK)
			{
				error = true;
				continue;
			}

			rtn = di.firm_update(db, firm_handle);

			if(rtn _NEQ_ THR_TRUE)
			{
				error = true;
				continue;
			}
		}
	}

	LOG_DEBUG("========= cidLogin processing end.");

	#if 0
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


session::HANDLE_RTN UploadHandle::cidDataGps(const protocol::PacketIn* in, protocol::PacketOut* out)
{
	bool error = false;

	stringstream ss;
	TlvHandle th;
	DbInterface di;

	TLVGroupPtr pTlvGrp = in->getTLVGroup();
	LOG_DEBUG("========= cidDataGps processing begin, pTlvGrp->size() = " << pTlvGrp->size());

	for(TLVGroupIter iter = pTlvGrp->begin(); iter != pTlvGrp->end(); ++iter)
	{
		if(iter->type _EQ_ TID_GPS)
		{
			TLV_GPS gps;
			TLV_HANDLE_GPS gps_handle;

			memcpy(&gps, iter->value, iter->len);

			gps_handle.dev_id = in->getDevId();
			if(!di.public_get_order_id(db, gps_handle.dev_id, gps_handle.order_id))
			{
				error = true;
				continue;
			}

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

	LOG_DEBUG("========= cidDataGps processing end.");

	#if 0
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

	stringstream ss;
	TlvHandle th;
	DbInterface di;

	TLVGroupPtr pTlvGrp = in->getTLVGroup();
	LOG_DEBUG("========= cidDataLbs processing begin, pTlvGrp->size() = " << pTlvGrp->size());

	for(TLVGroupIter iter = pTlvGrp->begin(); iter != pTlvGrp->end(); ++iter)
	{
		if(iter->type _EQ_ TID_LBS)
		{
			TLV_LBS lbs;
			TLV_HANDLE_LBS lbs_handle;

			memcpy(&lbs, iter->value, iter->len);

			lbs_handle.dev_id = in->getDevId();
			if(!di.public_get_order_id(db, lbs_handle.dev_id, lbs_handle.order_id))
			{
				error = true;
				continue;
			}

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

	LOG_DEBUG("========= cidDataLbs processing end.");

	#if 0
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


session::HANDLE_RTN UploadHandle::cidDataTh(const protocol::PacketIn* in, protocol::PacketOut* out)
{
	bool error = false;

	stringstream ss;
	TlvHandle th;
	DbInterface di;

	TLVGroupPtr pTlvGrp = in->getTLVGroup();
	LOG_DEBUG("========= cidDataTh processing begin, pTlvGrp->size() = " << pTlvGrp->size());

	for(TLVGroupIter iter = pTlvGrp->begin(); iter != pTlvGrp->end(); ++iter)
	{
		if(iter->type _EQ_ TID_TH)
		{
			TLV_TH th_data;
			TLV_HANDLE_TH th_handle;

			memcpy(&th_data, iter->value, iter->len);

			th_handle.dev_id = in->getDevId();
			if(!di.public_get_order_id(db, th_handle.dev_id, th_handle.order_id))
			{
				error = true;
				continue;
			}

			int rtn = th.tlv_th_handle(th_data, th_handle);

			if(rtn _NEQ_ THR_OK)
			{
				error = true;
				continue;
			}

			rtn = di.th_update(db, th_handle);

			if(rtn _NEQ_ THR_TRUE)
			{
				error = true;
				continue;
			}
		}
	}

	LOG_DEBUG("========= cidDataTh processing end.");

	#if 0
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


session::HANDLE_RTN UploadHandle::cidUnband(const protocol::PacketIn* in, protocol::PacketOut* out)
{
	bool error = false;

	TlvHandle th;
	DbInterface di;

	TLVGroupPtr pTlvGrp = in->getTLVGroup();
	LOG_DEBUG("========= cidUnband processing begin, pTlvGrp->size() = " << pTlvGrp->size());

	for(TLVGroupIter iter = pTlvGrp->begin(); iter != pTlvGrp->end(); ++iter)
	{
		if(iter->type _EQ_ TID_RTN)
		{
			TLV_RTN unband_data;
			TLV_HANDLE_UNBAND_RTN unband_handle;

			memcpy(&unband_data, iter->value, iter->len);

			unband_handle.dev_id = in->getDevId();
			int rtn = th.tlv_unband_handle(unband_data, unband_handle);

			if(rtn _NEQ_ THR_OK)
			{
				error = true;
				continue;
			}

			rtn = di.unband_update(db, unband_handle);

			if(rtn _NEQ_ THR_TRUE)
			{
				error = true;
				continue;
			}
		}
	}

	LOG_DEBUG("========= cidUnband processing end.");

	#if 0
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


session::HANDLE_RTN UploadHandle::cidDevUnband(const protocol::PacketIn* in, protocol::PacketOut* out)
{
	bool error = false;

	TlvHandle th;
	DbInterface di;

	TLVGroupPtr pTlvGrp = in->getTLVGroup();
	LOG_DEBUG("========= cidDevUnband processing begin, pTlvGrp->size() = " << pTlvGrp->size());

	for(TLVGroupIter iter = pTlvGrp->begin(); iter != pTlvGrp->end(); ++iter)
	{
		if(iter->type _EQ_ TID_TIME)
		{
			TLV_TIME tm;
			TLV_HANDLE_DEV_UNBAND_RTN dev_unband_handle;

			memcpy(&tm, iter->value, iter->len);

			dev_unband_handle.dev_id = in->getDevId();
			int rtn = th.tlv_dev_unband_handle(tm, dev_unband_handle);

			if(rtn _NEQ_ THR_OK)
			{
				error = true;
				continue;
			}

			rtn = di.dev_unband_update(db, dev_unband_handle);

			if(rtn _NEQ_ THR_TRUE)
			{
				error = true;
				continue;
			}
		}
	}

	LOG_DEBUG("========= cidDevUnband processing end.");

	#if 0
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