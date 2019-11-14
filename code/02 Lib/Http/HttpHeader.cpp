#include "stdafx.h"
#include "Include/http/HttpHeader.h"

#include "Include/http/HttpRequest.h"
#include "Include/http/HttpHeaderDef.h"

#include "com/StringTool.h"
#include "com/BufferTool.h"
using namespace com;


namespace http
{
	map<string, string>::iterator HttpHeader::FindHeader(const string& key)
	{
		for (map<string, string>::iterator it = mapHeaders.begin(); it != mapHeaders.end(); it++)
		{
			string str1 = StringTool::ToLower(key);
			string str2 = StringTool::ToLower(it->first);
			if (str1 == str2)
			{
				return it;
				break;
			}
		}

		return mapHeaders.end();
	}

	bool HttpHeader::IsExistHeader(const string& key)
	{
		map<string, string>::iterator it = FindHeader(key);
		if (it != mapHeaders.end())
		{
			return true;
		}

		return false;
	}

	void HttpHeader::SetHeader(const string& key, const string& val)
	{
		map<string, string>::iterator it = FindHeader(key);
		if (it != mapHeaders.end())
		{
			it->second = val;
		}
		else
		{
			mapHeaders.insert({ key, val });
		}
	}

	void HttpHeader::SetHeader(const string& key, const BYTE& val)
	{
		char ch[30] = { 0 };
		sprintf_s(ch, "%d", val);

		SetHeader(key, ch);
	}

	void HttpHeader::SetHeader(const string& key, const INT16& val)
	{
		char ch[30] = { 0 };
		sprintf_s(ch, "%d", val);

		SetHeader(key, ch);
	}

	void HttpHeader::SetHeader(const string& key, const INT32& val)
	{
		char ch[30] = { 0 };
		sprintf_s(ch, "%d", val);

		SetHeader(key, ch);
	}

	void HttpHeader::SetHeader(const string& key, const UINT32& val)
	{
		char ch[30] = { 0 };
		sprintf_s(ch, "%d", val);

		SetHeader(key, ch);
	}

	void HttpHeader::SetHeader(const string& key, const INT64& val)
	{
		char ch[30] = { 0 };
		sprintf_s(ch, "%d", val);

		SetHeader(key, ch);
	}

	void HttpHeader::SetHeader(const string& key, const UINT64& val)
	{
		char ch[30] = { 0 };
		sprintf_s(ch, "%d", val);

		SetHeader(key, ch);
	}

	void HttpHeader::SetHeader(const string& key, const bool& val, const string& trueVal, const string& falseVal)
	{
		SetHeader(key, val == true ? trueVal : falseVal);
	}

	string HttpHeader::GetHeader(const string& key)
	{
		map<string, string>::iterator it = FindHeader(key);
		if (it != mapHeaders.end())
		{
			return it->second;
		}

		return "";
	}

	string HttpHeader::GetContentType()
	{
		string result = "";

		string str = GetHeader(HttpHeaderDef::ContentType);
		if (!str.empty())
		{
			vector<string> vec = StringTool::Split(str, ";");
			if (vec.size() > 1 && !vec[0].empty())
			{
				result = StringTool::Trim(vec[0]);
			}
			else
			{
				result = str;
			}
		}

		return result;
	}

	string HttpHeader::GetCharset()
	{
		string result = "";

		string str = GetHeader(HttpHeaderDef::ContentType);
		if (!str.empty())
		{
			vector<string> vec1 = StringTool::Split(str, ";");
			if (vec1.size() > 1 && !vec1[1].empty())
			{
				vector<string> vec2 = StringTool::Split(vec1[1], "=");
				if (vec2.size() == 2 && !vec2[1].empty())
				{
					result = StringTool::Trim(vec2[1]);
				}
			}
		}

		return result;
	}

	void HttpHeader::RemoveHeader(const string& key)
	{
		map<string, string>::iterator it = FindHeader(key);
		if (it != mapHeaders.end())
		{
			mapHeaders.erase(it);
		}
	}

	map<string, string> HttpHeader::GetHeaders()
	{
		return mapHeaders;
	}

	void HttpHeader::Clear()
	{
		mapHeaders.clear();
	}

	int HttpHeader::GenerateBuf(BYTE* pBuf, int len)
	{
		int nTotal = 0;

		string method = StringTool::ToUpper(GetMethod());

		string str;

		for (map<string, string>::iterator it = mapHeaders.begin(); it != mapHeaders.end(); it++)
		{
			str += it->first + ": " + it->second + "\r\n";
		}

		str += "\r\n";

		nTotal = BufferTool::Copy(pBuf, len, (BYTE*)str.c_str(), str.length());

		return nTotal;
	}

	int HttpHeader::ParseFromBuf(BYTE* pBuf, int len, HttpHeader& header, bool& bSuccess)
	{
		int result = 0;
		bool b = false;

		string str1 = (char*)pBuf;
		int n1 = str1.find("\r\n\r\n");
		if (n1 > 0 && n1 <= Http_MaxHeaderLen)
		{
			string str2 = str1.substr(0, n1 + 2);
			vector<string> vec1 = StringTool::Split(str2, "\r\n");
			int n2 = vec1.size();
			if (n2 > 0)
			{
				int count = 0;

				for (auto & it : vec1)
				{
					if (!it.empty())
					{
						int n3 = it.find(":");
						if (n3 > 0)
						{
							count++;
							string key = it.substr(0, n3);
							string val = "";
							if (n3 + 1 <= (int)it.size())
							{
								val = it.substr(n3 + 1);
							}

							header.SetHeader(key, StringTool::TrimLeft(val));
						}
					}
				}

				if (count = n2 && count > 0)
				{
					result = n1 + 4;
					b = true;
				}
			}
		}

		bSuccess = b;

		return result;
	}
}