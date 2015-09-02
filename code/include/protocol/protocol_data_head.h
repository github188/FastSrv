/*
//
//	Last Modify Date: 2015-08-28
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
			MSG_NONE = 0x0000,						// 0x0000 无效命令
			MSG_LOGIN,								// 0x0001 终端登录
			MSG_LOGIN_OUT,							// 0x0002 退出请求
			MSG_CONNECT_CUTOVER,					// 0x0003 传输切换(收到该命令数据包下发缓存消息给对应终端)
			MSG_BIND_CUTOVER,						// 0x0004 绑定切换
			MSG_CHANGEFREQ_REP,						// 0x0005 心跳
			MSG_BIND_REP,							// 0x0006 绑定回复
			MSG_RELIEVE_BIND_REP,					// 0x0007 解绑回复
			MSG_DATA_UPLOAD = 0x000A,				// 0x000A 数据信息上传
			MSG_CCID_CHANGE = 0x000C,				// 0x000C CCID串号修改
			MSG_UPDATE_INFO = 0x000D,				// 0x000D 终端更新信息请求
			MSG_UPDATE_UNBIND = 0x000E,     		// 0x000E  终端请求解绑
			MSG_DEVICE_INFO_REP = 0x0010,			// 0x0010 下发信息回复
			MSG_PARAMETER_REP,						// 0x0011 参数配置下发回复
			MSG_LONLAT_REP,							// 0x0012 起止经纬度下发回复
			MSG_UPDATE_REP,							// 0x0013 升级信息下发回复
			MSG_SERVICE_LOCATION_REP,				// 0x0014 快速服务定位配置信息下发回复
			MSG_COMMUNICATION_CONFIG_REP,			// 0x0015 进程通讯配置信息下发回复
			MSG_SERVER_INFO_RES = 0x0020,			// 0x0020 服务器信息查询响应
			MSG_PARAMETER_RES,						// 0x0021 运行参数信息查询响应
			MSG_LONLAT_RES,							// 0x0022 起止经纬度查询响应
			MSG_UPDATE_RES,							// 0x0023 终端升级信息查询响应
			MSG_SERVICE_LOCATION_RES,				// 0x0024 快速服务定位信息查询响应
			MSG_COMMUNICATION_CONFIG_RES,			// 0x0025 进程通讯配置信息查询响应
			MSG_CCID_RES = 0x002C,					// 0x002C CCID串号请求包响应
			MSG_HARDWARE_INFO_RES = 0x002D  		// 0x002D 硬件信息查询响应
		};

		enum MSG_SERVER
		{
			MSG_CONNECT_CUTOVER_CONFIRM = 0x8003,	// 0x8003 传输切换确认
			MSG_BIND_CUTOVER_CONFIRM = 0x8004,		// 0x8004 终端绑定切换确认
			MSG_BIND_REQ = 0x8006,					// 0x8006 终端绑定请求
			MSG_DISCONNECT_REQ =0x8007,
			MSG_UPDATE_INFO_SEND = 0x800D,			// 0x800D 升级信息下发
			MSG_UPDATE_UNBIND_REPLY = 0x800E,       // 0x800E  终端解绑信息回复包
			MSG_DEVICE_INFO_ISS = 0x8010,			// 0x8010 下发信息（登录服务器,业务服务器）
			MSG_PARAMETER_ISS,						// 0x8011 参数配置下发回复
			MSG_LONLAT_ISS,							// 0x8012 起止经纬度下发回复SendingMsg
			MSG_UPDATE_ISS,							// 0x8013 升级信息下发回复
			MSG_SERVICE_LOCATION_ISS,				// 0x8014 快速服务定位配置信息下发回复
			MSG_COMMUNICATION_CONFIG_ISS,			// 0x8015 进程通讯配置信息下发回复
			MSG_SERVER_INFO_REQ = 0x8020,			// 0x8020 服务器信息查询
			MSG_PARAMETER_REQ,						// 0x8021 运行参数信息查询
			MSG_LONLAT_REQ,							// 0x8022 起止经纬度查询
			MSG_UPDATE_REQ,							// 0x8023 终端升级信息查询
			MSG_SERVICE_LOCATION_REQ,				// 0x8024 快速服务定位信息查询
			MSG_COMMUNICATION_CONFIG_REQ,			// 0x8025 进程通讯配置信息查询
			MSG_CCID_REQ = 0x802C,					// 0x802C CCID串号请求
			MSG_HARDWARE_INFO_REQ = 0x802D			// 0x802D 硬件信息查询
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