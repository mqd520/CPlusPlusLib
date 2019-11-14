#include "stdafx.h"
#include "Include/http/Url.h"

#include <assert.h>
#include <regex>

#include "com/StringTool.h"
using namespace com;


namespace http
{
	Url::Url(string url) :
		strAbsoluteUrl(url)
	{
		if (url.empty())
		{
			return;
		}

		string strTmpUrl = strAbsoluteUrl;

		// parse http protocol
		strHttpProtocol = "HTTP/1.1";
		string strTmpUrl1 = StringTool::ToLower(strTmpUrl);
		if ((int)strTmpUrl1.find("https://") > -1)
		{
			strTmpUrl = strTmpUrl.substr(strlen("https://"));
			strHttpProtocol = "HTTPS/1.1";
			nPort = 443;
		}
		else
		{
			nPort = 80;
			if ((int)strTmpUrl1.find("http://") > -1)
			{
				strTmpUrl = strTmpUrl.substr(strlen("http://"));
			}
		}


		// parse ip or domain name
		smatch result;
		regex pattern1(R"((?=(\b|\D))(((\d{1,2})|(1\d{1,2})|(2[0-4]\d)|(25[0-5]))\.){3}((\d{1,2})|(1\d{1,2})|(2[0-4]\d)|(25[0-5]))(?=(\b|\D)))", regex::icase);
		if (regex_search(strTmpUrl, result, pattern1))
		{
			strHostAddr = result[0];
			strHost = result[0];
			nHostType = EHostType::Ip;
			strTmpUrl = strTmpUrl.substr(strlen(strHostAddr.c_str()));
		}
		else
		{
			regex pattern2(R"((?=^.{3,255}$)[a-zA-Z0-9][-a-zA-Z0-9]{0,62}(\.[a-zA-Z0-9][-a-zA-Z0-9]{0,62})+)", regex::icase);
			if (regex_search(strTmpUrl, result, pattern2))
			{
				strHostAddr = result[0];
				strHost = result[0];
				nHostType = EHostType::Domainname;
				strTmpUrl = strTmpUrl.substr(strlen(strHostAddr.c_str()));
			}
			else
			{
				assert(false);
			}
		}


		// parse port if that exist
		regex pattern3(R"(:\d{0,5})", regex::icase);
		if (regex_search(strTmpUrl, result, pattern3))
		{
			string tmp = result[0];
			nPort = atoi(tmp.substr(1).c_str());
			strHost += tmp;
			strTmpUrl = strTmpUrl.substr(strlen(tmp.c_str()));
		}


		// parse absolute path
		if (!strTmpUrl.empty())
		{
			strAbsolutePath = strTmpUrl;
		}
		else
		{
			strAbsolutePath = "/";
		}


		// parse query param 
		if ((int)strAbsolutePath.find("?") > -1)
		{
			vector<string> vec = StringTool::Split(strAbsolutePath, "?");
			strRequestPath = vec[0];
			if (vec.size() > 1)
			{
				strQueryParam = vec[1];
				vector<string> vec1 = StringTool::Split(strQueryParam, "&");
				for (vector<string>::iterator it = vec1.begin(); it != vec1.end(); it++)
				{
					if (!it->empty())
					{
						if ((int)it->find("=") > -1)
						{
							vector<string> vec2 = StringTool::Split(*it, "=");
							if (vec2.size() == 2)
							{
								vecParam.push_back({ vec2[0], vec2[1] });
							}
							else
							{
								vecParam.push_back({ vec2[0], "" });
							}
						}
					}
				}
			}
			else
			{
				strQueryParam = "";
			}
		}
		else
		{
			strRequestPath = strAbsolutePath;
			strQueryParam = "";
		}
	}

	string Url::GetAbsoluteUrl() const
	{
		return strAbsoluteUrl;
	}

	string Url::GetHttpProtocol() const
	{
		return strHttpProtocol;
	}

	string Url::GetHost() const
	{
		return strHost;
	}

	string Url::GetHostAddr() const
	{
		return strHostAddr;
	}

	EHostType Url::GetHostType() const
	{
		return nHostType;
	}

	int Url::GetPort() const
	{
		return nPort;
	}

	string Url::GetAbsolutePath() const
	{
		return strAbsolutePath;
	}

	string Url::GetRequestPath() const
	{
		return strRequestPath;
	}

	string Url::GetQueryParam() const
	{
		return strQueryParam;
	}

	vector<pair<string, string>> Url::GetParamList() const
	{
		return vecParam;
	}
}