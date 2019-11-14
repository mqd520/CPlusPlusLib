
// Tcp.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号

#include "Service1.h"


// CTcpApp: 
// 有关此类的实现，请参阅 Tcp.cpp
//

class CTcpApp : public CWinApp
{
public:
	CTcpApp();

protected:
	Service1 srv1;

public:
	Service1* GetService1();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CTcpApp theApp;