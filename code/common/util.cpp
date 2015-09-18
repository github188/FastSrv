/*
//
//	Last Modify Date: 2015-09-11
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
	void split(const string& in, const string delimiter, StringSet& out)
	{
		int cur = 0;
		int next = 0;

		next = in.find(delimiter, cur);

		while(next != std::string::npos)
		{
			out.insert(in.substr(cur, next - cur));
			cur = next + 1;
			next = in.find(delimiter, cur);
		}

		out.insert(in.substr(cur));
	}
};// namespace common
