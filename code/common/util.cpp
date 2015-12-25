/*
//
//	Last Modify Date: 2015-12-25
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
	//字符串拆分
	void split(const string& in, const string delimiter, StringSet& out)
	{
		string::size_type cur = 0;
		string::size_type next = 0;

		next = in.find(delimiter, cur);

		while(next != std::string::npos)
		{
			out.insert(in.substr(cur, next - cur));
			cur = next + 1;
			next = in.find(delimiter, cur);
		}

		out.insert(in.substr(cur));
	}

	// 16进制打印
	char hex2char(int hex)
	{
		char c_res = ' ';
		// 0~9转换成对应字符,转为'0'~'9'
		if (hex >= 0 && hex <= 9)
		{
			c_res = char(hex + '0');
		}
		// 10~15十六进制为a~f,转换为'a'~'f'
		else if (hex >= 10 && hex <= 15)
		{
			c_res = char(hex - 10 + 'A');
		}

		return c_res;
	}

	string printByHex(const char* message, const int length)
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

		// LOG_DEBUG(out);

		return out;
	}

	string printByHex(const unsigned char* message, const int length)
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

		// LOG_DEBUG(out);

		return out;
	}

	//进制转换
	string int2binary(const int i, const int reverse)
	{
		std::bitset<std::numeric_limits<int>::digits> bs(i);
		std::string str;

		if(reverse)
		{
			/* cut data on first character '1' */
			str = bs.to_string().substr(bs.to_string().find('1'));
			std::replace(str.begin(),str.end(),'0','X');
			std::replace(str.begin(),str.end(),'1','0');
			std::replace(str.begin(),str.end(),'X','1');
			str = str.substr(str.find('1'));
		}
		else
		{
			/* cut data on first character '1' */
			str = bs.to_string().substr(bs.to_string().find('1'));
		}

		return str;
	}

	string uchar2binary(const unsigned char i)
	{
		std::bitset<std::numeric_limits<unsigned char>::digits> bs(i);
		std::string str;
		str = bs.to_string();

		return str;
	}

	int binary2int(const string& str)
	{
		std::bitset<std::numeric_limits<int>::digits> bs(str);

		return (int)bs.to_ulong();
	}

	//生成当前时间
	string buildDateTime()
	{
		struct timeval tv;
		gettimeofday(&tv, NULL);

		struct tm* pst;
		pst = localtime(&tv.tv_sec);

		string sdt;

		char buf[36];
		memset(buf, 0, sizeof(buf));
		sprintf(buf, "%04d%02d%02d%02d%02d%02d", pst->tm_year + 1900, pst->tm_mon + 1, pst->tm_mday, pst->tm_hour, pst->tm_min, pst->tm_sec);

		stringstream ss;

		ss << buf;
		sdt = ss.str();
		ss.str("");
		ss.clear();

		return sdt;
	}

	//生成当前时间（秒数）
	long long buildDateTimeSecond()
	{
		struct timeval tv;
		gettimeofday(&tv, NULL);

		return tv.tv_sec;
	}
};// namespace common
