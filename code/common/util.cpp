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


	char hex2char(int hex)
	{
		char c_res = ' ';
		// 0~9转换成对应字符,转为'0'~'9'
		if (hex >= 0 && hex <= 9)
		{
			c_res = char(hex + '0');
		}
		// 10~15十六进制为a~f,转换为'a'~'9'
		else if (hex >= 10 && hex <= 15)
		{
			c_res = char(hex - 10 + 'A');
		}

		return c_res;
	}


	// 16进制打印
	void printByHex(const char* message, const int length)
	{
		string out;

		for (int i = 0; i < length; i++)
		{
			int k = (unsigned char)*(message + i)/ 16;
			out += hex2char(k);
			k = (unsigned char)*(message + i)% 16;
			out += hex2char(k);
			out += " ";
		}

		LOG_DEBUG(out);

		return;
	}


	void printByHexU(unsigned char* message, int length)
	{
		string out;

		for (int i = 0; i < length; i++)
		{
			int k = (unsigned char)*(message + i)/ 16;
			out += hex2char(k);
			k = (unsigned char)*(message + i)% 16;
			out += hex2char(k);
			out += " ";
		}

		LOG_DEBUG(out);

		return;
	}
};// namespace common
