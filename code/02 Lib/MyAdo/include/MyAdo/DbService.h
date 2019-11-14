#pragma once

#include <queue>
using namespace std;

#include "com/Lock.h"
using namespace com;

#include "Ado.h"
#include "DbRequest.h"


namespace MyAdo
{
	// Ado Service
	class DbService
	{
	protected:
		queue<DbRequest> quDbReqs;	// DbRequest queue
		Lock lock;					// lock

	public:
		//************************************
		// Method:    Push Db Request
		// Parameter: DbRequest & req
		//************************************
		void PushDbRequest(DbRequest& req);

		//************************************
		// Method:    Process Db Request
		//************************************
		void ProcessDbRequest();

		//************************************
		// Method:    Exit
		//************************************
		void Exit();
	};

	extern DbService _dbSrv;		// DbService obj
}