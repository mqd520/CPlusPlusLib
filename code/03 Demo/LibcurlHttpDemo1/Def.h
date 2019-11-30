#pragma once

#include <string>
using namespace std;


#define		$ProjectName					("LibcurlHttpDemo1.exe")			// Project name


// LibcurlHttp Info
typedef struct tagConfigLibcurlHttpInfo
{
	int nThreadCount;		// Thread count
	int nSleepTime;			// Thread sleep time(in ms)
	bool bProxy;			// Whether enable proxy
	string strProxyAddr;	// Proxy Addr
}ConfigLibcurlHttpInfo;	// LibcurlHttp Info


// Https Info
typedef struct tagConfigHttpsInfo
{
	string	url;		// url
	int		count;		// count
	string	method;		// method
	string	data;		// data
	string	contentType;// Content-Type
}ConfigHttpsInfo;	// Https Info