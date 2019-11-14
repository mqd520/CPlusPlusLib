#include "stdafx.h"
#include "Include/tcp/TcpApp.h"

#include "WorkerThread.h"


namespace tcp
{
	HANDLE hIO = NULL;
	vector<WorkerThread*> vecThds;
	int nCount = 0;


	LPFN_ACCEPTEX	TcpApp::AcceptEx = nullptr;
	LPFN_CONNECTEX	TcpApp::ConnectEx = nullptr;
	LPFN_GETACCEPTEXSOCKADDRS TcpApp::GetAddrEx = nullptr;
	TcpServiceMgr*	TcpApp::pTcpSrvMgr = nullptr;


	TcpApp::TcpApp()
	{

	}

	void TcpApp::LoadExFuns()
	{
		SocketTool::Init();
		SOCKET socket = SocketTool::CreateTcpSocket();
		if (socket != INVALID_SOCKET)
		{
			DWORD dwResult = 0;

			GUID guidAccept = WSAID_ACCEPTEX;
			int n1 = WSAIoctl(socket, SIO_GET_EXTENSION_FUNCTION_POINTER,
				&guidAccept, sizeof(guidAccept),
				&AcceptEx, sizeof(AcceptEx),
				&dwResult, NULL, NULL);
			if (n1 != 0)
			{
				Log::Write_2_File(ECommonLogType::Fatal, true, "Load AcceptEx fail, return: %d, code: %d", n1, WSAGetLastError());
			}
			else
			{
				dwResult = 0;
				GUID guidConn = WSAID_CONNECTEX;
				int n2 = WSAIoctl(socket, SIO_GET_EXTENSION_FUNCTION_POINTER,
					&guidConn, sizeof(guidConn),
					&ConnectEx, sizeof(ConnectEx),
					&dwResult, NULL, NULL);
				if (n2 != 0)
				{
					Log::Write_2_File(ECommonLogType::Fatal, true, "Load ConnectEx fail, return: %d, code: %d", n2, WSAGetLastError());
				}
				else
				{
					dwResult = 0;
					GUID guidGetAddr = WSAID_GETACCEPTEXSOCKADDRS;
					int n3 = WSAIoctl(socket, SIO_GET_EXTENSION_FUNCTION_POINTER,
						&guidGetAddr, sizeof(guidGetAddr),
						&GetAddrEx, sizeof(GetAddrEx),
						&dwResult, NULL, NULL);
					if (n3 != 0)
					{
						Log::Write_2_File(ECommonLogType::Fatal, true, "Load GetSocketAddrEx fail, return: %d, code: %d", n3, WSAGetLastError());
					}
				}
			}


			SocketTool::CloseSocket(socket);
		}
	}

	void TcpApp::Init(int count /*= 0*/)
	{
		//hIO = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);

		LoadExFuns();

		if (count <= 0)
		{
			SYSTEM_INFO si;
			GetSystemInfo(&si);

			count = si.dwNumberOfProcessors;
		}
		nCount = count;

		for (int i = 0; i < count; i++)
		{
			WorkerThread* p = new WorkerThread();
			vecThds.push_back(p);

			p->Run();
		}
	}

	void TcpApp::Exit()
	{
		for (auto & it : vecThds)
		{
			if (it)
			{
				it->Exit(2 * 1000);
				delete it;
			}
		}
		vecThds.clear();

		if (pTcpSrvMgr)
		{
			pTcpSrvMgr->Clear();
			delete pTcpSrvMgr;
			pTcpSrvMgr = nullptr;
		}

	}

	void TcpApp::RegTcpLogCallback(CommonLogCallback callback)
	{
		Log::RegLogCallback(callback);
	}

	TcpServiceMgr* TcpApp::GetTcpSrvMgr()
	{
		if (!pTcpSrvMgr)
		{
			pTcpSrvMgr = new TcpServiceMgr();
		}

		return pTcpSrvMgr;
	}
}