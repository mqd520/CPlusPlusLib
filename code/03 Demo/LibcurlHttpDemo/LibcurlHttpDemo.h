
// LibcurlHttpDemo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CLibcurlHttpDemoApp: 
// �йش����ʵ�֣������ LibcurlHttpDemo.cpp
//

class CLibcurlHttpDemoApp : public CWinApp
{
public:
	CLibcurlHttpDemoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CLibcurlHttpDemoApp theApp;