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
	string move;									//移动标记
	string voltage;									//电压
	string temperature;								//温度
	string exposure;								//光曝
}HANDLE_BasicData;


//标准报文 TLV_GPS 的处理结果
typedef struct TLV_HANDLE_GPS
{
	//处理后的原始数据
	string datetime;
	HANDLE_BasicData hbd;
	string latitude;
	string longitude;
	//额外的数据
	string mode;									// 0 = gps; 1 = lbs
}TLV_HANDLE_GPS;


//标准报文 TLV_LBS 的处理结果
typedef struct TLV_HANDLE_LBS
{
	string datetime;
	HANDLE_BasicData hbd;
	string latitude;
	string longitude;
	//额外的数据
	string mode;									// 0 = gps; 1 = lbs
}TLV_HANDLE_LBS;

#endif