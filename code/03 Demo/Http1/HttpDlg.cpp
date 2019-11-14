
// HttpDlg.cpp : 实现文件
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


// CHttpDlg 对话框



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


// CHttpDlg 消息处理程序

BOOL CHttpDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	m_edUrl.SetWindowText(_T("http://192.168.0.1:8088/path1/path2?Id=1&str=test001"));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CHttpDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CHttpDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CHttpDlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
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
