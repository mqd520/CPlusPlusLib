#include "StdAfx.h"

#include "SocketBuf.h"
#include "AutoLock.h"

CSocketBuf::CSocketBuf(SocketBuf::PFNPutTip pfnPutTip, void * pThis)
{
	m_pfnPutTip = pfnPutTip;
	m_pThis = pThis;
}

CSocketBuf::~CSocketBuf(void)
{
}

/******************************************************************************
初始化
******************************************************************************/
void CSocketBuf::Init(void)
{
	//互斥锁
	CAutoLock lock(&m_csLock, m_pfnPutTip, m_pThis);

	m_setSocket.clear();
}

/******************************************************************************
创建
******************************************************************************/
SOCKET CSocketBuf::Create(void)
{
	//互斥锁
	CAutoLock lock(&m_csLock, m_pfnPutTip, m_pThis);

	//创建套接字
	SOCKET socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0
		, WSA_FLAG_OVERLAPPED);
	if (socket == INVALID_SOCKET)
	{
		_PutTip("", SocketBuf::CREATE_CREATE_FAIL);
		return INVALID_SOCKET;
	}

	//加入套接字表
	pair<set<SOCKET>::iterator, bool> pr = m_setSocket.insert(socket);
	if (!pr.second)
	{
		_PutTip("", SocketBuf::CREATE_INSERT_SET_FAIL);
		return INVALID_SOCKET;
	}

	return socket;
}

/******************************************************************************
创建
******************************************************************************/
SOCKET CSocketBuf::Create(unsigned short usPort)
{
	//创建
	SOCKET socket = Create();

	//本地地址信息
	sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (usPort < 0)
	{
		_PutTip("", SocketBuf::CREATE_PORT_INVALID);
		return INVALID_SOCKET;
	}
	addr.sin_port = htons(usPort);

	//绑定套接字
	if (socket == INVALID_SOCKET)
	{
		_PutTip("", SocketBuf::CREATE_SOCKET_INVALID);
		return INVALID_SOCKET;
	}
	if (bind(socket ,(SOCKADDR *)&addr, sizeof(addr)) != 0)
	{
		if (WSAGetLastError() != WSAEADDRINUSE)
		{
			_PutTip("", SocketBuf::CREATE_BIND_FAIL);
			return INVALID_SOCKET;
		}

		//关闭
		Close(socket);
		return INVALID_SOCKET;
	}

	return socket;
}

/******************************************************************************
关闭
******************************************************************************/
void CSocketBuf::Close(SOCKET socket)
{
	//互斥锁
	CAutoLock lock(&m_csLock, m_pfnPutTip, m_pThis);

	//套接字不存在
	if (socket == INVALID_SOCKET)
	{
		_PutTip("", SocketBuf::CLOSE_SOCKET_INVALID);
		return;
	}
	set<SOCKET>::iterator it = m_setSocket.find(socket);
	if (it == m_setSocket.end())
	{
		_PutTip("", SocketBuf::CLOSE_SOCKET_NOT_EXIST);
		return;
	}

	//从套接字表中删除
	try
	{
		m_setSocket.erase(it);
	}
	catch (...)
	{
		_PutTip("", SocketBuf::CLOSE_ERASE_EXCEPTION);
		return;
	}

	//关闭套接字
	if (closesocket(socket) != 0)
	{
		_PutTip("", SocketBuf::CLOSE_CLOSE_SOCKET_FAIL);
		return;
	}
}

/******************************************************************************
清空
******************************************************************************/
void CSocketBuf::Clear(void)
{
	//互斥锁
	CAutoLock lock(&m_csLock, m_pfnPutTip, m_pThis);

	//遍历套接字表
	set<SOCKET>::iterator it = m_setSocket.begin();
	while (it != m_setSocket.end())
	{
		//获取套接字
		SOCKET socket = *it;
		if (socket == INVALID_SOCKET)
		{
			_PutTip("", SocketBuf::CLEAR_SOCKET_INVALID);
			return;
		}

		//从套接字表中删除
		try
		{
			it = m_setSocket.erase(it);
		}
		catch (...)
		{
			_PutTip("", SocketBuf::CLEAR_ERASE_EXCEPTION);
			return;
		}

		//关闭套接字
		if (closesocket(socket) != 0)
		{
			_PutTip("", SocketBuf::CLEAR_CLOSE_SOCKET_FAIL);
			return;
		}
	}
}

/******************************************************************************
输出提示
******************************************************************************/
void CSocketBuf::_PutTip(string strTip, int iErr, string strErr)
{
	//输出提示回调
	if (m_pfnPutTip == NULL
		|| m_pThis == NULL)
	{
		return;
	}
	m_pfnPutTip(strTip, "SocketBuf", iErr, strErr, m_pThis);
}