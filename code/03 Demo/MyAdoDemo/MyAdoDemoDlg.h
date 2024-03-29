
// MyAdoDemoDlg.h : 头文件
//

#pragma once
#include "afxwin.h"

#include <string>
#include "afxcmn.h"
using namespace std;

#include "MyAdo/AdoResult.h"
using namespace MyAdo;


// CMyAdoDemoDlg 对话框
class CMyAdoDemoDlg : public CDialogEx
{
	// 构造
public:
	CMyAdoDemoDlg(CWnd* pParent = NULL);	// 标准构造函数

	// 对话框数据
	enum { IDD = IDD_MYADODEMO_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


	// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
