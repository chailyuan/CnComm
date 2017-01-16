
// 20091465Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "20091465.h"
#include "20091465Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CMy20091465Dlg �Ի���




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
	ON_MESSAGE(ON_COM_RECEIVE,OnReceive)//�Լ�������Ϣ��Ӧ���ƣ�OnReveive������Ҫ��д�ĺ���
	ON_BN_CLICKED(IDC_BUTTON_CLEARSEND, &CMy20091465Dlg::OnBnClickedButtonClearsend)
END_MESSAGE_MAP()


// CMy20091465Dlg ��Ϣ�������

BOOL CMy20091465Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//Ĭ����Ͽ�ѡ���һ��
	m_ctrlCombo.SetCurSel(0);
	m_bSerialPortOpened=true;
	GetDlgItem(IDC_BUTTON_CLOSE)->EnableWindow(!m_bSerialPortOpened);
	GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(!m_bSerialPortOpened);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMy20091465Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMy20091465Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMy20091465Dlg::OnBnClickedButtonOpen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int l_Port_Num=0;//l��ʾ�ֲ�����
	l_Port_Num=m_ctrlCombo.GetCurSel()+1;//+1����Ϊ��Get��ֵ��Num-1
	if(!m_Comm_SerialPort.Open(l_Port_Num,9600,0,8,0))
	{
		AfxMessageBox("��ʧ�ܣ�������ѡ��˿�");

	}
	else
	{
		if(m_Comm_SerialPort.IsOpen())
		{
			AfxMessageBox("��ѡ�˿��Ѿ���");
			GetDlgItem(IDC_BUTTON_OPEN)->EnableWindow(!m_bSerialPortOpened);//��ʾ��ť״̬
			GetDlgItem(IDC_BUTTON_CLOSE)->EnableWindow(m_bSerialPortOpened);
				GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(m_bSerialPortOpened);
			m_Comm_SerialPort.SetWnd(m_hWnd);
		}
	}
}


void CMy20091465Dlg::OnBnClickedButtonClose()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_Comm_SerialPort.Close();
	GetDlgItem(IDC_BUTTON_OPEN)->EnableWindow(m_bSerialPortOpened);//��ʾ��ť״̬,�ر�close��ť
	GetDlgItem(IDC_BUTTON_CLOSE)->EnableWindow(!m_bSerialPortOpened);//��open��ť
	GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(!m_bSerialPortOpened);
}


void CMy20091465Dlg::OnBnClickedButtonSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(!m_bSerialPortOpened)
	{
		MessageBox("���ȴ򿪶˿�");
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_strEditReceiveMsg="";
	UpdateData(false);
}
LRESULT CMy20091465Dlg::OnReceive(WPARAM ch, LPARAM port)//WPARAM LPARAM��������Ϣ�������൱�ڳ�����
{
	char str[100];
	m_Comm_SerialPort.ReadString(str,100);
	m_strEditReceiveMsg+=str;
	UpdateData(false);
	return 0;
}




void CMy20091465Dlg::OnBnClickedButtonClearsend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_strEditSendMsg="";
	UpdateData(false);
}
