
// MyAdoDemoDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"

#include <string>
#include "afxcmn.h"
using namespace std;

#include "MyAdo/AdoResult.h"
using namespace MyAdo;


// CMyAdoDemoDlg �Ի���
class CMyAdoDemoDlg : public CDialogEx
{
	// ����
public:
	CMyAdoDemoDlg(CWnd* pParent = NULL);	// ��׼���캯��

	// �Ի�������
	enum { IDD = IDD_MYADODEMO_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


	// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

protected:
	void OnDbResult(AdoResult& result, void* lpParam1, void* lpParam2);

public:
	void ShowDialogInfo(CString str);

public:
	afx_msg void OnBnClickedButton1();
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
protected:
	CListCtrl m_lcDataTable;
};
