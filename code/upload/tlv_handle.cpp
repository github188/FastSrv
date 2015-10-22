/*
//
//	Last Modify Date: 2015-10-22
//	Author: zengpw
//	History:
//					2015-10-20 zengpw created
//	File Property: private
//	Future:
//					I. tlv 消息处理
//
//
*/

#include "tlv_handle.h"

TLV_HANDLE_RTN TlvHandle::basic_data_handle(BasicData& bd, HANDLE_BasicData& hbd)
{
	char buf[12];
	stringstream ss;

	//移动标记
	ss << (int)bd.move;
	hbd.move = ss.str();
	ss.str("");
	ss.clear();

	//电压
	ss << bd.voltage;
	hbd.voltage = ss.str();
	ss.str("");
	ss.clear();

	//温度
	memset(buf, 0, sizeof(buf));
	sprintf(buf, "%3.1f", (float)bd.temperature/10);

	ss << buf;
	hbd.temperature = ss.str();
	ss.str("");
	ss.clear();

	//光曝
	ss << bd.exposure;
	hbd.exposure = ss.str();
	ss.str("");
	ss.clear();

	return THR_OK;
}


TLV_HANDLE_RTN TlvHandle::tlv_gps_handle(TLV_GPS& gps, TLV_HANDLE_GPS& gps_handle)
{
	LOG_DEBUG("====== tlv_gps_handle processing ======");

	//-------------- 打印入参
	LOG_DEBUG("---------- TLV_GPS content : ");
	printDateTime2k(gps.dt);
	LOG_DEBUG("rssi = " << (int)gps.bd.rssi << \
			", move = " << (int)gps.bd.move << \
			", voltage = " << gps.bd.voltage << \
			", temperature = " << gps.bd.temperature \
			<< ", exposure = " << gps.bd.exposure);
	LOG_DEBUG("sn_lat = " << (int)gps.sn_lat << \
			", ew_long = " << (int)gps.ew_long << \
			", latitude = " << gps.latitude << \
			", longitude = " << gps.longitude);
	LOG_DEBUG("---------- end.");

	//-------------- 处理参数
	char buf[12];
	stringstream ss;

	//时间
	gps_handle.datetime = DateTime2String2k(gps.dt);

	//基础数据
	if(basic_data_handle(gps.bd, gps_handle.hbd) _NEQ_ THR_OK)
	{
		return THR_FAIL;
	}

	//经纬度
	//若干个0 + 原始数据 = 9位，然后再加上 000，共12位
	memset(buf, 0, sizeof(buf));
	sprintf(buf, "%09u", gps.latitude);
	ss << buf;
	gps_handle.latitude = ss.str();
	gps_handle.latitude += "000";
	ss.str("");
	ss.clear();

	memset(buf, 0, sizeof(buf));
	sprintf(buf, "%09u", gps.longitude);
	ss << buf;
	gps_handle.longitude = ss.str();
	gps_handle.longitude += "000";
	ss.str("");
	ss.clear();

	//额外的数据
	gps_handle.mode = "0";

	//-------------- 打印出参
	LOG_DEBUG("---------- TLV_HANDLE_GPS content : ");
	LOG_DEBUG("datetime = " << gps_handle.datetime);
	LOG_DEBUG("move = " << gps_handle.hbd.move << \
			", temperature = " << gps_handle.hbd.temperature << \
			", voltage = " << gps_handle.hbd.voltage << \
			", exposure = " << gps_handle.hbd.exposure);
	LOG_DEBUG("latitude = " << gps_handle.latitude << \
			", longitude = " << gps_handle.longitude);
	LOG_DEBUG("---------- end.");

	return THR_OK;
}


TLV_HANDLE_RTN TlvHandle::tlv_lbs_handle(TLV_LBS& lbs, TLV_HANDLE_LBS& lbs_handle)
{

	LOG_DEBUG("====== tlv_lbs_handle processing ======");

	//-------------- 打印入参
	LOG_DEBUG("---------- TLV_LBS content : ");
	printDateTime2k(lbs.dt);
	LOG_DEBUG("rssi = " << (int)lbs.bd.rssi << \
			", move = " << (int)lbs.bd.move << \
			", voltage = " << lbs.bd.voltage << \
			", temperature = " << lbs.bd.temperature \
			<< ", exposure = " << lbs.bd.exposure);

	for(int i = 0; i < 3; i++)
	{
		LOG_DEBUG("cell = " << (int)lbs.ld[i].cell << \
				",mnc = " << (int)lbs.ld[i].mnc << \
				",mcc = " << lbs.ld[i].mcc << \
				",lac = " << lbs.ld[i].lac << \
				",cell_id = " << lbs.ld[i].cell_id << \
				",bsic = " << (int)lbs.ld[i].bsic << \
				", rssi = " << (int)lbs.ld[i].rssi);
	}

	LOG_DEBUG("---------- end.");

	//-------------- 处理参数
	char buf[12];
	stringstream ss;

	//时间
	lbs_handle.datetime = DateTime2String2k(lbs.dt);

	//基础数据
	if(basic_data_handle(lbs.bd, lbs_handle.hbd) _NEQ_ THR_OK)
	{
		return THR_FAIL;
	}

	// LBS 转经纬度
	HttpInterface hi;
	if(hi.lbs2gps(lbs.ld, lbs_handle.latitude, lbs_handle.longitude) _NEQ_ THR_OK)
	{
		lbs_handle.latitude = "000000000000";
		lbs_handle.longitude = "000000000000";
	}

	//额外的数据
	lbs_handle.mode = "1";

	//-------------- 打印出参
	LOG_DEBUG("---------- TLV_HANDLE_LBS content : ");
	LOG_DEBUG("datetime = " << lbs_handle.datetime);
	LOG_DEBUG("move = " << lbs_handle.hbd.move << \
			", temperature = " << lbs_handle.hbd.temperature << \
			", voltage = " << lbs_handle.hbd.voltage << \
			", exposure = " << lbs_handle.hbd.exposure);
	LOG_DEBUG("latitude = " << lbs_handle.latitude << \
			", longitude = " << lbs_handle.longitude);
	LOG_DEBUG("---------- end.");

	return THR_OK;
}