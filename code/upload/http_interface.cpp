/*
//
//	Last Modify Date: 2015-10-23
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

		if(python_call.py_requestAmap(request, latitude, longitude))
		{
			return THR_OK;
		}
	}

	return THR_FAIL;
}