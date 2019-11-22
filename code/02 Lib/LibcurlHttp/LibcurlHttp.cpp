#include "stdafx.h"
#include "LibcurlHttp.h"

#include "com/Log.h"
#include "com/StringTool.h"
#include "com/NumberTool.h"
using namespace com;

#include "LibcurlHttpApp.h"


size_t OnWriteData(void* buffer, size_t size, size_t nmemb, void* lpVoid);
size_t OnWriteHeader(void* buffer, size_t size, size_t nmemb, void* lpVoid);

namespace libcurlHttp
{
	struct curl_slist * LibcurlHttp::SetHeadersOpt(CURL* pCurl)
	{
		struct curl_slist *pHeaders = NULL;

		for (auto & it : mapHeaders)
		{
			string str = it.first + ":" + it.second;
			//pHeaders = curl_slist_append(pHeaders, str.c_str());
		}

		if (pHeaders)
		{
			//curl_easy_setopt(pCurl, CURLOPT_HTTPHEADER, pHeaders);
		}

		return pHeaders;
	}

	void LibcurlHttp::SetBodyOpt(CURL* pCurl, const string& method)
	{
		if (method == "POST")
		{
			struct curl_slist *pBody = NULL;

			if (IsFormData())
			{
				int n = 0;
				string formData;
				for (auto & it : mapFormItems)
				{
					if (n == 0)
					{
						formData += it.first + "=" + it.second;
					}
					else
					{
						formData += "&" + it.first + "=" + it.second;
					}

					n++;
				}

				curl_easy_setopt(pCurl, CURLOPT_POSTFIELDS, formData.c_str());
				curl_easy_setopt(pCurl, CURLOPT_POSTFIELDSIZE, formData.size());
			}
			else
			{
				curl_easy_setopt(pCurl, CURLOPT_POSTFIELDS, strBodyData.c_str());
			}
		}
	}

	bool LibcurlHttp::IsFormData()
	{
		if (GetHeader("Content-Type") == "application/x-www-form-urlencoded" ||
			GetHeader("Content-type") == "application/x-www-form-urlencoded")
		{
			return true;
		}

		return false;
	}

	CURL* LibcurlHttp::Init()
	{
		CURL *pCurl = curl_easy_init();
		if (nullptr == pCurl)
		{
			Log::Write_2_Console(ELogType::Error, "curl init fail", true, __FUNCTION__, __FILE__, __LINE__);

			return nullptr;
		}

		return pCurl;
	}

