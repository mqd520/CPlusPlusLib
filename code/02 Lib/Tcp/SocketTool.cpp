#include "stdafx.h"
#include "Include/tcp/SocketTool.h"

#include <WS2tcpip.h>

#include "com/Log.h"
using namespace com;


namespace tcp
{
	SocketTool::SocketTool()
	{

	}

	void SocketTool::ProcessErrorInfo(string fn, int code, string remark /*= ""*/, bool b /*= true*/)
	{
		if (b)
		{
			char ch[256] = { 0 };
			sprintf_s(ch, "socket error, fn: %s, code: %d, remark: %s", fn.c_str(), code, remark.c_str());

			Log::Write_2_File(ECommonLogType::Error, true, ch);
		}
	}

	bool SocketTool::Init(bool b /*= true*/)
	{
		WSADATA wsaData;
		if (WSAStartup(MAKEWORD(2, 2), &wsaData))
		{
			if (b)
			{
				ProcessErrorInfo("WSAStartup", WSAGetLastError(), "", b);
			}

			return false;
		}

		return true;
	}

	void SocketTool::Exit()
	{
		WSACleanup();
	}

	SOCKET SocketTool::CreateTcpSocket(bool b /*= true*/)
	{
		SOCKET s = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (s == INVALID_SOCKET)
		{
			if (b)
			{
				ProcessErrorInfo("::socket", WSAGetLastError(), "create socket fail", b);
			}
		}

		return s;
	}

	SOCKET SocketTool::CreateLPTcpSocket(bool b /*= true*/)
	{
		if (Init(b))
		{
			SOCKET s = ::WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
			if (s == INVALID_SOCKET)
			{
				if (b)
				{
					ProcessErrorInfo("::WSASocket", WSAGetLastError(), "create socket fail", b);
				}
			}

			return s;
		}

		return INVALID_SOCKET;
	}

	SOCKADDR_IN SocketTool::GetSocketAddr(string ip, int port)
	{
		SOCKADDR_IN addr;
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
		if (ip.empty())
		{
			addr.sin_addr.S_un.S_addr = INADDR_ANY;
		}
		else
		{
			in_addr s;
			inet_pton(AF_INET, ip.c_str(), (void*)&s);
			addr.sin_addr.S_un.S_addr = s.S_un.S_addr;
		}
		return addr;
	}

	bool SocketTool::Bind(SOCKET socket, string ip, int port, bool b /*= true*/)
	{
		SOCKADDR_IN addr = GetSocketAddr(ip, port);
		int result = ::bind(socket, (SOCKADDR*)&addr, sizeof(addr));
		if (result == 0)
		{
			return true;
		}
		else
		{
			if (b)
			{
				char ch[50] = { 0 };
				sprintf_s(ch, "bind fail, ip: %s, port: %d", ip.c_str(), port);
				ProcessErrorInfo("bind", WSAGetLastError(), ch, b);
			}

			return false;
		}
	}

	bool SocketTool::Listen(SOCKET socket, string ip, int port, int backlog /*= SOMAXCONN*/, bool b /*= true*/)
	{
		int ret = ::listen(socket, backlog);
		if (ret == 0)
		{
			return true;
		}
		else
		{
			if (b)
			{
				char ch[100] = { 0 };
				sprintf_s(ch, "listen fail, socket: %d, ip: %s, port: %d", socket, ip.c_str(), port);
				ProcessErrorInfo("listen", WSAGetLastError(), ch, b);
			}

			return false;
		}
	}

	SOCKET SocketTool::Accept(SOCKET socket, string ip, int port, bool b /*= true*/)
	{
		SOCKADDR_IN addr = GetSocketAddr(ip, port);
		SOCKET client = ::accept(socket, (SOCKADDR*)&addr, NULL);
		if (client == INVALID_SOCKET)
		{
			if (b)
			{
				char ch[100] = { 0 };
				sprintf_s(ch, "accept fail, socket: %d, ip: %s, port: %d", socket, ip.c_str(), port);
				ProcessErrorInfo("accept", WSAGetLastError(), ch, b);
			}
		}

		return client;
	}

	bool SocketTool::Recv(SOCKET socket, BYTE* pBuf, int len, int* actuallyLen, bool b /*= true*/)
	{
		bool connected = false;
		int ret = ::recv(socket, (char*)pBuf, len, 0);
		int nError = WSAGetLastError();
		int n = errno;

		if (actuallyLen != NULL)
		{
			*actuallyLen = ret;
		}

		if (ret > 0)
		{
			connected = true;
		}
		else
		{
			if (ret == SOCKET_ERROR)
			{
				if (b)
				{
					char ch[100] = { 0 };
					sprintf_s(ch, "recv fail, socket: %d", socket);
					ProcessErrorInfo("recv", nError, ch, b);
				}
			}

			if (nError == WSAEWOULDBLOCK || nError == WSAEINPROGRESS || n == EINTR)
			{
				connected = true;
			}
		}

		return connected;
	}

	bool SocketTool::Send(SOCKET socket, BYTE* pBuf, int len, int* actuallyLen, bool b /*= true*/)
	{
		bool connected = false;
		int ret = ::send(socket, (const char*)pBuf, len, 0);
		int nError = WSAGetLastError();
		int n = errno;

		if (actuallyLen != NULL)
		{
			*actuallyLen = ret;
		}

		if (ret > 0)
		{
			connected = true;
		}
		else
		{
			if (ret == SOCKET_ERROR)
			{
				if (b)
				{
					char ch[100] = { 0 };
					sprintf_s(ch, "send fail, socket: %d", socket);
					ProcessErrorInfo("send", WSAGetLastError(), ch, b);
				}
			}

			if (nError == WSAEWOULDBLOCK || nError == WSAEINPROGRESS || n == EINTR)
			{
				connected = true;
			}
		}

		return connected;
	}

