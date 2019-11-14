#include "stdafx.h"
#include "Include/tcp/TcpClient.h"


namespace tcp
{
	TcpClient::TcpClient(const string& ip, const int& port) :
		TcpService(ip, port, ETcpSrvType::Client)
	{

	}
}