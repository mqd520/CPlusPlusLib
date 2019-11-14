#include "stdafx.h"
#include "Include/http/RequestLine.h"

#include "com/BufferTool.h"
#include "com/StringTool.h"
using namespace com;


namespace http
{
	RequestLine::RequestLine(const string& method /*= "GET"*/) :
		strMethod(method)
	{

	}

	string RequestLine::GetProtocolName()
	{
		vector<string> vec = StringTool::Split(strProtocol, "/");

		return vec[0];
	}

	string RequestLine::GetProtocolVersion()
	{
		vector<string> vec = StringTool::Split(strProtocol, "/");

		return vec[1];
	}

	int RequestLine::GenerateBuf(BYTE* pBuf, int len)
	{
		int nTotal = 0;

		string str = strMethod + " " + strAbsolutePath + " " + strProtocol + "\r\n";

		nTotal = BufferTool::Copy(pBuf, len, (BYTE*)str.c_str(), str.length());

		return nTotal;
	}

	void RequestLine::Reset(const string& method, const string& path, const string& protocol)
	{
		strMethod = method;
		strAbsolutePath = path;
		strProtocol = protocol;

		if (!path.empty())
		{
			vector<string> vec1 = StringTool::Split(path, "?");
			if (vec1.size() == 2 && !vec1[1].empty())
			{
				vector<string> vec2 = StringTool::Split(vec1[1], "&");
				for (auto & it : vec2)
				{
					if (!it.empty())
					{
						vector<string> vec3 = StringTool::Split(it, "=");
						if (vec3.size() == 2)
						{
							pair<string, string> item = { vec3[0], vec3[1] };
							vecQueryParams.emplace_back(item);
						}
						else
						{
							pair<string, string> item = { vec3[0], "" };
							vecQueryParams.emplace_back(item);
						}
					}
				}
			}
		}
	}

	int RequestLine::ParseFromBuf(BYTE* pBuf, int len, RequestLine& line, bool& bSuccess)
	{
		int result = 0;
		bool b = false;

		string strMethod = "";
		string strPath = "";
		string strProtocol = "";

		string str1 = (char*)pBuf;
		int n1 = str1.find("\r\n");
		if (n1 > 0)
		{
			string str2 = str1.substr(0, n1);
			vector<string> vec = StringTool::Split(str2, " ");
			if (vec.size() == 3)
			{
				if (vec[0] == "GET" || vec[0] == "POST")
				{
					strMethod = vec[0];
					if (!vec[1].empty() && vec[1].substr(0, 1) == "/")
					{
						strPath = vec[1];
						if (!vec[2].empty())
						{
							vector<string> vec1 = StringTool::Split(vec[2], "/");
							if (vec1.size() == 2)
							{
								if (vec1[0] == "HTTP" || vec1[0] == "HTTPS")
								{
									strProtocol = vec[2];

									result = n1 + 2;
									b = true;
								}
							}
						}
					}
				}
			}
		}

		line.Reset(strMethod, strPath, strProtocol);

		bSuccess = b;

		return result;
	}
}