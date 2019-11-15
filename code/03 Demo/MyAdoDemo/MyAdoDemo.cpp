
// MyAdoDemo.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "MyAdoDemo.h"
#include "MyAdoDemoDlg.h"

#include <iostream>
#include <fstream>
using namespace std;

#include <sys/timeb.h>

#include "com/Log.h"
#include "com/CommonTool.h"
#include "com/TimeTool.h"
#include "com/StringTool.h"
using namespace com;

#include "MyAdo/MyAdoApp.h"
using namespace MyAdo;

#include "AdoHelper.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyAdoDemoApp

BEGIN_MESSAGE_MAP(CMyAdoDemoApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


void OnLog(ELogType type, string& log, ExtraLogInfo& info);



// CMyAdoDemoApp ����

CMyAdoDemoApp::CMyAdoDemoApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CMyAdoDemoApp ����

CMyAdoDemoApp theApp;


// CMyAdoDemoApp ��ʼ��

BOOL CMyAdoDemoApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()��  ���򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ���Windows Native���Ӿ����������Ա��� MFC �ؼ�����������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO:  Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));



	Log::RegLogFileCallback(OnLog);



	MyAdoApp::Init(1);
	AdoHelper::Init();


	CMyAdoDemoDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO:  �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO:  �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
		TRACE(traceAppMsg, 0, "����: ������ڶԻ�����ʹ�� MFC �ؼ������޷� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS��\n");
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

void OnLog(ELogType type, string& log, ExtraLogInfo& info)
{
	string path = CommonTool::GetCurrentExeDir() + "log.txt";

	char ch[1024] = { 0 };
	sprintf_s(ch, "[%s] [%s] [0x%04x] [%s:%s:%d] \n %s \n\n",
		TimeTool::Format(info.time, true, "yyyy-mm-dd HH:MM:ss.ff").c_str(),
		Log::GetLogTypeStr(type).c_str(),
		info.nThreadId,
		info.strFileName.c_str(),
		info.strFunctionName.c_str(),
		info.nRowNo,
		log.c_str());

	fstream fs;
	fs.open(path, ios::app);
	fs << ch;
	fs.close();
}

int CMyAdoDemoApp::ExitInstance()
{
	// TODO:  �ڴ����ר�ô����/����û���

	char ch[1024] = { 0 };
	sprintf_s(ch, "MyAdoApp::Exit, time: %s \n", TimeTool::Format("yyyy-mm-dd HH:MM:ss.ff").c_str());
	OutputDebugStringA(ch);

	MyAdoApp::Exit(1 * 1000);
	AdoHelper::Exit();

	return CWinApp::ExitInstance();
}
