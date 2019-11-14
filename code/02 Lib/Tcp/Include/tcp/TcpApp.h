#pragma once

#include "SocketTool.h"
#include <MSWSock.h>

#include "com/Log.h"
using namespace com;

#include "../../TcpServiceMgr.h"


namespace tcp
{
	// Tcp App
	class TcpApp final
	{
	private:
		TcpApp();

	public:
		static LPFN_ACCEPTEX	AcceptEx;
		static LPFN_CONNECTEX	ConnectEx;
		static LPFN_GETACCEPTEXSOCKADDRS GetAddrEx;

	private:
		static TcpServiceMgr* pTcpSrvMgr;

	private:
		//************************************
		// Method:    Load Ex Funs
		//************************************
		static void LoadExFuns();

	public:
		//************************************
		// Method:    Init
		//************************************
		static void Init(int count = 0);

		//************************************
		// Method:    Exit
		//************************************
		static void Exit();

		//************************************
		// Method:    Reg Tcp Log Callback
		// Parameter: CommonLogCallback callback
		//************************************
		static void RegTcpLogCallback(CommonLogCallback callback);

		//************************************
		// Method:    Get Tcp Service Mgr
		//************************************
		static TcpServiceMgr* GetTcpSrvMgr();
	};
}