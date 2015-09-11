/*
//
//	Last Modify Date: 2015-09-11
//	Author: zengpw
//	History:
//					2015-08-27 zengpw created
//	File Property: public
//	Future:
//					I. 进程
//
//
*/

#include "process.h"

namespace common
{
	// key : "c:C:l:L:p:P:m:M:"
	void getConfigMap(int argc, char* argv[], string key, ConfigMap& mapConfig)
	{
		mapConfig.clear();

		StringSet SetString;
		common::split(key, ":", SetString);

		int opt;
		while((opt = getopt(argc, argv, key.c_str())) != -1)
		{
			char c[2] = {(char)opt, '\0'};
			string s(c, 1);
			StringSet::iterator iter = SetString.find(s);

			if(iter != SetString.end())
			{
				mapConfig[*iter] = string(optarg);
			}
		}

		ConfigMap::iterator iter;
		for(iter = mapConfig.begin(); iter != mapConfig.end(); ++iter)
		{
			printf("\n execute arg : %s = %s \n", iter->first.c_str(), iter->second.c_str());
		}
	}
};// namespace common
