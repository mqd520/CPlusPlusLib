#include "stdafx.h"
#include "Include/http/HttpSubObject.h"

#include "Include/http/HttpRequest.h"
#include "Include/http/HttpResponse.h"


namespace http
{
	void HttpSubObject::AttachHttpObj(void* pObj, EHttpType type /*= EHttpType::Request*/)
	{
		this->pObj = pObj;
		this->httpType = type;
	}

	EHttpType HttpSubObject::GetHttpType()
	{
		return httpType;
	}

	HttpRequest* HttpSubObject::GetHttpRequest()
	{
		return (HttpRequest*)pObj;
	}

	HttpResponse* HttpSubObject::GetHttpResponse()
	{
		return (HttpResponse*)pObj;
	}

	string HttpSubObject::GetMethod()
	{
		if (httpType == EHttpType::Request)
		{
			return ((HttpRequest*)pObj)->strMethod;
		}
		else
		{
			return "";
		}
	}

	string HttpSubObject::GetContentType()
	{
		if (httpType == EHttpType::Request)
		{
			return ((HttpRequest*)pObj)->header.GetContentType();
		}
		else
		{
			return ((HttpResponse*)pObj)->header.GetContentType();
		}
	}

	int HttpSubObject::GetContentLength()
	{
		int nContentLength = 0;
		string str = "";

		if (httpType == EHttpType::Request)
		{
			str = ((HttpRequest*)pObj)->header.GetHeader(HttpHeaderDef::ContentLength);
		}
		else
		{
			str = ((HttpResponse*)pObj)->header.GetHeader(HttpHeaderDef::ContentLength);
		}

		if (!str.empty())
		{
			nContentLength = atoi(str.c_str());
		}

		return nContentLength;
	}

	string HttpSubObject::GetCharset()
	{
		if (httpType == EHttpType::Request)
		{
			return ((HttpRequest*)pObj)->header.GetCharset();
		}
		else
		{
			return ((HttpResponse*)pObj)->header.GetCharset();
		}
	}
}