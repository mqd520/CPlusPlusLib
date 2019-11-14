#include "stdafx.h"
#include "Include/http/HttpResponse.h"

#include "com/StringTool.h"
#include "com/BufferTool.h"
#include "com/TimeTool.h"
using namespace com;


namespace http
{
	HttpResponse::HttpResponse(int code /*= 0*/, const string& text /*= "OK"*/, const string& protocol /*= "HTTP/1.1"*/) :
		line(ResponseLine(code, text, protocol)),
		header(HttpHeader()),
		body(HttpBody())
	{
		if (code > 0)
		{
			header.SetHeader(HttpHeaderDef::ContentType, "text/html");
		}

		Init();
	}

	void HttpResponse::Init()
	{
		line.AttachHttpObj(this, EHttpType::Response);
		header.AttachHttpObj(this, EHttpType::Response);
		body.AttachHttpObj(this, EHttpType::Response);
	}

	int HttpResponse::GenerateBuf(BYTE* pBuf, int len)
	{
		int result = 0;

		header.SetHeader(HttpHeaderDef::Date, TimeTool::GetCurrentTimeStr("GMT", false));


		BYTE buf1[Http_MaxFstLineLen] = { 0 };
		int n1 = line.GenerateBuf(buf1, Http_MaxFstLineLen);


		BYTE buf2[Http_MaxBodyLen] = { 0 };
		int n2 = body.GenerateBuf(buf2, Http_MaxBodyLen);


		BYTE buf3[Http_MaxHeaderLen] = { 0 };
		header.SetHeader(HttpHeaderDef::ContentLength, n2);
		int n3 = header.GenerateBuf(buf3, Http_MaxHeaderLen);


		if (n1 > 0)
		{
			BufferTool::Copy(pBuf, len, buf1, n1);
			result += n1;
		}
		if (n3 > 0)
		{
			BufferTool::Copy(pBuf + n1, len - n1, buf3, n3);
			result += n3;
		}
		if (n2 > 0)
		{
			BufferTool::Copy(pBuf + n1 + n3, len - n1 - n3, buf2, n2);
			result += n2;
		}


		return result;
	}

	bool HttpResponse::ParseFromBuf(BYTE* pBuf, int len, HttpResponse& res, int& usedLen)
	{
		bool result = false;
		usedLen = 0;

		int len1 = ResponseLine::ParseFromBuf(pBuf, len, res.line, result);
		if (result && len1 > 0 && len1 < len)
		{
			usedLen += len1;

			int len2 = HttpHeader::ParseFromBuf(pBuf + len1, len - len1, res.header, result);
			if (result && len2 > 0 && len2 <= len - len1)
			{
				usedLen += len2;

				string strLength = res.header.GetHeader(HttpHeaderDef::ContentLength);
				int nContentLength = atoi(strLength.c_str());

				if (nContentLength > 0 && len - len1 - len2 > 0)
				{
					int len3 = HttpBody::ParseFromBuf(pBuf + len1 + len2, len - len1 - len2, res.body, result);

					if (result && len3 > 0)
					{
						usedLen += len3;
					}
				}
			}
		}

		return result;
	}
}