#pragma once

#include <WinSock2.h>
#include <string>
#include <vector>
using namespace std;


namespace tcp
{
	// Socket Tool
	class SocketTool final
	{
	private:
		SocketTool();

	private:
		//************************************
		// Method:    Process Error Info
		// Parameter: fn:		function name
		// Parameter: code:		error code
		// Parameter: remark:	remark
		// Parameter: b:		whether process
		//************************************
		static void ProcessErrorInfo(string fn, int code, string remark = "", bool b = true);

	public:
		//************************************
		// Method:    Init
		//************************************
		static bool Init(bool b = true);

		//************************************
		// Method:    Exit
		//************************************
		static void Exit();

		//************************************
		// Method:    Create a Tcp Socket
		//************************************
		static SOCKET CreateTcpSocket(bool b = true);

		//************************************
		// Method:    Create a Tcp Socket(overlapped)
		//************************************
		static SOCKET CreateLPTcpSocket(bool b = true);

		//************************************
		// Method:    Get SOCKADDR_IN
		//************************************
		static SOCKADDR_IN GetSocketAddr(string ip, int port);

		//************************************
		// Method:    bind socket
		//************************************
		static bool Bind(SOCKET socket, string ip, int port, bool b = true);

		//************************************
		// Method:    Listen
		// Parameter: socket: socket
		// Parameter: ip
		// Parameter: port
		// Parameter: backlog
		//************************************
		static bool Listen(SOCKET socket, string ip, int port, int backlog = SOMAXCONN, bool b = true);

		//************************************
		// Method:    Accept
		// Parameter: ip
		// Parameter: port
		//************************************
		static SOCKET Accept(SOCKET socket, string ip, int port, bool b = true);

		//************************************
		// Method:    Recv
		// Parameter: socket: socket
		// Parameter: pBuf
		// Parameter: len
		// Parameter: actuallyLen
		//************************************
		static bool Recv(SOCKET socket, BYTE* pBuf, int len, int* actuallyLen, bool b = true);

		//************************************
		// Method:    Send
		// Parameter: socket: socket
		// Parameter: pBuf
		// Parameter: len
		// Parameter: actuallyLen
		//************************************
		static bool Send(SOCKET socket, BYTE* pBuf, int len, int* actuallyLen, bool b = true);

		//************************************
		// Method:    Connect
		// Parameter: socket: socket
		// Parameter: ip
		// Parameter: port
		//************************************
		static bool Connect(SOCKET socket, string ip, int port, bool b = true);

		//************************************
		// Method:    Select
		//************************************
		static int Select(int nfds, fd_set* readfds, fd_set *writefds, fd_set *exceptfds, const struct timeval *timeout, bool b = true);

		//************************************
		// Method:    Shutdown socket
		//************************************
		static void ShutDown(SOCKET socket, int how = SD_BOTH, bool b = true);

		//************************************
		// Method:    Close socket
		//************************************
		static bool CloseSocket(SOCKET socket, bool b = true);

		//************************************
		// Method:    Set socket NonBlock
		//************************************
		static void SetNonBlock(SOCKET socket, bool nonblock = true);

		//************************************
		// Method:    Get socket Status
		//************************************
		static bool GetSocketOpt(SOCKET socket, char* optval, int* optlen, bool b = true);

		//************************************
		// Method:    Get peer socket addr
		//************************************
		static string GetPeerIpAndPort(SOCKET socket, int* port);

		//************************************
		// Method:    Get Host Name
		// Parameter: bool b
		//************************************
		static string GetHostName(bool b = true);

		//************************************
		// Method:    Host to Ip
		// Parameter: string host
		// Parameter: bool b
		//************************************
		static vector<string> Host_2_Ip(string host, bool b = true);

		//************************************
		// Method:    Get Local Ip list
		// Parameter: bool b
		//************************************
		static vector<string> GetLocalIps(bool b = true);

		//************************************
		// Method:    Get Local First Ip
		// Parameter: bool b
		//************************************
		static string GetLocalIp(bool b = true);
	};
}