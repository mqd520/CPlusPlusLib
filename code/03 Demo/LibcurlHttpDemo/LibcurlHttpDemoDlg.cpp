
// LibcurlHttpDemoDlg.cpp : ʵ���ļ�
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


// CLibcurlHttpDemoDlg �Ի���



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
END_MESSAGE_MAP()


// CLibcurlHttpDemoDlg ��Ϣ�������

BOOL CLibcurlHttpDemoDlg::OnInitDialog()
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

void CLibcurlHttpDemoDlg::OnPaint()
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
HCURSOR CLibcurlHttpDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CLibcurlHttpDemoDlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	LibcurlHttp http;
	LibcurlHttpResult result = http.Get("http://127.0.0.1:8017", true, true);

	int status = result.nHttpStatus;

	OutputDebugStringA(result.response.c_str());
	OutputDebugStringA("\n");
}
