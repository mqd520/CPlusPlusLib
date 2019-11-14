#pragma once

#include "http/Url.h"
using namespace http;


// CUrlInfoDlg 对话框

class CUrlInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CUrlInfoDlg)

public:
	CUrlInfoDlg(Url& url, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUrlInfoDlg();

// 对话框数据
	enum { IDD = IDD_URLINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

protected:
	HICON m_hIcon;

protected:
	virtual BOOL OnInitDialog();

protected:
	void ShowUrlInfo(Url& url);

protected:
	Url url;

public:
	void SetUrlInfo(Url& url);
};
