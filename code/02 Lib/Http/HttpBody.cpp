#include "stdafx.h"
#include "Include/http/HttpBody.h"

#include "Include/http/HttpRequest.h"
#include "Include/http/HttpHeaderDef.h"
#include "Include/http/HttpTool.h"

#include "com/StringTool.h"
#include "com/BufferTool.h"
using namespace com;


namespace http
{
	HttpBody::HttpBody() :
		pBuf(""),
		nLen(0),
		strTextData("")
	{

	}

	bool HttpBody::IsTextData()
	{
		return HttpTool::IsTextType(GetContentType());
	}

	bool HttpBody::SetBinaryData(BYTE* buf, int len)
	{
		pBuf = (char*)buf;
		nLen = len;

		return true;
	}

	bool HttpBody::SetTextData(string strText)
	{
		strTextData = strText;

		return true;
	}

	int HttpBody::GenerateBuf(BYTE* pBuf, int len)
	{
		int nTotal = 0;

		string method = StringTool::ToUpper(GetMethod());
		string contentType = StringTool::ToLower(GetContentType());

		if (GetHttpType() == EHttpType::Request)
		{
			if (method != "POST")
			{
				return nTotal;
			}
		}


		if (HttpTool::IsTextType(contentType))
		{
			string str = "";

			if (contentType == "application/x-www-form-urlencoded")
			{
				str = form.Join();
			}
			else
			{
				str = strTextData;
			}

			if (!str.empty())
			{
				string charset = StringTool::ToLower(GetCharset());
				if (charset.empty() || charset == "utf-8")
				{
					string str1 = StringTool::GB2312_2_UTF8((char*)str.c_str());
					nTotal = BufferTool::Copy(pBuf, len, (BYTE*)str1.c_str(), str1.length());
				}
				else
				{
					nTotal = BufferTool::Copy(pBuf, len, (BYTE*)str.c_str(), str.length());
				}
			}
		}
		else
		{
			if (!this->pBuf.empty() && this->nLen > 0)
			{
				nTotal = BufferTool::Copy(pBuf, len, (BYTE*)this->pBuf.c_str(), nLen);
			}
		}

		return nTotal;
	}

	int HttpBody::ParseFromBuf(BYTE* pBuf, int len, HttpBody& body, bool& bSuccess)
	{
		int result = 0;
		bool b = false;

		string str1 = (char*)pBuf;

		string contentType = body.GetContentType();
		int nContentLength = body.GetContentLength();

		if (nContentLength > 0)
		{
			if (nContentLength <= len)
			{
				b = true;
				result = nContentLength;

				if (HttpTool::IsTextType(contentType))
				{
					string contentType1 = StringTool::ToLower(contentType);
					string charset = StringTool::ToLower(body.GetCharset());
					string str2 = str1.substr(0, nContentLength);

					if (charset.empty() || charset == "utf-8")
					{
						str2 = StringTool::UTF8_2_GB2312((char*)str2.c_str());
					}

					if (contentType1 == "application/x-www-form-urlencoded")
					{
						body.form.ParseFormText(str2);
					}
					else
					{
						body.SetTextData(str2);
					}
				}
				else
				{
					body.SetBinaryData(pBuf, result);
				}
			}
		}
		else
		{
			b = true;
		}

		bSuccess = b;

		return result;
	}
}