	bool SocketTool::Connect(SOCKET socket, string ip, int port, bool b /*= true*/)
	{
		SOCKADDR_IN addr = GetSocketAddr(ip, port);
		int ret = ::connect(socket, (SOCKADDR*)&addr, sizeof(addr));

		if (ret == SOCKET_ERROR)
		{
			if (b)
			{
				char ch[100] = { 0 };
				sprintf_s(ch, "connect fail, socket: %d, ip: %s, port: %d", socket, ip.c_str(), port);
				ProcessErrorInfo("connect", WSAGetLastError(), ch, b);
			}

			return false;
		}

		return true;
	}

	int SocketTool::Select(int nfds, fd_set* readfds, fd_set *writefds, fd_set *exceptfds, const struct timeval *timeout, bool b /*= true*/)
	{
		int ret = ::select(nfds, readfds, writefds, exceptfds, timeout);

		if (ret == SOCKET_ERROR)
		{
			if (b)
			{
				ProcessErrorInfo("select", WSAGetLastError(), "select fail", b);
			}
		}

		return ret;
	}


	void SocketTool::ShutDown(SOCKET socket, int how /*= SD_BOTH*/, bool b /*= true*/)
	{
		int ret = ::shutdown(socket, how);

		if (ret == SOCKET_ERROR)
		{
			if (b)
			{
				char ch[100] = { 0 };
				sprintf_s(ch, "shutdown fail, socket: %d", socket);
				ProcessErrorInfo("shutdown", WSAGetLastError(), ch, b);
			}
		}
	}

	bool SocketTool::CloseSocket(SOCKET socket, bool b /*= true*/)
	{
		int ret = ::closesocket(socket);

		if (ret == SOCKET_ERROR)
		{
			if (b)
			{
				char ch[100] = { 0 };
				sprintf_s(ch, "closesocket fail, socket: %d", socket);
				ProcessErrorInfo("closesocket", WSAGetLastError(), ch, b);
			}
			return false;
		}

		return true;
	}

	void SocketTool::SetNonBlock(SOCKET socket, bool nonblock /*= true*/)
	{
		u_long mode = nonblock ? 1 : 0;
		::ioctlsocket(socket, FIONBIO, &mode);
	}

	bool SocketTool::GetSocketOpt(SOCKET socket, char* optval, int* optlen, bool b /*= true*/)
	{
		int result = ::getsockopt(socket, SOL_SOCKET, SO_SNDBUF, optval, optlen);
		return result == 1;
	}

	string SocketTool::GetPeerIpAndPort(SOCKET socket, int* port)
	{
		string strIP = "";

		SOCKADDR_IN addr;
		int len = sizeof(addr);
		int result = ::getpeername(socket, (SOCKADDR*)&addr, &len);
		if (result != SOCKET_ERROR)
		{
			char ch[30] = { 0 };
			in_addr s;
			s.S_un = addr.sin_addr.S_un;
			inet_ntop(AF_INET, (void*)&s, ch, 30);
			strIP = ch;

			if (port != NULL)
			{
				*port = ntohs(addr.sin_port);
			}
		}

		return strIP;
	}

	string SocketTool::GetHostName(bool b /*= true*/)
	{
		char ch[128] = { 0 };

		WSADATA wsaData;
		int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (ret == 0)
		{
			int ret = ::gethostname(ch, sizeof(ch));
			if (ret != 0)
			{
				ProcessErrorInfo("gethostname", WSAGetLastError(), "", b);
			}
		}

		return ch;
	}

	vector<string> SocketTool::Host_2_Ip(string host, bool b /*= true*/)
	{
		vector<string> vec;

		WSADATA wsaData;
		int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (ret == 0)
		{
			struct addrinfo hints;
			struct addrinfo *res, *cur;
			struct sockaddr_in *addr;
			char chIp[30] = { 0 };

			memset(&hints, 0, sizeof(struct addrinfo));

			hints.ai_family = AF_INET;
			hints.ai_flags = AI_PASSIVE;
			hints.ai_protocol = 0;
			hints.ai_socktype = SOCK_STREAM;

			int ret = getaddrinfo(host.c_str(), NULL, &hints, &res);
			if (ret == -1)
			{
				char ch[100] = { 0 };
				sprintf_s(ch, "closesocket fail, socket: %d", socket);
				ProcessErrorInfo("getaddrinfo", WSAGetLastError(), ch, b);
			}
			else
			{
				for (cur = res; cur != nullptr; cur = cur->ai_next)
				{
					memset(chIp, 0, 30);

					addr = (struct sockaddr_in *)cur->ai_addr;
					sprintf_s(chIp, "%u.%u.%u.%u",
						(*addr).sin_addr.S_un.S_un_b.s_b1,
						(*addr).sin_addr.S_un.S_un_b.s_b2,
						(*addr).sin_addr.S_un.S_un_b.s_b3,
						(*addr).sin_addr.S_un.S_un_b.s_b4);

					vec.emplace_back(chIp);
				}
			}

			freeaddrinfo(res);
		}

		return vec;
	}

	vector<string> SocketTool::GetLocalIps(bool b /*= true*/)
	{
		vector<string> vec;

		string hostname = GetHostName(b);
		if (!hostname.empty())
		{
			vec = Host_2_Ip(hostname);
		}

		return vec;
	}

	string SocketTool::GetLocalIp(bool b /*= true*/)
	{
		vector<string> vec = GetLocalIps(b);
		if (!vec.empty())
		{
			return vec[0];
		}

		return "";
	}
}