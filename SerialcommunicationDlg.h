
// SerialcommunicationDlg.h : ͷ�ļ�
//

#pragma once
#include "resource.h"	

// CSerialcommunicationDlg �Ի���
class CSerialcommunicationDlg : public CDialogEx
{
// ����
public:
	CSerialcommunicationDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SERIALCOMMUNICATION_DIALOG };
	
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

public:
	void InitComboBox();

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnCommcontrol();
	afx_msg void OnBnClickedBtnSend();
};
