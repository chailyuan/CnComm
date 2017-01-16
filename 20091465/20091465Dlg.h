
// 20091465Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "CnComm.h"

// CMy20091465Dlg �Ի���
class CMy20091465Dlg : public CDialogEx
{
// ����
public:
	CMy20091465Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY20091465_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


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
	// ��Ͽ����
	CComboBox m_ctrlCombo;
	//����˿ں���
	CnComm m_Comm_SerialPort;
	//����˿ڴ�״̬
	bool m_bSerialPortOpened;
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedButtonClose();
	// ���Ϳ��Ӧ�ı���
	CString m_strEditSendMsg;
	afx_msg void OnBnClickedButtonSend();
	// ���տ��Ӧ�ı���
	CString m_strEditReceiveMsg;
	afx_msg void OnBnClickedButtonClear();
	//������Ϣ������
	afx_msg LRESULT OnReceive(WPARAM ch, LPARAM port);
	afx_msg void OnBnClickedButtonClearsend();
};
