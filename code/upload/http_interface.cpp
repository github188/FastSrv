/*
//
//	Last Modify Date: 2015-11-19
//	Author: zengpw
//	History:
//					2015-10-22 zengpw created
//	File Property: private
//	Future:
//					I. http 操作
//
//
*/

#include "http_interface.h"

TLV_HANDLE_RTN HttpInterface::lbs2gps(TLV_LBS& lbs, string& latitude, string& longitude)
{
	LOG_DEBUG("---------- lbs2gps filter : ");

	vector<LbsData> vLbs;

	for(int i = 0; i < sizeof(lbs.ld)/sizeof(LbsData); i++)
	{
		if(lbs.ld[i].lac != 0 && lbs.ld[i].cell_id != 0 && (int)lbs.ld[i].rssi != 0 && (int)lbs.ld[i].mcc == 460)
		{
			LOG_DEBUG("cell = " << (int)lbs.ld[i].cell << \
					",mnc = " << (int)lbs.ld[i].mnc << \
					",mcc = " << lbs.ld[i].mcc << \
					",lac = " << lbs.ld[i].lac << \
					",cell_id = " << lbs.ld[i].cell_id << \
					",bsic = " << (int)lbs.ld[i].bsic << \
					", rssi = " << (int)lbs.ld[i].rssi);

			vLbs.push_back(lbs.ld[i]);
		}
	}

	LOG_DEBUG("---------- end.");

	return lbs2gpsAmap(vLbs, latitude, longitude);
}


TLV_HANDLE_RTN HttpInterface::lbs2gps(TLV_MANAGE_LBS& m_lbs, string& latitude, string& longitude)
{
	LOG_DEBUG("---------- lbs2gps filter : ");

	vector<LbsData> vLbs;

	for(int i = 0; i < sizeof(m_lbs.ld)/sizeof(LbsData); i++)
	{
		if(m_lbs.ld[i].lac != 0 && m_lbs.ld[i].cell_id != 0 && (int)m_lbs.ld[i].rssi != 0 && (int)m_lbs.ld[i].mcc == 460)
		{
			LOG_DEBUG("cell = " << (int)m_lbs.ld[i].cell << \
					",mnc = " << (int)m_lbs.ld[i].mnc << \
					",mcc = " << m_lbs.ld[i].mcc << \
					",lac = " << m_lbs.ld[i].lac << \
					",cell_id = " << m_lbs.ld[i].cell_id << \
					",bsic = " << (int)m_lbs.ld[i].bsic << \
					", rssi = " << (int)m_lbs.ld[i].rssi);

			vLbs.push_back(m_lbs.ld[i]);
		}
	}

	LOG_DEBUG("---------- end.");

	return lbs2gpsAmap(vLbs, latitude, longitude);
}


TLV_HANDLE_RTN HttpInterface::lbs2gpsAmap(vector<LbsData> &vLbs, string& latitude, string& longitude)
{
	stringstream ss;

	string bts = "";
	string nearbts = "";
	string request = "";

	if(vLbs.size() > 0)
	{
		ss << (int)vLbs[0].mcc;
		bts += ss.str() + ",";
		ss.str("");
		ss.clear();

		ss << (int)vLbs[0].mnc;
		bts += ss.str() + ",";
		ss.str("");
		ss.clear();

		ss << (int)vLbs[0].lac;
		bts += ss.str() + ",";
		ss.str("");
		ss.clear();

		ss << (int)vLbs[0].cell_id;
		bts += ss.str() + ",";
		ss.str("");
		ss.clear();

		ss << (int)vLbs[0].rssi - 111;
		bts += ss.str();
		ss.str("");
		ss.clear();

		for(int i = 1; i < vLbs.size(); i++)
		{
			ss << (int)vLbs[0].mcc;
			nearbts += ss.str() + ",";
			ss.str("");
			ss.clear();

			ss << (int)vLbs[0].mnc;
			nearbts += ss.str() + ",";
			ss.str("");
			ss.clear();

			ss << (int)vLbs[0].lac;
			nearbts += ss.str() + ",";
			ss.str("");
			ss.clear();

			ss << (int)vLbs[0].cell_id;
			nearbts += ss.str() + ",";
			ss.str("");
			ss.clear();

			ss << (int)vLbs[0].rssi - 111;
			nearbts += ss.str() + "|";
			ss.str("");
			ss.clear();
		}

		request = "http://apilocate.amap.com/position?accesstype=0&imei=866104021101384&cdma=0&bts=";
		request += bts;

		if(nearbts.length() > 0)
		{
			nearbts = nearbts.substr(0, nearbts.length() - 1);

			request += "&nearbts=";
			request += nearbts;
		}

		request += "&output=json&key=fe0d26ade7f0dc72e2d2efa4d10fc259";
		LOG_DEBUG("request : " << request);

		if(!python_call.py_requestAmap(request, latitude, longitude))
		{
			return THR_FAIL;
		}
	}
	else
	{
		//如果是整个 LBS 包被过滤了，则返回全0
		latitude = "000000000000";
		longitude = "000000000000";
	}

	return THR_OK;
}


TLV_HANDLE_RTN HttpInterface::gps2addrAmap(const string& latitude, const string& longitude, string& addr)
{
	//地址转换
	char buf[24];
	stringstream ss;
	double dx, dy;
	string x, y;

	ss << latitude;
	ss >> dx;
	ss.str("");
	ss.clear();

	// 11位数字（第1位是0，在转换成 double 类型时丢失），去掉后面的0；剩下7位数字，然后除以 100000
	memset(buf, 0, sizeof(buf));
	sprintf(buf, "%3.3f", dx/100000/10000);
	ss << buf;
	ss >> x;
	ss.str("");
	ss.clear();

	ss << longitude;
	ss >> dy;
	ss.str("");
	ss.clear();

	// 12位数字，去掉后面的0；剩下8位数字，然后除以 100000
	memset(buf, 0, sizeof(buf));
	sprintf(buf, "%3.3f", dy/100000/10000);
	ss << buf;
	ss >> y;
	ss.str("");
	ss.clear();

	//查询
	string request;

	request = "http://restapi.amap.com/v3/geocode/regeo?location=";
	request += y + ",";
	request += x;
	request += "&extensions=all&output=json&key=44e606a9c5a628e9a8bd42226249f84c";

	LOG_DEBUG("request : " << request);

	if(python_call.py_requestAmapUseAddr(request, addr))
	{
		if(addr.length() _EQ_ 0)
		{
			addr = "未获取到定位数据";
		}

		return THR_OK;
	}

	if(addr.length() _EQ_ 0)
	{
		addr = "未获取到定位数据";
	}

	return THR_FAIL;
}