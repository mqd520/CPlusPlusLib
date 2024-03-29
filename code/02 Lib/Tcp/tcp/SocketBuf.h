#pragma once

#include <string>
#include <set>
using namespace std;

#include "SocketBufDef.h"

/******************************************************************************
套接字缓冲区类
功能：
	实现套接字的创建、关闭和清空。
作者：
	佳也 2623168833 jaye8090@qq.com
时间：
	2014-11-3 到 2014-11-7
******************************************************************************/
class CSocketBuf
{
public:
	CSocketBuf(SocketBuf::PFNPutTip pfnPutTip = NULL, void * pThis = NULL);

	~CSocketBuf(void);

	/**************************************************************************
	初始化
	说明：
		此接口是线程安全的
	**************************************************************************/
	void Init(void);

//基本接口
public:
	/**************************************************************************
	创建
	说明：
		创建一个套接字
		此接口是线程安全的
	返回：
		套接字
	**************************************************************************/
	SOCKET Create(void);

	/**************************************************************************
	创建
	说明：
		创建一个套接字，并绑定端口。
		此接口是线程安全的
	参数：
		usPort		端口，0表示由系统随机分配端口。
	返回：
		绑定成功返回套接字，否则返回INVALID_SOCKET。
	**************************************************************************/
	SOCKET Create(unsigned short usPort);

	/**************************************************************************
	关闭
	说明：
		关闭一个套接字
		此接口是线程安全的
	参数：
		socket		套接字
	**************************************************************************/
	void Close(SOCKET socket);

	/**************************************************************************
	清空
	说明：
		关闭所有创建的套接字
		此接口是线程安全的
	**************************************************************************/
	void Clear(void);

//内部操作
private:
	/**************************************************************************
	输出提示
	参数：
		strTip		提示
		iErr		错误码
		strErr		错误串
	**************************************************************************/
	void _PutTip(string strTip, int iErr = 0, string strErr = "");

//内部数据
private:
	SocketBuf::PFNPutTip		m_pfnPutTip;		//输出提示回调函数
	void						* m_pThis;			//回调this指针

	CCriticalSection		m_csLock;		//互斥锁

	set<SOCKET>		m_setSocket;		//套接字表
};