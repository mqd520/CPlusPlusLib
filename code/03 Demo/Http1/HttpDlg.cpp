
// HttpDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Http.h"
#include "HttpDlg.h"
#include "afxdialogex.h"


#include "com/StringTool.h"
using namespace com;

#include "http/Url.h"
using namespace http;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHttpDlg �Ի���



CHttpDlg::CHttpDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHttpDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHttpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edUrl);
}

BEGIN_MESSAGE_MAP(CHttpDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CHttpDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CHttpDlg ��Ϣ�������

BOOL CHttpDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	m_edUrl.SetWindowText(_T("http://192.168.0.1:8088/path1/path2?Id=1&str=test001"));

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CHttpDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CHttpDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CHttpDlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString strUrl;
	m_edUrl.GetWindowTextW(strUrl);

	string strUrl1 = StringTool::UTF16_2_GB2312(strUrl.GetBuffer());
	int n = strUrl1.find("http://");
	Url url(strUrl1);

	char ch[1024] = { 0 };
	sprintf_s(ch, "\
 Absolute url: %s \n\n\
     Protocol: %s \n\n\
         Host: %s \n\n\
     HostAddr: %s \n\n\
	 HostType: %s \n\n\
         Port: %d \n\n\
Absolute path: %s \n\n\
 Request path: %s \n\n\
  Query param: %s \n", 
url.GetAbsoluteUrl().c_str(),
url.GetHttpProtocol().c_str(),
url.GetHost().c_str(),
url.GetHostAddr().c_str(),
url.GetHostType() == EHostType::Ip ? "Ip" : "Doamin name",
url.GetPort(),
url.GetAbsolutePath().c_str(),
url.GetRequestPath().c_str(),
url.GetQueryParam().c_str());

	OutputDebugStringA("Parse url result: \n");
	OutputDebugStringA(ch);
	OutputDebugStringA("\n");

	MessageBoxA(m_hWnd, ch, "Http", MB_OK);
}
