#pragma once


namespace MyAdo
{
	// MyAdo
	class MyAdoApp
	{
	public:
		static bool bEnableAutoCloseConnection;		// Enable Auto Close Connection, only for async mode, default: false
		static bool bEnableAutoSqlLog;				// Enable Auto Record Sql Log, default: false

	public:
		//************************************
		// Method:    Init
		// Parameter: int nThreadCount
		// Parameter: int nSleepTime
		//************************************
		static void Init(int nThreadCount = 1, int nSleepTime = 50);

		//************************************
		// Method:    Exit
		//************************************
		static void Exit(int timeout = 1 * 1000);

		//************************************
		// Method:    Is All Thread Started
		//************************************
		static bool IsAllThreadStarted();
	};
}