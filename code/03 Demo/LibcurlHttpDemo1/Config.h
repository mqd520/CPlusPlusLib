#pragma once

#include <vector>
using namespace std;

#include "Def.h"


// Config
class Config
{
public:
	Config();

public:
	ConfigLibcurlHttpInfo	libcurlHttp;	// Libcurl Http info
	vector<ConfigHttpsInfo>	vecHttps;		// Https list
	//string					dbConnection;	// Db connection
	int						taskSleepTime;	// Task sleep time
	string					strDbServiceAddr;// Db Service Addr

public:
	//************************************
	// Method:    Init
	//************************************
	void Init();
};

extern Config _cfg;		// the only Config object