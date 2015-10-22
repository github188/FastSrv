/*
//
//	Last Modify Date: 2015-10-16
//	Author: zengpw
//	History:
//					2015-08-19 zengpw created
//	File Property: public
//	Future:
//					I. tlv 基础结构
//
//
*/

#ifndef _PROTOCOL_TLV_SYS_H_
#define _PROTOCOL_TLV_SYS_H_

#include <vector>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
#include "common/log.h"

using namespace std;

namespace protocol
{
	namespace tlv
	{
		#pragma pack(push, 1)

		enum CID
		{
			CID_LOGIN = 0x0001,							//登录/注册
			CID_DEV_MSG = 0x0002,						//设备信息
			CID_UNBAND = 0x0003,						//远程解绑
			CID_DEV_UNBAND = 0x0004,					//设备发起解绑
			CID_DEV_BAND = 0x0005,						//设备发起绑定
			CID_PARAMETER = 0x0006,						//运行参数下发
			CID_PARAMETER_REQUEST = 0x0007,				//设备请求运行参数
			CID_PARAMETER_VERSION = 0x0008,				//版本升级参数下发
			CID_DEV_INIT = 0x0009,						//初始化终端
			CID_DEV_TIME = 0x000A,						//终端时间校正
			CID_DATA_GPS = 0x000B,						//gps数据上传
			CID_DATA_LBS = 0x000C,						//lbs数据上传
			CID_DATA_TH = 0x000D,						//温湿度数据上传
			CID_DATA_EXPOSURE = 0x000E					//光曝
		};

		enum TID
		{
			TID_DEV_FIRM = 0x01,					//协议版本
			TID_TIME = 0x02,						//时间
			TID_DEV_MSG = 0x03,						//设备信息
			TID_RTN = 0x04,							//1 = 成功； 0 = 失败
			TID_ORDER_ID = 0x05,					//订单号
			TID_PARAMETER = 0x06,					//运行参数
			TID_PARAMETER_VERSION = 0x07,			//版本升级参数
			TID_GPS = 0x08,							//gps上传数据
			TID_LBS = 0x09,							//lbs上传数据
			TID_TH = 0x0A,							//温湿度上传数据
			TID_EXPOSURE = 0x0B						//光曝上传数据
		};

		typedef struct Head
		{
			unsigned char	xcode[4];
			unsigned char	dev_id[12];
			unsigned short	cid;
			int				build_time;
			unsigned short	len;
		}Head;
		typedef Head* HeadPtr;

		typedef struct TLV
		{
			char type;
			char len;
			char* value;

			TLV()
			{
				value = NULL;
			}
		}TLV;
		typedef vector<TLV> TLVGroup;
		typedef const TLVGroup* TLVGroupPtr;
		typedef TLVGroup::const_iterator TLVGroupIter;

		#pragma pack(pop)
	}// namespace tlv
};// namespace protocol

#endif