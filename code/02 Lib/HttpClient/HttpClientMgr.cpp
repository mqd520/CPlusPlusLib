#include "stdafx.h"
#include "Include/hc/HttpClientMgr.h"

namespace hc
{
	HttpClientMgr::HttpClientMgr()
	{

	}

	HttpClientMgr::~HttpClientMgr()
	{

	}

	void HttpClientMgr::Add(HttpClient* phc)
	{
		bool b = false;
		for (vector<HttpClient*>::iterator it = vecHttpClients.begin(); it != vecHttpClients.end(); it++)
		{
			if (*it == phc)
			{
				b = true;
				break;
			}
		}

		if (!b)
		{
			vecHttpClients.push_back(phc);
		}
	}

	void HttpClientMgr::Remove(HttpClient* phc)
	{
		for (vector<HttpClient*>::iterator it = vecHttpClients.begin(); it != vecHttpClients.end(); it++)
		{
			if (*it == phc)
			{
				vecHttpClients.erase(it);
				break;
			}
		}
	}

	void HttpClientMgr::Remove()
	{
		vecHttpClients.clear();
	}

	HttpClient* HttpClientMgr::GetByUrl(string url)
	{
		HttpClient* phc = NULL;

		for (vector<HttpClient*>::iterator it = vecHttpClients.begin(); it != vecHttpClients.end(); it++)
		{
			if ((*it)->GetUrl() == url)
			{
				phc = *it;
				break;
			}
		}

		return phc;
	}

	HttpClient* HttpClientMgr::Get(string guid)
	{
		HttpClient* phc = NULL;

		for (vector<HttpClient*>::iterator it = vecHttpClients.begin(); it != vecHttpClients.end(); it++)
		{
			if ((*it)->GetGUID() == guid)
			{
				phc = *it;
				break;
			}
		}

		return phc;
	}
}