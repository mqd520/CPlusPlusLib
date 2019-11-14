#pragma once

#include <string>
using namespace std;

#include "Def.h"


namespace tcp
{
	// Tcp Service
	class TcpService
	{
	public:
		TcpService(const string& ip, const int& port, ETcpSrvType type);

		virtual ~TcpService();

	protected:
		string strIp;		// Ip
		int nPort;			// Port
		ETcpSrvType type;	// Tcp Service Type

	public:
		//************************************
		// Method:    Get Ip
		//************************************
		string GetIp() const;

		//************************************
		// Method:    Get Port
		//************************************
		int GetPort() const;

		//************************************
		// Method:    GetType
		//************************************
		ETcpSrvType GetType() const;

		//************************************
		// Method:    Reset Addr
		// Parameter: string ip
		// Parameter: int port
		//************************************
		virtual bool ResetAddr(string ip, int port);

		//************************************
		// Method:    Exit
		//************************************
		virtual void Exit();
	};
}