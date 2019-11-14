
// TimerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Timer.h"
#include "TimerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


Timer* pTimer = nullptr;

// CTimerDlg 对话框



CTimerDlg::CTimerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTimerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTimerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edLog);
}

BEGIN_MESSAGE_MAP(CTimerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CTimerDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTimerDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CTimerDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CTimerDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CTimerDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CTimerDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CTimerDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CTimerDlg::OnBnClickedButton8)
END_MESSAGE_MAP()


// CTimerDlg 消息处理程序

BOOL CTimerDlg::OnInitDialog()
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

void CTimerDlg::OnPaint()
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
HCURSOR CTimerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTimerDlg::WriteLog(CString log)
{
	CString str;
	m_edLog.GetWindowTextW(str);

	CString str1 = log + L"\r\n" + str;

	m_edLog.SetWindowTextW(str1);
}

void CTimerDlg::OnTimer1(Timer* p, int count)
{
	wchar_t ch[1024] = { 0 };
	wsprintfW(ch, L"OnTimer: %d", count);

	WriteLog(ch);
}

void CTimerDlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	if (pTimer == nullptr)
	{
		pTimer = new Timer(2 * 1000);
		pTimer->RegTimerEvt(std::bind(&CTimerDlg::OnTimer1, this, _1, _2));
	}
}


void CTimerDlg::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码
	if (pTimer)
	{
		pTimer->Start();
	}
}


void CTimerDlg::OnBnClickedButton3()
{
	// TODO:  在此添加控件通知处理程序代码
	if (pTimer)
	{
		pTimer->Pause();
	}
}


void CTimerDlg::OnBnClickedButton4()
{
	// TODO:  在此添加控件通知处理程序代码
	if (pTimer)
	{
		pTimer->Resume();
	}
}


void CTimerDlg::OnBnClickedButton5()
{
	// TODO:  在此添加控件通知处理程序代码
	if (pTimer)
	{
		pTimer->Stop();
	}
}


void CTimerDlg::OnBnClickedButton6()
{
	// TODO:  在此添加控件通知处理程序代码
	if (pTimer)
	{
		pTimer->Restart();
	}
}


void CTimerDlg::OnBnClickedButton7()
{
	// TODO:  在此添加控件通知处理程序代码
	if (pTimer)
	{
		delete pTimer;
		pTimer = nullptr;
	}
}


void CTimerDlg::OnBnClickedButton8()
{
	// TODO:  在此添加控件通知处理程序代码
	m_edLog.SetWindowTextW(L"");
}
