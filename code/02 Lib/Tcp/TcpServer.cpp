#include "stdafx.h"
#include "Include/tcp/TcpServer.h"


namespace tcp
{
	TcpServer::TcpServer(string ip /*= ""*/, int port /*= 0*/) :
		TcpService(ip, port, ETcpSrvType::Server),

		bRunning(false),
		socket(INVALID_SOCKET)
	{

	}

	bool TcpServer::ResetAddr(string ip, int port)
	{
		if (!bRunning)
		{
			return __super::ResetAddr(ip, port);
		}

		return false;
	}

	bool TcpServer::Run()
	{
		if (bRunning)
		{
			return false;
		}

		socket = SocketTool::CreateLPTcpSocket();
		if (socket != INVALID_SOCKET)
		{
			bool b = SocketTool::Bind(socket, strIp, nPort);
			if (b)
			{
				bool b1 = SocketTool::Listen(socket, strIp, nPort);
				return b1;
			}
		}

		return true;
	}

	void TcpServer::Stop()
	{
		bRunning = false;

		if (socket != INVALID_SOCKET)
		{
			SocketTool::ShutDown(socket);
			SocketTool::CloseSocket(socket);
			socket = INVALID_SOCKET;
		}
	}

	void TcpServer::Exit()
	{
		__super::Exit();

		Stop();
	}
}