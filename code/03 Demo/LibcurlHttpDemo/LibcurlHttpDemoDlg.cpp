
// LibcurlHttpDemoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LibcurlHttpDemo.h"
#include "LibcurlHttpDemoDlg.h"
#include "afxdialogex.h"

#include "libcurlHttp/LibcurlHttp.h"
using namespace libcurlHttp;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLibcurlHttpDemoDlg 对话框



CLibcurlHttpDemoDlg::CLibcurlHttpDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLibcurlHttpDemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLibcurlHttpDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLibcurlHttpDemoDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CLibcurlHttpDemoDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CLibcurlHttpDemoDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CLibcurlHttpDemoDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CLibcurlHttpDemoDlg 消息处理程序

BOOL CLibcurlHttpDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CLibcurlHttpDemoDlg::OnPaint()
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
HCURSOR CLibcurlHttpDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CLibcurlHttpDemoDlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	LibcurlHttp http;
	http.SetFormItem("username", "AAtest001");
	http.SetFormItem("pwd", "123456");
	LibcurlHttpResult result = http.Post("http://192.168.43.121:8001", true, true);

	int status = result.nHttpStatus;

	OutputDebugStringA(result.response.c_str());
	OutputDebugStringA("\n");
}


void CLibcurlHttpDemoDlg::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码
	LibcurlHttp http;
	http.SetBodyData(R"({"username": "AAtest001", "pwd": "123456"})");
	LibcurlHttpResult result = http.Post("http://192.168.43.121:8001/json", false, false, "application/json");

	int status = result.nHttpStatus;

	OutputDebugStringA(result.response.c_str());
	OutputDebugStringA("\n");
}


void CLibcurlHttpDemoDlg::OnBnClickedButton3()
{
	// TODO:  在此添加控件通知处理程序代码
	LibcurlHttp http;
	LibcurlHttpResult result = http.Get("http://www.baidu.com", false, false);

	int status = result.nHttpStatus;

	OutputDebugStringA(result.response.c_str());
	OutputDebugStringA("\n");
}
