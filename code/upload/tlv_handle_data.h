/*
//
//	Last Modify Date: 2015-12-25
//	Author: zengpw
//	History:
//					2015-10-20 zengpw created
//	File Property: private
//	Future:
//					I. tlv 消息处理
//
//
*/

#ifndef _TLV_HANDLE_DATA_H_
#define _TLV_HANDLE_DATA_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
#include "common/log.h"

using namespace std;

typedef enum TLV_HANDLE_RTN
{
	THR_OK = 0x01,					//处理正确，返回值需要处理
	THR_TRUE = 0x02,				//处理正确，返回值不需要处理
	THR_FAIL = 0x04,				//处理错误，并且需要处理错误
	THR_ERROR = 0x08				//处理错误，但是可以忽略错误
}TLV_HANDLE_RTN;


//公共结构体 BasicData 的处理结果
typedef struct HANDLE_BasicData
{
	string rssi;									//场强
	string move;									//移动标记
	string flag;									// =0 光曝正常； =1 光曝报警
	string voltage;									//电压
	string temperature;								//温度
	string exposure;								//光曝
	//额外数据
	string alarm;
	string addr;
}HANDLE_BasicData;

//标准报文 TLV_DEV_FIRM 的处理结果
typedef struct TLV_HANDLE_DEV_FIRM
{
	string dev_id;
	string version;
	string imei;
	string iccid;
}TLV_HANDLE_DEV_FIRM;

//标准报文 TLV_DEV_MSG 的处理结果
typedef struct TLV_HANDLE_DEV_MSG
{
	string dev_id;
	string state;
	string rssi;
	string version;
	string voltage;
	string flag;
}TLV_HANDLE_DEV_MSG;

//标准报文 TLV_GPS 的处理结果
typedef struct TLV_HANDLE_GPS
{
	string dev_id;
	string order_id;
	string datetime;
	HANDLE_BasicData hbd;
	string latitude;
	string longitude;
	//额外数据
	string mode;									// 0 = gps; 1 = lbs
}TLV_HANDLE_GPS;

//标准报文 TLV_LBS 的处理结果
typedef struct TLV_HANDLE_LBS
{
	string dev_id;
	string order_id;
	string datetime;
	HANDLE_BasicData hbd;
	string latitude;
	string longitude;
	//额外数据
	string mode;									// 0 = gps; 1 = lbs
}TLV_HANDLE_LBS;

//标准报文 TLV_TH 的处理结果
typedef struct TLV_HANDLE_TH
{
	string dev_id;
	string order_id;
	string datetime;
	string datetime_gps;
	string alarm;
	string t0;
	string h0;
	//额外数据
	//温度绝对值超过80℃则标记
	string overflow;
}TLV_HANDLE_TH;

//标准报文 CID_UNBAND - TLV_RTN 的处理结果
typedef struct TLV_HANDLE_UNBAND_RTN
{
	string dev_id;
	string rtn;
}TLV_HANDLE_UNBAND_RTN;

//标准报文 CID_DEV_UNBAND - TLV_RTN 的处理结果
typedef struct TLV_HANDLE_DEV_UNBAND_RTN
{
	string dev_id;
	string datetime;
}TLV_HANDLE_DEV_UNBAND_RTN;

//标准报文 CID_PARAMETER - TLV_RTN 的处理结果
typedef struct TLV_HANDLE_PARAMETER_RTN
{
	string dev_id;
	string rtn;
}TLV_HANDLE_PARAMETER_RTN;

//标准报文 CID_PARAMETER_VERSION - TLV_RTN 的处理结果
typedef struct TLV_HANDLE_VERSION_RTN
{
	string dev_id;
	string rtn;
}TLV_HANDLE_VERSION_RTN;

//标准报文 TLV_MANAGE_LBS 的处理结果
typedef struct TLV_HANDLE_MANAGE_LBS
{
	string dev_id;
	string datetime;
	string rssi;
	string state;
	string voltage;
	string temperature;
	string latitude;
	string longitude;
}TLV_HANDLE_MANAGE_LBS;

//标准报文 TLV_TH2 的处理结果
typedef struct TLV_HANDLE_TH2
{
	string dev_id;
	string order_id;
	string datetime;
	string datetime_gps;
	string alarm;
	string t0;
	string h0;
	string t1;
	string h1;
	//额外数据
	//温度绝对值超过80℃则标记
	string overflow;
}TLV_HANDLE_TH2;

#endif