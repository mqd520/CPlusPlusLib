#pragma once

#include "http/Url.h"
using namespace http;


// CUrlInfoDlg �Ի���

class CUrlInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CUrlInfoDlg)

public:
	CUrlInfoDlg(Url& url, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUrlInfoDlg();

// �Ի�������
	enum { IDD = IDD_URLINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
