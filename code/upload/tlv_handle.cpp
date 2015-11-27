/*
//
//	Last Modify Date: 2015-11-18
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
	char buf[64];
	stringstream ss;

	//场强
	ss << (int)bd.rssi;
	hbd.rssi = ss.str();
	ss.str("");
	ss.clear();

	//移动标记
	ss << (int)bd.move;
	hbd.move = ss.str();
	ss.str("");
	ss.clear();

	//光曝告警标记
	ss << (int)bd.flag;
	hbd.flag = ss.str();
	ss.str("");
	ss.clear();

	if(hbd.flag == "1")
	{
		hbd.alarm = "2";
	}

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


TLV_HANDLE_RTN TlvHandle::tlv_firm_handle(TLV_DEV_FIRM& firm, TLV_HANDLE_DEV_FIRM& firm_handle)
{
	LOG_DEBUG("====== tlv_firm_handle processing ======");

	//-------------- 打印入参
	LOG_DEBUG("---------- TLV_DEV_FIRM content : ");
	LOG_DEBUG("version = " << firm.version << \
			", imei = " << firm.imei << \
			", iccid = " << firm.iccid);
	LOG_DEBUG("---------- end.");

	//-------------- 处理参数
	stringstream ss;

	ss << firm.version;
	firm_handle.version = ss.str();
	ss.str("");
	ss.clear();

	// imei[15] 通常被写满数据，从而导致没有 '\0' 结束符
	firm_handle.imei.assign((char*)firm.imei, sizeof(firm.imei));

	ss << firm.iccid;
	firm_handle.iccid = ss.str();
	ss.str("");
	ss.clear();

	//-------------- 打印出参
	LOG_DEBUG("---------- TLV_HANDLE_DEV_FIRM content : ");
	LOG_DEBUG("dev_id = " << firm_handle.dev_id << \
			", version = " << firm_handle.version << \
			", imei = " << firm_handle.imei << \
			", iccid = " << firm_handle.iccid);
	LOG_DEBUG("---------- end.");

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
			", flag = " << (int)gps.bd.flag << \
			", voltage = " << gps.bd.voltage << \
			", temperature = " << gps.bd.temperature << \
			", exposure = " << gps.bd.exposure);
	LOG_DEBUG("sn_lat = " << (int)gps.sn_lat << \
			", ew_long = " << (int)gps.ew_long << \
			", latitude = " << gps.latitude << \
			", longitude = " << gps.longitude);
	LOG_DEBUG("---------- end.");

	//-------------- 处理参数
	char buf[64];
	stringstream ss;

	//时间
	gps_handle.datetime = DateTime2String2k(gps.dt);

	//基础数据
	if(basic_data_handle(gps.bd, gps_handle.hbd) _NEQ_ THR_OK)
	{
		return THR_FAIL;
	}

	//经纬度，需要补长度到 12 位
	memset(buf, 0, sizeof(buf));
	sprintf(buf, "%08u", gps.latitude);
	ss << buf;
	gps_handle.latitude = ss.str();
	gps_handle.latitude += "000000000000";
	gps_handle.latitude = gps_handle.latitude.substr(0, 12);
	ss.str("");
	ss.clear();

	memset(buf, 0, sizeof(buf));
	sprintf(buf, "%8u", gps.longitude);
	ss << buf;
	gps_handle.longitude = ss.str();
	gps_handle.longitude += "000000000000";
	gps_handle.longitude = gps_handle.longitude.substr(0, 12);
	ss.str("");
	ss.clear();

	//额外的数据
	gps_handle.mode = "0";

	//-------------- 打印出参
	LOG_DEBUG("---------- TLV_HANDLE_GPS content : ");
	LOG_DEBUG("dev_id = " << gps_handle.dev_id << \
			", order_id = " << gps_handle.order_id << \
			", datetime = " << gps_handle.datetime);
	LOG_DEBUG("rssi = " << gps_handle.hbd.rssi << \
			", move = " << gps_handle.hbd.move << \
			", flag = " << gps_handle.hbd.flag << \
			", voltage = " << gps_handle.hbd.voltage << \
			", temperature = " << gps_handle.hbd.temperature << \
			", exposure = " << gps_handle.hbd.exposure);
	LOG_DEBUG("latitude = " << gps_handle.latitude << \
			", longitude = " << gps_handle.longitude);
	LOG_DEBUG("alarm = " << gps_handle.hbd.alarm);
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
			", flag = " << (int)lbs.bd.flag << \
			", voltage = " << lbs.bd.voltage << \
			", temperature = " << lbs.bd.temperature << \
			", exposure = " << lbs.bd.exposure);

	for(int i = 0; i < sizeof(lbs.ld)/sizeof(LbsData); i++)
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
	char buf[64];
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
	if(hi.lbs2gps(lbs, lbs_handle.latitude, lbs_handle.longitude) _NEQ_ THR_OK)
	{
		return THR_FAIL;
		// lbs_handle.latitude = "000000000000";
		// lbs_handle.longitude = "000000000000";
	}
	else
	{
		//移除字符 '.'
		string::iterator it_lat = remove_if(lbs_handle.latitude.begin(), lbs_handle.latitude.end(), bind2nd(equal_to<char>(), '.'));
		lbs_handle.latitude.erase(it_lat, lbs_handle.latitude.end());
		string::iterator it_longi = remove_if(lbs_handle.longitude.begin(), lbs_handle.longitude.end(), bind2nd(equal_to<char>(), '.'));
		lbs_handle.longitude.erase(it_longi, lbs_handle.longitude.end());

		//补到12位长度
		memset(buf, 0, sizeof(buf));
		sprintf(buf, "0%s", lbs_handle.latitude.c_str());
		ss << buf;
		lbs_handle.latitude = ss.str() + "000000000000";
		lbs_handle.latitude = lbs_handle.latitude.substr(0, 12);
		ss.str("");
		ss.clear();

		lbs_handle.longitude += "000000000000";
		lbs_handle.longitude = lbs_handle.longitude.substr(0, 12);
	}

	//告警数据
	if(lbs_handle.hbd.flag != "0")
	{
		hi.gps2addrAmap(lbs_handle.latitude, lbs_handle.longitude, lbs_handle.hbd.addr);
	}

	//额外的数据
	lbs_handle.mode = "1";

	//-------------- 打印出参
	LOG_DEBUG("---------- TLV_HANDLE_LBS content : ");
	LOG_DEBUG("dev_id = " << lbs_handle.dev_id << \
			", order_id = " << lbs_handle.order_id << \
			", datetime = " << lbs_handle.datetime);
	LOG_DEBUG("rssi = " << lbs_handle.hbd.rssi << \
			", move = " << lbs_handle.hbd.move << \
			", flag = " << lbs_handle.hbd.flag << \
			", voltage = " << lbs_handle.hbd.voltage << \
			", temperature = " << lbs_handle.hbd.temperature << \
			", exposure = " << lbs_handle.hbd.exposure);
	LOG_DEBUG("latitude = " << lbs_handle.latitude << \
			", longitude = " << lbs_handle.longitude);
	LOG_DEBUG("alarm = " << lbs_handle.hbd.alarm << \
			", addr = " << lbs_handle.hbd.addr);
	LOG_DEBUG("---------- end.");

	return THR_OK;
}


TLV_HANDLE_RTN TlvHandle::tlv_th_handle(TLV_TH& th, TLV_HANDLE_TH& th_handle)
{
	LOG_DEBUG("====== tlv_th_handle processing ======");

	//-------------- 打印入参
	LOG_DEBUG("---------- TLV_TH content : ");
	printDateTime2k(th.dt);
	printDateTime2k(th.dt_gps);
	LOG_DEBUG("alarm = " << (int)th.alarm << \
			", t0 = " << th.t0 << \
			", h0 = " << th.h0);

	LOG_DEBUG("---------- end.");

	//-------------- 处理参数
	char buf[64];
	stringstream ss;

	th_handle.datetime = DateTime2String2k(th.dt);
	th_handle.datetime_gps = DateTime2String2k(th.dt_gps);

	ss << (int)th.alarm;
	th_handle.alarm = ss.str();
	ss.str("");
	ss.clear();

	memset(buf, 0, sizeof(buf));
	sprintf(buf, "%3.1f", (float)th.t0/10);

	ss << buf;
	th_handle.t0 = ss.str();
	ss.str("");
	ss.clear();

	memset(buf, 0, sizeof(buf));
	sprintf(buf, "%3.1f", (float)th.h0/10);

	ss << buf;
	th_handle.h0 = ss.str();
	ss.str("");
	ss.clear();

	//-------------- 打印出参
	LOG_DEBUG("---------- TLV_HANDLE_TH content : ");
	LOG_DEBUG("dev_id = " << th_handle.dev_id << \
			", order_id = " << th_handle.order_id << \
			", datetime = " << th_handle.datetime);
	LOG_DEBUG("datetime_gps = " << th_handle.datetime_gps);
	LOG_DEBUG("alarm = " << th_handle.alarm << \
			", t0 = " << th_handle.t0 << \
			", h0 = " << th_handle.h0);
	LOG_DEBUG("---------- end.");

	return THR_OK;
}


TLV_HANDLE_RTN TlvHandle::tlv_unband_handle(TLV_RTN& rtn, TLV_HANDLE_UNBAND_RTN& unband_handle)
{
	LOG_DEBUG("====== tlv_unband_handle processing ======");

	//-------------- 打印入参
	LOG_DEBUG("---------- TLV_RTN content : ");
	LOG_DEBUG("rtn = " << (int)rtn);
	LOG_DEBUG("---------- end.");

	stringstream ss;

	ss << (int)rtn;
	unband_handle.rtn = ss.str();
	ss.str("");
	ss.clear();

	//-------------- 打印出参
	LOG_DEBUG("---------- TLV_HANDLE_UNBAND_RTN content : ");
	LOG_DEBUG("dev_id = " << unband_handle.dev_id);
	LOG_DEBUG("rtn = " << unband_handle.rtn);
	LOG_DEBUG("---------- end.");

	return THR_OK;
}


TLV_HANDLE_RTN TlvHandle::tlv_dev_unband_handle(TLV_TIME& tm, TLV_HANDLE_DEV_UNBAND_RTN& dev_unband_handle)
{
	LOG_DEBUG("====== tlv_unband_handle processing ======");

	//-------------- 打印入参
	LOG_DEBUG("---------- TLV_TIME content : ");
	printDateTimeSec(tm);
	LOG_DEBUG("---------- end.");

	dev_unband_handle.datetime = DateTime2StringSec(tm);

	//-------------- 打印出参
	LOG_DEBUG("---------- TLV_HANDLE_DEV_UNBAND_RTN content : ");
	LOG_DEBUG("dev_id = " << dev_unband_handle.dev_id);
	LOG_DEBUG("datetime = " << dev_unband_handle.datetime);
	LOG_DEBUG("---------- end.");

	return THR_OK;
}


TLV_HANDLE_RTN TlvHandle::tlv_dev_msg_handle(TLV_DEV_MSG& tdm, TLV_HANDLE_DEV_MSG& dev_msg_handle)
{
	LOG_DEBUG("====== tlv_dev_msg_handle processing ======");

	//-------------- 打印入参
	LOG_DEBUG("---------- TLV_DEV_MSG content : ");
	LOG_DEBUG("state = " << (int)tdm.state << \
			", rssi = " << (int)tdm.rssi << \
			", version = " << tdm.version << \
			", voltage = " << tdm.voltage << \
			", flag = " << tdm.flag);
	LOG_DEBUG("---------- end.");

	stringstream ss;

	ss << (int)tdm.state;
	dev_msg_handle.state = ss.str();
	ss.str("");
	ss.clear();

	ss << (int)tdm.rssi;
	dev_msg_handle.rssi = ss.str();
	ss.str("");
	ss.clear();

	ss << tdm.version;
	dev_msg_handle.version = ss.str();
	ss.str("");
	ss.clear();

	ss << tdm.voltage;
	dev_msg_handle.voltage = ss.str();
	ss.str("");
	ss.clear();

	ss << tdm.flag;
	dev_msg_handle.flag = ss.str();
	ss.str("");
	ss.clear();

	//-------------- 打印出参
	LOG_DEBUG("---------- TLV_HANDLE_DEV_MSG content : ");
	LOG_DEBUG("dev_id = " << dev_msg_handle.dev_id << \
			", state = " << dev_msg_handle.state << \
			", rssi = " << dev_msg_handle.rssi << \
			", version = " << dev_msg_handle.version << \
			", voltage = " << dev_msg_handle.voltage << \
			", flag = " << dev_msg_handle.flag);
	LOG_DEBUG("---------- end.");

	return THR_OK;
}


TLV_HANDLE_RTN TlvHandle::tlv_parameter_handle(TLV_RTN& rtn, TLV_HANDLE_PARAMETER_RTN& parameter_handle)
{
	LOG_DEBUG("====== tlv_parameter_handle processing ======");

	//-------------- 打印入参
	LOG_DEBUG("---------- TLV_RTN content : ");
	LOG_DEBUG("rtn = " << (int)rtn);
	LOG_DEBUG("---------- end.");

	stringstream ss;

	ss << (int)rtn;
	parameter_handle.rtn = ss.str();
	ss.str("");
	ss.clear();

	//-------------- 打印出参
	LOG_DEBUG("---------- TLV_HANDLE_PARAMETER_RTN content : ");
	LOG_DEBUG("dev_id = " << parameter_handle.dev_id);
	LOG_DEBUG("rtn = " << parameter_handle.rtn);
	LOG_DEBUG("---------- end.");

	return THR_OK;
}


TLV_HANDLE_RTN TlvHandle::tlv_version_handle(TLV_RTN& rtn, TLV_HANDLE_VERSION_RTN& ver_handle)
{
	LOG_DEBUG("====== tlv_version_handle processing ======");

	//-------------- 打印入参
	LOG_DEBUG("---------- TLV_RTN content : ");
	LOG_DEBUG("rtn = " << (int)rtn);
	LOG_DEBUG("---------- end.");

	stringstream ss;

	ss << (int)rtn;
	ver_handle.rtn = ss.str();
	ss.str("");
	ss.clear();

	//-------------- 打印出参
	LOG_DEBUG("---------- TLV_HANDLE_VERSION_RTN content : ");
	LOG_DEBUG("dev_id = " << ver_handle.dev_id);
	LOG_DEBUG("rtn = " << ver_handle.rtn);
	LOG_DEBUG("---------- end.");

	return THR_OK;
}


TLV_HANDLE_RTN TlvHandle::tlv_manage_lbs_handle(TLV_MANAGE_LBS& m_lbs, TLV_HANDLE_MANAGE_LBS& m_lbs_handle)
{
	LOG_DEBUG("====== tlv_lbs_handle processing ======");

	//-------------- 打印入参
	LOG_DEBUG("---------- TLV_MANAGE_LBS content : ");
	printDateTime2k(m_lbs.dt);
	LOG_DEBUG("rssi = " << (int)m_lbs.rssi << \
			", state = " << (int)m_lbs.state << \
			", voltage = " << m_lbs.voltage << \
			", temperature = " << m_lbs.temperature);

	for(int i = 0; i < sizeof(m_lbs.ld)/sizeof(LbsData); i++)
	{
		LOG_DEBUG("cell = " << (int)m_lbs.ld[i].cell << \
				",mnc = " << (int)m_lbs.ld[i].mnc << \
				",mcc = " << m_lbs.ld[i].mcc << \
				",lac = " << m_lbs.ld[i].lac << \
				",cell_id = " << m_lbs.ld[i].cell_id << \
				",bsic = " << (int)m_lbs.ld[i].bsic << \
				", rssi = " << (int)m_lbs.ld[i].rssi);
	}

	LOG_DEBUG("---------- end.");

	//-------------- 处理参数
	char buf[64];
	stringstream ss;

	//时间
	m_lbs_handle.datetime = DateTime2String2k(m_lbs.dt);

	ss << (int)m_lbs.rssi;
	m_lbs_handle.rssi = ss.str();
	ss.str("");
	ss.clear();

	ss << (int)m_lbs.state;
	m_lbs_handle.state = ss.str();
	ss.str("");
	ss.clear();

	ss << m_lbs.voltage;
	m_lbs_handle.voltage = ss.str();
	ss.str("");
	ss.clear();

	memset(buf, 0, sizeof(buf));
	sprintf(buf, "%3.1f", (float)m_lbs.temperature/10);

	ss << buf;
	m_lbs_handle.temperature = ss.str();
	ss.str("");
	ss.clear();

	// LBS 转经纬度
	HttpInterface hi;
	if(hi.lbs2gps(m_lbs, m_lbs_handle.latitude, m_lbs_handle.longitude) _NEQ_ THR_OK)
	{
		m_lbs_handle.latitude = "000000000000";
		m_lbs_handle.longitude = "000000000000";
	}
	else
	{
		//移除字符 '.'
		string::iterator it_lat = remove_if(m_lbs_handle.latitude.begin(), m_lbs_handle.latitude.end(), bind2nd(equal_to<char>(), '.'));
		m_lbs_handle.latitude.erase(it_lat, m_lbs_handle.latitude.end());
		string::iterator it_longi = remove_if(m_lbs_handle.longitude.begin(), m_lbs_handle.longitude.end(), bind2nd(equal_to<char>(), '.'));
		m_lbs_handle.longitude.erase(it_longi, m_lbs_handle.longitude.end());

		//补到12位长度
		memset(buf, 0, sizeof(buf));
		sprintf(buf, "0%s", m_lbs_handle.latitude.c_str());
		ss << buf;
		m_lbs_handle.latitude = ss.str() + "000000000000";
		m_lbs_handle.latitude = m_lbs_handle.latitude.substr(0, 12);
		ss.str("");
		ss.clear();

		m_lbs_handle.longitude += "000000000000";
		m_lbs_handle.longitude = m_lbs_handle.longitude.substr(0, 12);
	}

	//-------------- 打印出参
	LOG_DEBUG("---------- TLV_HANDLE_MANAGE_LBS content : ");
	LOG_DEBUG("dev_id = " << m_lbs_handle.dev_id << \
			", datetime = " << m_lbs_handle.datetime);
	LOG_DEBUG("rssi = " << m_lbs_handle.rssi << \
			", state = " << m_lbs_handle.state << \
			", voltage = " << m_lbs_handle.voltage << \
			", temperature = " << m_lbs_handle.temperature);
	LOG_DEBUG("latitude = " << m_lbs_handle.latitude << \
			", longitude = " << m_lbs_handle.longitude);
	LOG_DEBUG("---------- end.");

	return THR_OK;
}