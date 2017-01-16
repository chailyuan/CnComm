
// 20091465Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "20091465.h"
#include "20091465Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMy20091465Dlg 对话框




CMy20091465Dlg::CMy20091465Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy20091465Dlg::IDD, pParent)
	, m_strEditSendMsg(_T(""))
	, m_strEditReceiveMsg(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy20091465Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_ctrlCombo);
	DDX_Text(pDX, IDC_EDIT2, m_strEditSendMsg);
	DDX_Text(pDX, IDC_EDIT1, m_strEditReceiveMsg);
}

BEGIN_MESSAGE_MAP(CMy20091465Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CMy20091465Dlg::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CMy20091465Dlg::OnBnClickedButtonClose)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CMy20091465Dlg::OnBnClickedButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CMy20091465Dlg::OnBnClickedButtonClear)
	ON_MESSAGE(ON_COM_RECEIVE,OnReceive)//自己建立消息响应机制，OnReveive是我们要编写的函数
	ON_BN_CLICKED(IDC_BUTTON_CLEARSEND, &CMy20091465Dlg::OnBnClickedButtonClearsend)
END_MESSAGE_MAP()


// CMy20091465Dlg 消息处理程序

BOOL CMy20091465Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//默认组合框选择第一项
	m_ctrlCombo.SetCurSel(0);
	m_bSerialPortOpened=true;
	GetDlgItem(IDC_BUTTON_CLOSE)->EnableWindow(!m_bSerialPortOpened);
	GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(!m_bSerialPortOpened);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMy20091465Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMy20091465Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMy20091465Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMy20091465Dlg::OnBnClickedButtonOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	int l_Port_Num=0;//l表示局部变量
	l_Port_Num=m_ctrlCombo.GetCurSel()+1;//+1是因为，Get的值是Num-1
	if(!m_Comm_SerialPort.Open(l_Port_Num,9600,0,8,0))
	{
		AfxMessageBox("打开失败，请重新选择端口");

	}
	else
	{
		if(m_Comm_SerialPort.IsOpen())
		{
			AfxMessageBox("所选端口已经打开");
			GetDlgItem(IDC_BUTTON_OPEN)->EnableWindow(!m_bSerialPortOpened);//显示按钮状态
			GetDlgItem(IDC_BUTTON_CLOSE)->EnableWindow(m_bSerialPortOpened);
				GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(m_bSerialPortOpened);
			m_Comm_SerialPort.SetWnd(m_hWnd);
		}
	}
}


void CMy20091465Dlg::OnBnClickedButtonClose()
{
	// TODO: 在此添加控件通知处理程序代码
	m_Comm_SerialPort.Close();
	GetDlgItem(IDC_BUTTON_OPEN)->EnableWindow(m_bSerialPortOpened);//显示按钮状态,关闭close按钮
	GetDlgItem(IDC_BUTTON_CLOSE)->EnableWindow(!m_bSerialPortOpened);//打开open按钮
	GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(!m_bSerialPortOpened);
}


void CMy20091465Dlg::OnBnClickedButtonSend()
{
	// TODO: 在此添加控件通知处理程序代码
	if(!m_bSerialPortOpened)
	{
		MessageBox("请先打开端口");
		return;
	}
	else
	{
		UpdateData(true);
		m_Comm_SerialPort.Write((LPCTSTR)m_strEditSendMsg);
	}
}


void CMy20091465Dlg::OnBnClickedButtonClear()
{
	// TODO: 在此添加控件通知处理程序代码
	m_strEditReceiveMsg="";
	UpdateData(false);
}
LRESULT CMy20091465Dlg::OnReceive(WPARAM ch, LPARAM port)//WPARAM LPARAM是两个消息参数，相当于长整数
{
	char str[100];
	m_Comm_SerialPort.ReadString(str,100);
	m_strEditReceiveMsg+=str;
	UpdateData(false);
	return 0;
}




void CMy20091465Dlg::OnBnClickedButtonClearsend()
{
	// TODO: 在此添加控件通知处理程序代码
	m_strEditSendMsg="";
	UpdateData(false);
}
