#pragma once


namespace MyAdo
{
	// MyAdo
	class MyAdoApp
	{
	public:
		static bool bEnableAutoCloseConnection;		// Enable Auto Close Connection, only for async mode, default: true
		static bool bEnableAutoSqlLog;				// Enable Auto Record Sql Log, default: true

	public:
		//************************************
		// Method:    Init
		// Parameter: int nThreadCount
		//************************************
		static void Init(int nThreadCount = 1);

		//************************************
		// Method:    Exit
		//************************************
		static void Exit(int timeout = 1 * 1000);
	};
}