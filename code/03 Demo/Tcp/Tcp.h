
// Tcp.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

#include "Service1.h"


// CTcpApp: 
// �йش����ʵ�֣������ Tcp.cpp
//

class CTcpApp : public CWinApp
{
public:
	CTcpApp();

protected:
	Service1 srv1;

public:
	Service1* GetService1();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CTcpApp theApp;