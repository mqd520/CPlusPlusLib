#pragma once

#include <vector>
using namespace std;


namespace tcp
{
	class TcpService;


	// Tcp Service Mgr
	class TcpServiceMgr
	{
	public:
		TcpServiceMgr();

	private:
		vector<TcpService*> vecTcpServices;	// Tcp Service list

	public:
		//************************************
		// Method:    IsExit
		// Parameter: TcpService * pSrv
		//************************************
		bool IsExit(TcpService* pSrv);

		//************************************
		// Method:    Add
		// Parameter: TcpService * pSrv
		//************************************
		void Add(TcpService* pSrv);

		//************************************
		// Method:    Remove
		// Parameter: TcpService * pSrv
		//************************************
		void Remove(TcpService* pSrv);

		//************************************
		// Method:    Clear
		//************************************
		void Clear();
	};
}