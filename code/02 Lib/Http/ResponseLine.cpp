#include "stdafx.h"
#include "Include/http/ResponseLine.h"

#include "com/BufferTool.h"
#include "com/StringTool.h"
using namespace com;


namespace http
{
	ResponseLine::ResponseLine(int code /*= 200*/, const string& text /*= "OK"*/, const string& protocol /*= "HTTP/1.1"*/) :
		nCode(code),
		strText(text),
		strProtocol(protocol)
	{

	}

	int ResponseLine::GenerateBuf(BYTE* pBuf, int len)
	{
		int result = 0;

		char ch[1024] = { 0 };
		sprintf_s(ch, "%s %d %s\r\n", strProtocol.c_str(), nCode, strText.c_str());

		result = BufferTool::Copy(pBuf, len, (BYTE*)ch, strlen(ch));

		return result;
	}

	int ResponseLine::ParseFromBuf(BYTE* pBuf, int len, ResponseLine& line, bool& bSuccess)
	{
		int result = 0;
		bool b = false;

		string protocol = "";
		int code = 0;
		string text = "";

		string str1 = (char*)pBuf;
		int n1 = str1.find("\r\n");
		if (n1 > 0)
		{
			string str2 = str1.substr(0, n1);
			vector<string> vec1 = StringTool::Split(str2, " ");
			if (vec1.size() == 3)
			{
				protocol = vec1[0];
				code = atoi(vec1[1].c_str());
				text = vec1[2];
			}
		}

		if ((protocol == "HTTP/1.1" || protocol == "HTTPS/1.1") && code > 0)
		{
			b = true;

			line.strProtocol = protocol;
			line.nCode = code;
			line.strText = text;

			result = n1 + 2;
		}

		bSuccess = b;

		return result;
	}
}