
// MyAdoDemo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMyAdoDemoApp: 
// �йش����ʵ�֣������ MyAdoDemo.cpp
//

class CMyAdoDemoApp : public CWinApp
{
public:
	CMyAdoDemoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CMyAdoDemoApp theApp;