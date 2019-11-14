#pragma once

#include <string>
#include <vector>
using namespace std;

#include "HttpSubObject.h"


namespace http
{
	// Host type
	enum  class EHostType : int
	{
		Ip = 1,				// ip

		Domainname = 2		// domainname
	};


	// Url
	class Url : public HttpSubObject
	{
	public:
		Url(string url);

	protected:
		string strAbsoluteUrl;		// absolute url
		string strHttpProtocol;		// http protocol
		string strHost;				// host
		string strHostAddr;			// addr
		EHostType nHostType;		// host type
		int nPort;					// port
		string strAbsolutePath;		// absolute path
		string strRequestPath;		// request path(not include query param)
		string strQueryParam;		// query param
		vector<pair<string, string>> vecParam;

	public:
		//************************************
		// Method:    Get Absolute Url
		//************************************
		string GetAbsoluteUrl() const;

		//************************************
		// Method:    Get Http protocol
		//************************************
		string GetHttpProtocol() const;

		//************************************
		// Method:    Get Host
		//************************************
		string GetHost() const;

		//************************************
		// Method:    Get Host addr
		//************************************
		string GetHostAddr() const;

		//************************************
		// Method:    Get Host type
		//************************************
		EHostType GetHostType() const;

		//************************************
		// Method:    Get Port
		//************************************
		int GetPort() const;

		//************************************
		// Method:    Get Absolute path
		//************************************
		string GetAbsolutePath() const;

		//************************************
		// Method:    Get Request path
		//************************************
		string GetRequestPath() const;

		//************************************
		// Method:    Get query param
		//************************************
		string GetQueryParam() const;

		//************************************
		// Method:    Get query param
		//************************************
		vector<pair<string, string>> GetParamList() const;
	};
}