
// TcpDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CTcpDlg �Ի���
class CTcpDlg : public CDialogEx
{
// ����
public:
	CTcpDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TCP_DIALOG };

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
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
protected:
	CEdit m_edPort;
	CButton m_btnListen;
public:
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
};