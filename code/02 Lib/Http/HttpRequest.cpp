#include "stdafx.h"
#include "Include/http/HttpRequest.h"

#include <assert.h>

#include "com/StringTool.h"
#include "com/BufferTool.h"
using namespace com;


namespace http
{
	HttpRequest::HttpRequest(
		const string& strUrl /*= ""*/,
		const string& method /*= "GET"*/,
		const string& contentType /*= ""*/) :

		url(strUrl),
		line(RequestLine(method)),
		header(HttpHeader()),
		body(HttpBody())
	{
		if (!strUrl.empty())
		{
			strMethod = method;
			strHost = url.GetHost();

			line.Reset(strMethod, url.GetAbsolutePath(), url.GetHttpProtocol());

			if (!contentType.empty())
			{
				header.SetHeader(HttpHeaderDef::ContentType, contentType);
			}
			header.SetHeader(HttpHeaderDef::UserAgent, Http_UserAgent);
		}

		Init();
	}

	void HttpRequest::Init()
	{
		url.AttachHttpObj(this);
		line.AttachHttpObj(this);
		header.AttachHttpObj(this);
		body.AttachHttpObj(this);
	}

	int HttpRequest::GenerateBuf(BYTE* pBuf, int len)
	{
		int nTotal = 0;

		string method = StringTool::ToUpper(strMethod);


		line.strMethod = method;
		header.SetHeader(HttpHeaderDef::Host, strHost);


		BYTE buf1[Http_MaxFstLineLen] = { 0 };
		int n1 = line.GenerateBuf(buf1, Http_MaxFstLineLen);
		nTotal += n1;


		BYTE buf2[Http_MaxBodyLen] = { 0 };
		int n2 = 0;
		if (method == "POST")
		{
			n2 = body.GenerateBuf(buf2, Http_MaxBodyLen);
		}
		nTotal += n2;


		BYTE buf3[Http_MaxHeaderLen] = { 0 };
		if (method == "POST")
		{
			header.SetHeader(HttpHeaderDef::ContentLength, n2);
		}
		else if (method == "GET")
		{
			header.RemoveHeader(HttpHeaderDef::ContentLength);
		}
		int n3 = header.GenerateBuf(buf3, Http_MaxHeaderLen);
		nTotal += n3;


		if (n1 > 0)
		{
			BufferTool::Copy(pBuf, len, buf1, n1);
		}
		if (n3 > 0)
		{
			BufferTool::Copy(pBuf + n1, len - n1, buf3, n3);
		}
		if (n2 > 0)
		{
			BufferTool::Copy(pBuf + n1 + n3, len - n1 - n3, buf2, n2);
		}

		return nTotal;
	}

	bool HttpRequest::ParseFromBuf(BYTE* pBuf, int len, HttpRequest& req, int& nUsed)
	{
		nUsed = 0;
		bool result = false;

		int len1 = RequestLine::ParseFromBuf(pBuf, len, req.line, result);
		if (result && len1 > 0 && len1 < len)
		{
			nUsed += len1;

			int len2 = HttpHeader::ParseFromBuf(pBuf + len1, len - len1, req.header, result);
			if (result && len2 > 0 && len2 <= len - len1)
			{
				nUsed += len2;

				string strProtocolName = req.line.GetProtocolName();
				string strHost1 = req.header.GetHeader(HttpHeaderDef::Host);
				string strPath = req.line.strAbsolutePath;
				string strUrl = strProtocolName + "://" + strHost1 + strPath;

				req.url = Url(strUrl);
				req.strMethod = req.line.strMethod;
				req.strHost = strHost1;

				string method = StringTool::ToUpper(req.line.strMethod);
				if (method == "POST" && len - len1 - len2 > 0)
				{
					int len3 = HttpBody::ParseFromBuf(pBuf + len1 + len2, len - len1 - len2, req.body, result);

					if (result && len3 > 0)
					{
						nUsed += len3;
					}
				}
			}
		}

		return result;
	}
}