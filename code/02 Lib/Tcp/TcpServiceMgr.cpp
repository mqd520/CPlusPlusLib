#include "stdafx.h"
#include "TcpServiceMgr.h"


namespace tcp
{
	TcpServiceMgr::TcpServiceMgr()
	{

	}

	bool TcpServiceMgr::IsExit(TcpService* pSrv)
	{
		bool result = false;

		for (auto & item : vecTcpServices)
		{
			if (item == pSrv)
			{
				result = true;
				break;
			}
		}

		return result;
	}

	void TcpServiceMgr::Add(TcpService* pSrv)
	{
		if (!IsExit(pSrv))
		{
			vecTcpServices.emplace_back(pSrv);
		}
	}

	void TcpServiceMgr::Remove(TcpService* pSrv)
	{
		for (vector<TcpService*>::iterator it = vecTcpServices.begin(); it != vecTcpServices.end(); it++)
		{
			if (*it == pSrv)
			{
				vecTcpServices.erase(it);
				break;
			}
		}
	}

	void TcpServiceMgr::Clear()
	{
		vecTcpServices.clear();
	}
}