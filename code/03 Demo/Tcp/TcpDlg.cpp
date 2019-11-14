
// TcpDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Tcp.h"
#include "TcpDlg.h"
#include "afxdialogex.h"
#include "Tcp.h"

#include "com/StringTool.h"
using namespace com;

#include "tcp/SocketTool.h"
using namespace tcp;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTcpDlg 对话框



CTcpDlg::CTcpDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTcpDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTcpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edPort);
	DDX_Control(pDX, IDC_BUTTON5, m_btnListen);
}

BEGIN_MESSAGE_MAP(CTcpDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CTcpDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTcpDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CTcpDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CTcpDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CTcpDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CTcpDlg::OnBnClickedButton6)
END_MESSAGE_MAP()


// CTcpDlg 消息处理程序

BOOL CTcpDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	m_edPort.SetWindowTextW(L"7099");

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTcpDlg::OnPaint()
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
HCURSOR CTcpDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTcpDlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	vector<string> vec = SocketTool::Host_2_Ip("");
}


void CTcpDlg::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码
	string hostname = SocketTool::GetHostName();
}


void CTcpDlg::OnBnClickedButton3()
{
	// TODO:  在此添加控件通知处理程序代码
	vector<string> vec = SocketTool::GetLocalIps();
}


void CTcpDlg::OnBnClickedButton4()
{
	// TODO:  在此添加控件通知处理程序代码
	string ip = SocketTool::GetLocalIp();
}


void CTcpDlg::OnBnClickedButton5()
{
	// TODO:  在此添加控件通知处理程序代码
	CString str;
	m_edPort.GetWindowTextW(str);

	int port = StringTool::To_Int32(StringTool::UTF16_2_GB2312(str.GetBuffer()));

	theApp.GetService1()->GetTcpServer()->ResetAddr("127.0.0.1", port);

	bool b = theApp.GetService1()->GetTcpServer()->Run();
	if (b)
	{
		m_btnListen.EnableWindow(FALSE);
		m_edPort.EnableWindow(FALSE);
	}
}


void CTcpDlg::OnBnClickedButton6()
{
	// TODO:  在此添加控件通知处理程序代码
	theApp.GetService1()->GetTcpServer()->Stop();
	
	m_btnListen.EnableWindow(TRUE);
	m_edPort.EnableWindow(TRUE);
}
