
// LibcurlHttpDemoDlg.h : ͷ�ļ�
//

#pragma once


// CLibcurlHttpDemoDlg �Ի���
class CLibcurlHttpDemoDlg : public CDialogEx
{
// ����
public:
	CLibcurlHttpDemoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_LIBCURLHTTPDEMO_DIALOG };

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
};
