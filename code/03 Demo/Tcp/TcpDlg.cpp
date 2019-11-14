
// TcpDlg.cpp : ʵ���ļ�
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


// CTcpDlg �Ի���



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


// CTcpDlg ��Ϣ�������

BOOL CTcpDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	m_edPort.SetWindowTextW(L"7099");

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTcpDlg::OnPaint()
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
HCURSOR CTcpDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTcpDlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	vector<string> vec = SocketTool::Host_2_Ip("");
}


void CTcpDlg::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	string hostname = SocketTool::GetHostName();
}


void CTcpDlg::OnBnClickedButton3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	vector<string> vec = SocketTool::GetLocalIps();
}


void CTcpDlg::OnBnClickedButton4()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	string ip = SocketTool::GetLocalIp();
}


void CTcpDlg::OnBnClickedButton5()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	theApp.GetService1()->GetTcpServer()->Stop();
	
	m_btnListen.EnableWindow(TRUE);
	m_edPort.EnableWindow(TRUE);
}
