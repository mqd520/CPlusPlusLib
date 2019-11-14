// UrlInfoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Http.h"
#include "UrlInfoDlg.h"
#include "afxdialogex.h"

#include "com/StringTool.h"
using namespace com;


// CUrlInfoDlg 对话框

IMPLEMENT_DYNAMIC(CUrlInfoDlg, CDialogEx)

CUrlInfoDlg::CUrlInfoDlg(Url& url, CWnd* pParent /*=NULL*/)
	: CDialogEx(CUrlInfoDlg::IDD, pParent),
	url(url)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CUrlInfoDlg::~CUrlInfoDlg()
{
}

void CUrlInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CUrlInfoDlg, CDialogEx)
END_MESSAGE_MAP()

BOOL CUrlInfoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	CFont font;
	font.CreateFont(0, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Arial"));

	GetDlgItem(IDC_STATIC1)->SetFont(&font);
	GetDlgItem(IDC_STATIC2)->SetFont(&font);
	GetDlgItem(IDC_STATIC3)->SetFont(&font);
	GetDlgItem(IDC_STATIC4)->SetFont(&font);
	GetDlgItem(IDC_STATIC5)->SetFont(&font);
	GetDlgItem(IDC_STATIC6)->SetFont(&font);
	GetDlgItem(IDC_STATIC7)->SetFont(&font);
	GetDlgItem(IDC_STATIC8)->SetFont(&font);
	GetDlgItem(IDC_STATIC9)->SetFont(&font);


	ShowUrlInfo(url);


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CUrlInfoDlg::ShowUrlInfo(Url& url)
{
	wstring str1 = StringTool::GB2312_2_UTF16((char*)url.GetAbsoluteUrl().c_str());
	wstring str2 = StringTool::GB2312_2_UTF16((char*)url.GetHttpProtocol().c_str());
	wstring str3 = StringTool::GB2312_2_UTF16((char*)url.GetHost().c_str());
	wstring str4 = StringTool::GB2312_2_UTF16((char*)url.GetHostAddr().c_str());
	wstring str5 = url.GetHostType() == EHostType::Ip ? L"Ip" : L"Domain name";
	wchar_t ch6[20] = { 0 };
	_itow_s(url.GetPort(), ch6, 10);
	wstring str6 = ch6;
	wstring str7 = StringTool::GB2312_2_UTF16((char*)url.GetAbsolutePath().c_str());
	wstring str8 = StringTool::GB2312_2_UTF16((char*)url.GetRequestPath().c_str());
	wstring str9 = StringTool::GB2312_2_UTF16((char*)url.GetQueryParam().c_str());


	GetDlgItem(IDC_STATIC31)->SetWindowTextW(str1.c_str());
	GetDlgItem(IDC_STATIC32)->SetWindowTextW(str2.c_str());
	GetDlgItem(IDC_STATIC33)->SetWindowTextW(str3.c_str());
	GetDlgItem(IDC_STATIC34)->SetWindowTextW(str4.c_str());
	GetDlgItem(IDC_STATIC35)->SetWindowTextW(str5.c_str());
	GetDlgItem(IDC_STATIC36)->SetWindowTextW(str6.c_str());
	GetDlgItem(IDC_STATIC37)->SetWindowTextW(str7.c_str());
	GetDlgItem(IDC_STATIC38)->SetWindowTextW(str8.c_str());
	GetDlgItem(IDC_STATIC39)->SetWindowTextW(str9.c_str());
}

void CUrlInfoDlg::SetUrlInfo(Url& url)
{
	this->url = url;
}

// CUrlInfoDlg 消息处理程序
