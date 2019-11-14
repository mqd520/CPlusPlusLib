
// TimerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Timer.h"
#include "TimerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


Timer* pTimer = nullptr;

// CTimerDlg �Ի���



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


// CTimerDlg ��Ϣ�������

BOOL CTimerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTimerDlg::OnPaint()
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (pTimer == nullptr)
	{
		pTimer = new Timer(2 * 1000);
		pTimer->RegTimerEvt(std::bind(&CTimerDlg::OnTimer1, this, _1, _2));
	}
}


void CTimerDlg::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (pTimer)
	{
		pTimer->Start();
	}
}


void CTimerDlg::OnBnClickedButton3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (pTimer)
	{
		pTimer->Pause();
	}
}


void CTimerDlg::OnBnClickedButton4()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (pTimer)
	{
		pTimer->Resume();
	}
}


void CTimerDlg::OnBnClickedButton5()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (pTimer)
	{
		pTimer->Stop();
	}
}


void CTimerDlg::OnBnClickedButton6()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (pTimer)
	{
		pTimer->Restart();
	}
}


void CTimerDlg::OnBnClickedButton7()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (pTimer)
	{
		delete pTimer;
		pTimer = nullptr;
	}
}


void CTimerDlg::OnBnClickedButton8()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_edLog.SetWindowTextW(L"");
}
