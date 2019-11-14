#include "stdafx.h"
#include "DbService.h"

#include "MyAdoApp.h"


namespace MyAdo
{
	DbService _dbSrv;

	void DbService::PushDbRequest(DbRequest& req)
	{
		//lock.Enter();

		quDbReqs.push(req);

		//lock.Leave();
	}

	void DbService::ProcessDbRequest()
	{
		DbRequest req;

		lock.Enter();

		if (!quDbReqs.empty())
		{
			req = quDbReqs.front();
			quDbReqs.pop();
		}

		lock.Leave();


		if (!req.sql.empty())
		{
			AdoResult result;

			if (req.type == EDbRequstType::NonQuery)
			{
				result = req.pAdo->ExecuteNonQuery(req.sql, req.param, req.cmdType);
			}
			else if (req.type == EDbRequstType::Query)
			{
				result = req.pAdo->ReadDataSet(req.sql, req.param, req.cmdType);
			}

			if (MyAdoApp::bEnableAutoCloseConnection)
			{
				req.pAdo->CloseConnection();
			}

			if (!req.callback._Empty())
			{
				req.callback(result, req.lpParam1, req.lpParam2);
			}
		}
	}

	void DbService::Exit()
	{
		lock.Disable(true);
	}
}