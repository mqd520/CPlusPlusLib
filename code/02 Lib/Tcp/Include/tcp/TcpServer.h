#pragma once

#include "TcpService.h"
#include "SocketTool.h"


namespace tcp
{
	// Tcp Server
	class TcpServer : public TcpService
	{
	public:
		TcpServer(string ip = "", int port = 0);

	protected:
		bool bRunning;
		SOCKET socket;

	public:
		//************************************
		// Method:    Reset Addr
		// Parameter: string ip
		// Parameter: int port
		//************************************
		bool ResetAddr(string ip, int port) override;

		//************************************
		// Method:    Run
		//************************************
		bool Run();

		//************************************
		// Method:    Stop
		//************************************
		void Stop();

		//************************************
		// Method:    Exit
		//************************************
		void Exit() override;
	};
}