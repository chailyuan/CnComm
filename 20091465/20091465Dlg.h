
// 20091465Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "CnComm.h"

// CMy20091465Dlg 对话框
class CMy20091465Dlg : public CDialogEx
{
// 构造
public:
	CMy20091465Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MY20091465_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// 组合框变量
	CComboBox m_ctrlCombo;
	//定义端口函数
	CnComm m_Comm_SerialPort;
	//定义端口打开状态
	bool m_bSerialPortOpened;
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedButtonClose();
	// 发送框对应的变量
	CString m_strEditSendMsg;
	afx_msg void OnBnClickedButtonSend();
	// 接收框对应的变量
	CString m_strEditReceiveMsg;
	afx_msg void OnBnClickedButtonClear();
	//定义消息处理函数
	afx_msg LRESULT OnReceive(WPARAM ch, LPARAM port);
	afx_msg void OnBnClickedButtonClearsend();
};
