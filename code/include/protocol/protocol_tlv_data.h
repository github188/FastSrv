/*
//
//	Last Modify Date: 2015-10-22
//	Author: zengpw
//	History:
//					2015-09-24 zengpw created
//	File Property: public
//	Future:
//					I. tlv 子协议结构
//
//
*/

#ifndef _PROTOCOL_TLV_DATA_H_
#define _PROTOCOL_TLV_DATA_H_

#include "protocol_tlv_sys.h"

using namespace std;

namespace protocol
{
	namespace tlv
	{
		#pragma pack(push, 1)

		//公共结构体 - 时间
		typedef struct DateTime
		{
			char year;
			char mon;
			char day;
			char hour;
			char min;
			char sec;
		}DateTime;
		DateTime buildDateTime2k();
		DateTime buildDateTime(char year, char mon, char day, char hour, char min, char sec);
		void printDateTime2k(DateTime& dt);
		string DateTime2String2k(DateTime& dt);

		//公共结构体 - 基础数据
		typedef struct BasicData
		{
			unsigned char rssi;								//场强
			unsigned char move;								//移动标记
			unsigned short voltage;							//电压
			short temperature;								//温度
			unsigned short exposure;						//光曝
		}BasicData;

		//公共结构体 - lbs信息
		typedef struct LbsData
		{
			unsigned char cell;
			unsigned char mnc;
			unsigned short mcc;
			unsigned short lac;
			unsigned short cell_id;
			unsigned char bsic;
			unsigned char rssi;
		}LbsData;

		//标准报文 - TLV_RTN
		typedef char TLV_RTN;

		//标准报文 - TLV_GPS
		typedef struct TLV_GPS
		{
			DateTime dt;
			BasicData bd;
			unsigned char sn_lat;							//南纬北纬
			unsigned char ew_long;							//东经西经
			unsigned int latitude;							//纬度
			unsigned int longitude;							//经度
		}TLV_GPS;

		//标准报文 - TLV_LBS
		typedef struct TLV_LBS
		{
			DateTime dt;
			BasicData bd;
			LbsData ld[3];
		}TLV_LBS;

		//标准报文 - TLV_TH
		typedef struct TLV_TH
		{
			DateTime dt;
			unsigned char alarm;
			unsigned short t0;
			unsigned short h0;
		}TLV_TH;

		#pragma pack(pop)
	}// namespace tlv
};// namespace protocol

#endif