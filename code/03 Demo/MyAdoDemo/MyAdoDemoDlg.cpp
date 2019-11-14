
// MyAdoDemoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MyAdoDemo.h"
#include "MyAdoDemoDlg.h"
#include "afxdialogex.h"

#include "MyAdo/Ado.h"
#include "MyAdo/DbService.h"
#include "MyAdo/MyAdoApp.h"
using namespace MyAdo;

#include "com/StringTool.h"
#include "com/CommonTool.h"
using namespace com;

#include "AdoHelper.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyAdoDemoDlg 对话框



CMyAdoDemoDlg::CMyAdoDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyAdoDemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyAdoDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_lcDataTable);
}

BEGIN_MESSAGE_MAP(CMyAdoDemoDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMyAdoDemoDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMyAdoDemoDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMyAdoDemoDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CMyAdoDemoDlg 消息处理程序

BOOL CMyAdoDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	m_lcDataTable.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMyAdoDemoDlg::OnPaint()
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
HCURSOR CMyAdoDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMyAdoDemoDlg::ShowDialogInfo(CString str)
{
	AfxMessageBox(str);
}


void CMyAdoDemoDlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	bool b = AdoHelper::default.TestConnect();

	wchar_t ch[128] = { 0 };
	swprintf_s(ch, L"%s", b ? L"连接成功!" : L"连接失败!");

	AfxMessageBox(ch);
}


void CMyAdoDemoDlg::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码
	//DbRequest req;
	////req.sql = StringTool::Format("UPDATE dbo.GameUserInfo SET GUName = '%d' WHERE GUUserID = 936", CommonTool::Rand());
	//req.sql = StringTool::Format("SELECT TOP 10 * FROM dbo.GameUserInfo");
	//req.pAdo = &AdoHelper::default;
	//req.type = EDbRequstType::Query;
	//req.cmdType = ECmdType::Text;
	//req.callback = std::bind(&CMyAdoDemoDlg::OnDbResult, this, _1, _2, _3);

	//_dbSrv.PushDbRequest(req);

	//for (int i = 0; i < 30; i++)
	//{
	//	DbRequest req;
	//	req.sql = "SELECT TOP 10 * FROM dbo.GameUserInfo";
	//	req.pAdo = &AdoHelper::default;
	//	req.type = EDbRequstType::Query;
	//	req.cmdType = ECmdType::Text;
	//	_dbSrv.PushDbRequest(req);
	//}
}


void CMyAdoDemoDlg::OnBnClickedButton3()
{
	// TODO:  在此添加控件通知处理程序代码
	//DbConnInfo info = GetDbConnInfo();

	//string sql = "select top 10 GUUserID, GUName, GUAccount, ac_meScore, GUUserRight from GameUserInfo;";

	//AdoParam param;

	//AdoResult result = ado.ReadDataSet(sql.c_str(), param);

	//if (!result.bError)
	//{
	//	int n = result.ds.tables[0]->rows.Count();
	//	for (int i = 0; i < n; i++)
	//	{
	//		int userid = result.ds.tables[0]->rows[i]->GetInt(0);
	//		string name = result.ds.tables[0]->rows[i]->GetString(1);
	//	}
	//}

	//ado.CloseConnection();

	//TRACE("%s \n", sql.c_str());
	//TRACE("Result: %d \n", result.nRecordsAffected);
}

void CMyAdoDemoDlg::OnDbResult(AdoResult& result, void* lpParam1, void* lpParam2)
{
	if (result.bError)
	{
		((CMyAdoDemoDlg*)theApp.m_pMainWnd)->ShowDialogInfo(_T("数据库执行错误"));
	}
	else
	{
		((CMyAdoDemoDlg*)theApp.m_pMainWnd)->ShowDialogInfo(_T("数据库执行成功"));

		//if (result.ds.tables.Count() > 0)
		//{
		//	DataTable* pDT = result.ds.tables[0];

		//	for (int i = 0; i < pDT->fields.Count(); i++)
		//	{
		//		m_lcDataTable.InsertColumn(i + 1, StringTool::GB2312_2_UTF16((char*)pDT->fields[i].strFieldName.c_str()).c_str(), LVCFMT_CENTER, 100);
		//	}

		//	for (int i = 0; i < pDT->rows.Count(); i++)
		//	{
		//		DataRow* pDR = pDT->rows[i];

		//		m_lcDataTable.InsertItem(i, _bstr_t(pDR->GetValue(0)));
		//		for (int j = 1; j < pDT->fields.Count(); j++)
		//		{
		//			m_lcDataTable.SetItemText(i, j, _bstr_t(pDR->GetValue(j)));
		//		}
		//	}
		//}
	}
}