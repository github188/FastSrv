/*
//
//	Last Modify Date: 2015-09-17
//	Author: zengpw
//	History:
//					2015-08-19 zengpw created
//	File Property: public
//	Future:
//					I. 协议的一部分
//
//
*/

#ifndef _PROTOCOL_DATA_HEAD_H_
#define _PROTOCOL_DATA_HEAD_H_

#include <vector>

using namespace std;

namespace protocol
{
	namespace data
	{
		enum MSG_CLIENT
		{
			MSG_TIME = 0x0001,						// 0x0001 终端登录
			MSG_CUTOVER = 0x0003,					// 0x0003 请求逻辑服务器信息
			MSG_UPLOAD = 0x000A						// 0x000A 数据上传
		};

		enum MSG_SERVER
		{
			MSG_TIME_REP = 0x8001,					// 0x0001 终端登录
			MSG_UPLOAD_REP = 0x800A,				// 0x800A 数据上传
			MSG_CUTOVER_REP = 0x8010				// 0x8010 下发逻辑服务器信息
		};

		typedef struct Head
		{
			unsigned char	bcc_code[4];
			unsigned short	len;
			unsigned short	command_id;
			unsigned short	seq;
			unsigned char	device_id[12];
			unsigned char	version;
			unsigned char	reserve[2];
			unsigned char	other;
		}Head;
		typedef Head* HeadPtr;
		typedef vector<Head> HeadVec;
		typedef vector<HeadPtr> HeadPtrVec;
	}// namespace data
};// namespace protocol

#endif