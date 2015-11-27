/*
//
//	Last Modify Date: 2015-11-12
//	Author: zengpw
//	History:
//					2015-09-24 zengpw created
//	File Property: public
//	Future:
//					I. task 单元测试
//
//
*/

#ifndef _TERMINAL_UT_HANDLE_H_
#define _TERMINAL_UT_HANDLE_H_

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
#include "protocol/putil.h"
#include "protocol/protocol_tlv.h"
#include "session/handle_basic.h"

using namespace std;

class TerminalUtHandle : public session::HandleBasic
{
public:
	session::HANDLE_RTN conn(protocol::PacketOut* out);
	session::HANDLE_RTN empty_build(protocol::PacketOut* out);
	session::HANDLE_RTN error_crc_build(protocol::PacketOut* out);
	session::HANDLE_RTN cidDataGps_build(protocol::PacketOut* out);
	session::HANDLE_RTN cidDataGps(const protocol::PacketIn* in, protocol::PacketOut* out);
	session::HANDLE_RTN cidDataLbs_build(protocol::PacketOut* out);
	session::HANDLE_RTN cidDataLbs(const protocol::PacketIn* in, protocol::PacketOut* out);
	session::HANDLE_RTN cidDataTh_build(protocol::PacketOut* out);
	session::HANDLE_RTN cidDataTh(const protocol::PacketIn* in, protocol::PacketOut* out);
	session::HANDLE_RTN cidUnband(const protocol::PacketIn* in, protocol::PacketOut* out);
	session::HANDLE_RTN cidDevband_build(protocol::PacketOut* out);
	session::HANDLE_RTN cidDevband(const protocol::PacketIn* in, protocol::PacketOut* out);
	session::HANDLE_RTN cidParameter_build(protocol::PacketOut* out);
	session::HANDLE_RTN cidParameter(const protocol::PacketIn* in, protocol::PacketOut* out);
	session::HANDLE_RTN cidParameterVersion_build(protocol::PacketOut* out);
	session::HANDLE_RTN cidParameterVersion(const protocol::PacketIn* in, protocol::PacketOut* out);
	session::HANDLE_RTN cidManageLbs_build(protocol::PacketOut* out);
	session::HANDLE_RTN cidManageLbs(const protocol::PacketIn* in, protocol::PacketOut* out);
};

#endif