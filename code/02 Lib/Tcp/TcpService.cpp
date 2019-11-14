#include "stdafx.h"
#include "Include/tcp/TcpService.h"

#include "Include/tcp/TcpApp.h"


namespace tcp
{
	TcpService::TcpService(const string& ip, const int& port, ETcpSrvType type) :
		strIp(ip),
		nPort(port),
		type(type)
	{
		TcpApp::GetTcpSrvMgr()->Add(this);
	}

	TcpService::~TcpService()
	{
		
	}

	string TcpService::GetIp() const
	{
		return strIp;
	}

	int TcpService::GetPort() const
	{
		return nPort;
	}

	void TcpService::Exit()
	{
		TcpApp::GetTcpSrvMgr()->Remove(this);
	}

	bool TcpService::ResetAddr(string ip, int port)
	{
		strIp = ip;
		nPort = port;

		return true;
	}
}