	void LibcurlHttp::Execute(const string& strUrl, string method, LibcurlHttpResult* pResult,
		bool bRecvResponse /*= false*/, bool bRecvHeader /*= false*/)
	{
		pResult->bSuccess = false;
		pResult->code = CURLE_FAILED_INIT;

		CURL* pCurl = Init();
		if (pCurl)
		{
			curl_easy_setopt(pCurl, CURLOPT_URL, strUrl.c_str());

			if (method == "POST" && IsFormData())
			{
				curl_easy_setopt(pCurl, CURLOPT_POST, true);
			}

			struct curl_slist* pHeaders = SetHeadersOpt(pCurl);
			//SetBodyOpt(pCurl, method);

			curl_easy_setopt(pCurl, CURLOPT_READFUNCTION, NULL);

			if (StringTool::StartWith(strUrl, "https", false))
			{
				curl_easy_setopt(pCurl, CURLOPT_SSL_VERIFYPEER, false);
				curl_easy_setopt(pCurl, CURLOPT_SSL_VERIFYHOST, false);
			}

			if (bRecvResponse)
			{
				curl_easy_setopt(pCurl, CURLOPT_WRITEFUNCTION, OnWriteData);
				curl_easy_setopt(pCurl, CURLOPT_WRITEDATA, (void*)&pResult->response);
			}

			TimeoutInfo timeoutInfo = LibcurlHttpApp::GetTimeoutInfo();
			if (timeoutInfo.nConnectTimeout > -1)
			{
				curl_easy_setopt(pCurl, CURLOPT_CONNECTTIMEOUT, timeoutInfo.nConnectTimeout);
			}
			if (timeoutInfo.nHttpTimeout > -1)
			{
				curl_easy_setopt(pCurl, CURLOPT_TIMEOUT, timeoutInfo.nHttpTimeout);
			}

			HttpProxyInfo proxyInfo = LibcurlHttpApp::GetHttpProxy();
			if (proxyInfo.bIsSet)
			{
				curl_easy_setopt(pCurl, CURLOPT_PROXY, proxyInfo.addr.c_str());
				curl_easy_setopt(pCurl, CURLOPT_PROXYTYPE, CURLPROXY_HTTP);
				if (StringTool::StartWith(strUrl, "https", false))
				{
					curl_easy_setopt(pCurl, CURLOPT_HTTPPROXYTUNNEL, 1L);
				}

				if (!proxyInfo.username.empty())
				{
					string str = proxyInfo.username + ":" + proxyInfo.pwd;
					curl_easy_setopt(pCurl, CURLOPT_PROXYUSERPWD, str.c_str());
				}
			}

			string strHeaders;
			curl_easy_setopt(pCurl, CURLOPT_HEADERFUNCTION, OnWriteHeader);
			curl_easy_setopt(pCurl, CURLOPT_HEADERDATA, (void*)&strHeaders);

			curl_easy_setopt(pCurl, CURLOPT_FOLLOWLOCATION, 1);
			curl_easy_setopt(pCurl, CURLOPT_NOSIGNAL, 1);

			SetBodyOpt(pCurl, method);

			if (LibcurlHttpApp::IsEnableHttpReqLog())
			{
				string data;
				if (IsFormData())
				{
					for (auto & it : mapFormItems)
					{
						data += "&" + it.first + "=" + it.second;
					}
				}
				else
				{
					data += strBodyData;
				}

				string log = StringTool::Format("[%s] %s", strUrl.c_str(), data.c_str());
				Log::Write_2_File(ELogType::Http, log, __FUNCTION__, __FILE__, __LINE__);
			}

			CURLcode code = curl_easy_perform(pCurl);
			pResult->code = code;
			pResult->bSuccess = code == CURLE_OK;

			vector<pair<string, string>> vecHeaders;
			vector<string> vec = StringTool::Split(strHeaders, "\r\n");
			int n = 0;
			for (auto & it : vec)
			{
				if (!it.empty())
				{
					if (n == 0)
					{
						vector<string> vec1 = StringTool::Split(it, " ");
						pResult->nHttpStatus = StringTool::To_Int32(vec1[1]);
					}
					else
					{
						vector<string> vec1 = StringTool::Split(it, ":");
						if (vec1.size() == 2)
						{
							vecHeaders.push_back({ vec1[0], StringTool::Trim(vec1[1]) });
						}
					}
				}

				n++;
			}

			if (bRecvHeader)
			{
				pResult->vecHeaders = vecHeaders;
			}

			if (code != CURLE_OK)
			{
				string str = StringTool::Format("Http error, curl code: %d, %s", code, curl_easy_strerror(code));
				Log::Write_2_Console(ELogType::Error, str, true, __FUNCTION__, __FILE__, __LINE__);
			}

			curl_easy_cleanup(pCurl);
			curl_slist_free_all(pHeaders);
		}
	}

	bool LibcurlHttp::IsExitHeader(const string& header)
	{
		map<string, string>::iterator it = mapHeaders.find(header);
		if (it != mapHeaders.end())
		{
			return true;
		}

		return false;
	}

	string LibcurlHttp::GetHeader(const string& header)
	{
		map<string, string>::iterator it = mapHeaders.find(header);
		if (it != mapHeaders.end())
		{
			return it->second;
		}

		return "";
	}

