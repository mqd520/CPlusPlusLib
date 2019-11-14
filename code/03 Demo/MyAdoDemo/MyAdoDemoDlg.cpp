
// MyAdoDemoDlg.cpp : ʵ���ļ�
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


// CMyAdoDemoDlg �Ի���



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


// CMyAdoDemoDlg ��Ϣ�������

BOOL CMyAdoDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	m_lcDataTable.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMyAdoDemoDlg::OnPaint()
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	bool b = AdoHelper::default.TestConnect();

	wchar_t ch[128] = { 0 };
	swprintf_s(ch, L"%s", b ? L"���ӳɹ�!" : L"����ʧ��!");

	AfxMessageBox(ch);
}


void CMyAdoDemoDlg::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
		((CMyAdoDemoDlg*)theApp.m_pMainWnd)->ShowDialogInfo(_T("���ݿ�ִ�д���"));
	}
	else
	{
		((CMyAdoDemoDlg*)theApp.m_pMainWnd)->ShowDialogInfo(_T("���ݿ�ִ�гɹ�"));

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