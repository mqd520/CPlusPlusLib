#pragma once

#include "TcpService.h"


namespace tcp
{
	// Tcp Client
	class TcpClient : public TcpService
	{
	public:
		TcpClient(const string& ip, const int& port);
	};
}