	void LibcurlHttp::SetHeader(const string& header, const string& val)
	{
		map<string, string>::iterator it = mapHeaders.find(header);
		if (it != mapHeaders.end())
		{
			it->second = val;
		}
		else
		{
			mapHeaders.insert({ header, val });
		}
	}

	void LibcurlHttp::SetFormItem(const string& item, const string& val)
	{
		map<string, string>::iterator it = mapFormItems.find(item);
		if (it != mapFormItems.end())
		{
			it->second = val;
		}
		else
		{
			mapFormItems.insert({ item, val });
		}
	}

	void LibcurlHttp::SetFormItem(const string& item, const wstring& val)
	{
		SetFormItem(item, (char*)val.c_str());
	}

	void LibcurlHttp::SetFormItem(const string& item, const BYTE& val)
	{
		SetFormItem(item, StringTool::Format("%u", val));
	}

	void LibcurlHttp::SetFormItem(const string& item, const INT16& val)
	{
		SetFormItem(item, StringTool::Format("%d", val));
	}

	void LibcurlHttp::SetFormItem(const string& item, const UINT16& val)
	{
		SetFormItem(item, StringTool::Format("%u", val));
	}

	void LibcurlHttp::SetFormItem(const string& item, const INT32& val)
	{
		SetFormItem(item, StringTool::Format("%d", val));
	}

	void LibcurlHttp::SetFormItem(const string& item, const UINT32& val)
	{
		SetFormItem(item, StringTool::Format("%u", val));
	}

	void LibcurlHttp::SetFormItem(const string& item, const INT64& val)
	{
		SetFormItem(item, StringTool::Format("%lld", val));
	}

	void LibcurlHttp::SetFormItem(const string& item, const UINT64& val)
	{
		SetFormItem(item, StringTool::Format("%llu", val));
	}

	void LibcurlHttp::SetFormItem(const string& item, const float& val, const int& decimal /*= 2*/)
	{
		SetFormItem(item, NumberTool::ToString(val, decimal));
	}

	void LibcurlHttp::SetFormItem(const string& item, const double& val, const int& decimal /*= 2*/)
	{
		SetFormItem(item, NumberTool::ToString(val, decimal));
	}

	void LibcurlHttp::SetBodyData(const string& data)
	{
		strBodyData = data;
	}

	LibcurlHttpResult LibcurlHttp::Post(const string& strUrl, bool bRecvResponse /*= false*/, bool bRecvHeader /*= false*/,
		const string& contentType /*= "application/x-www-form-urlencoded"*/)
	{
		LibcurlHttpResult result;

		if (!contentType.empty())
		{
			SetHeader("Content-Type", contentType);
		}

		Execute(strUrl, "POST", &result, bRecvResponse, bRecvHeader);

		return result;
	}

	LibcurlHttpResult LibcurlHttp::Get(const string& strUrl, bool bRecvResponse /*= false*/, bool bRecvHeader /*= false*/,
		const string& contentType /*= "application/x-www-form-urlencoded"*/)
	{
		LibcurlHttpResult result;

		if (!contentType.empty())
		{
			SetHeader("Content-Type", contentType);
		}

		Execute(strUrl, "GET", &result, bRecvResponse, bRecvHeader);

		return result;
	}
}


size_t OnWriteData(void* buffer, size_t size, size_t nmemb, void* lpVoid)
{
	std::string* str = dynamic_cast<std::string*>((std::string *)lpVoid);
	if (NULL == str || NULL == buffer)
	{
		return -1;
	}

	char* pData = (char*)buffer;
	str->append(pData, size * nmemb);

	return nmemb;
}

size_t OnWriteHeader(void* buffer, size_t size, size_t nmemb, void* lpVoid)
{
	std::string* str = dynamic_cast<std::string*>((std::string *)lpVoid);
	if (NULL == str || NULL == buffer)
	{
		return -1;
	}

	char* pData = (char*)buffer;
	str->append(pData, size * nmemb);

	return nmemb;
}