/*
//
//	Last Modify Date: 2015-08-28
//	Author: zengpw
//	History:
//					2015-08-26 zengpw created
//	File Property: public
//	Future:
//					I. 消息处理（不涉及网络）
//
//
*/

#ifndef _BALANCE_HANDLE_H_
#define _BALANCE_HANDLE_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
#include "protocol/putil.h"
#include "protocol/protocol.h"

using namespace std;

class BalanceHandle
{
public:
	void dispatch(const protocol::Packet* in, protocol::Packet* out);
	void msgLogin(const protocol::Packet* in, protocol::Packet* out);
	void msgCutover(const protocol::Packet* in, protocol::Packet* out);
};

#endif