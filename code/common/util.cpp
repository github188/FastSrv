/*
//
//	Last Modify Date: 2015-08-28
//	Author: zengpw
//	History:
//					2015-08-12 zengpw created
//	File Property: public
//	Future:
//					I. 部分工具
//
//
*/

#include "util.h"

namespace common
{
	Error::Error()
	{
		id = "common-util-Error-0000";
		msg = "undefined error";
	}

	Error::Error(string eId,string eMsg)
	{
		id = eId;
		msg = eMsg;
	}

	void Error::set(string eId,string eMsg)
	{
		id = eId;
		msg = eMsg;
	}

	string Error::getId()
	{
		return id;
	}

	string Error::getMsg()
	{
		return msg;
	}

	void Error::print()
	{
		cout << endl;
		cout << "id = " << id << "msg = " << msg;
		cout << endl;
	}
};// namespace common
