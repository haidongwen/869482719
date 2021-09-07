
// SerialcommunicationDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Serialcommunication.h"
#include "SerialcommunicationDlg.h"
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


// CSerialcommunicationDlg �Ի���



CSerialcommunicationDlg::CSerialcommunicationDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSerialcommunicationDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSerialcommunicationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSerialcommunicationDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_COMMCONTROL, &CSerialcommunicationDlg::OnBnClickedBtnCommcontrol)
	ON_BN_CLICKED(IDC_BTN_SEND, &CSerialcommunicationDlg::OnBnClickedBtnSend)
END_MESSAGE_MAP()


// CSerialcommunicationDlg ��Ϣ�������

BOOL CSerialcommunicationDlg::OnInitDialog()
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	InitComboBox();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CSerialcommunicationDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSerialcommunicationDlg::OnPaint()
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
HCURSOR CSerialcommunicationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSerialcommunicationDlg::InitComboBox()
{
	CComboBox *pComboComm = (CComboBox*)GetDlgItem(IDC_COMBO_COMM);
	ASSERT(pComboComm);

	for (int i = 1; i <= 8; i++)
	{
		CString strComm;
		strComm.Format(_T("COM%d"), i);
		pComboComm->AddString(strComm);
	}
	pComboComm->SetCurSel(0); //ѡ�е�0���б�

	//��Ӳ�����
	CComboBox *pComboBaudrate = (CComboBox*)GetDlgItem(IDC_COMBO_BAUDRATE);
	ASSERT(pComboBaudrate);
	pComboBaudrate->SetItemData(pComboBaudrate->AddString(_T("300")), 300);  //�ַ�300������300����
	pComboBaudrate->SetItemData(pComboBaudrate->AddString(_T("600")), 600);
	pComboBaudrate->SetItemData(pComboBaudrate->AddString(_T("1200")), 1200);
	pComboBaudrate->SetItemData(pComboBaudrate->AddString(_T("2400")), 2400);
	pComboBaudrate->SetItemData(pComboBaudrate->AddString(_T("4800")), 4800);
	pComboBaudrate->SetItemData(pComboBaudrate->AddString(_T("9600")), 9600);
	pComboBaudrate->SetItemData(pComboBaudrate->AddString(_T("19200")), 19200);
	pComboBaudrate->SetItemData(pComboBaudrate->AddString(_T("38400")), 38400);
	pComboBaudrate->SetItemData(pComboBaudrate->AddString(_T("43000")), 43000);
	pComboBaudrate->SetItemData(pComboBaudrate->AddString(_T("56000")), 56000);
	pComboBaudrate->SetItemData(pComboBaudrate->AddString(_T("17600")), 17600);
	pComboBaudrate->SetItemData(pComboBaudrate->AddString(_T("115200")), 115200);
	pComboBaudrate->SetCurSel(5); //ѡ�е�5���б�

	//���У��λ
	CComboBox *pComboCheckBit = (CComboBox*)GetDlgItem(IDC_COMBO_CHECKBIT);
	ASSERT(pComboCheckBit);
	pComboCheckBit->SetItemData(pComboCheckBit->AddString(_T("��None")), NOPARITY);
	pComboCheckBit->SetItemData(pComboCheckBit->AddString(_T("��0DD")), ODDPARITY);
	pComboCheckBit->SetItemData(pComboCheckBit->AddString(_T("żEVEN")), EVENPARITY);
	pComboCheckBit->SetCurSel(0);

	//�������λ
	CComboBox *pComboDataBit = (CComboBox*)GetDlgItem(IDC_COMBO_DATABIT);
	ASSERT(pComboDataBit);
	pComboDataBit->SetItemData(pComboDataBit->AddString(_T("6")), 6);
	pComboDataBit->SetItemData(pComboDataBit->AddString(_T("7")), 7);
	pComboDataBit->SetItemData(pComboDataBit->AddString(_T("8")), 8);
	pComboDataBit->SetCurSel(2);

	//���ֹͣλ
	CComboBox *pComboStopBit = (CComboBox*)GetDlgItem(IDC_COMBO_STOPBIT);
	ASSERT(pComboStopBit);
	pComboStopBit->SetItemData(pComboStopBit->AddString(_T("1")), ONE5STOPBITS);
	pComboStopBit->SetItemData(pComboStopBit->AddString(_T("2")), TWOSTOPBITS);
	pComboStopBit->SetCurSel(0);
}

void CSerialcommunicationDlg::OnBnClickedBtnCommcontrol()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	static BOOL bIsOpen = FALSE;
	CButton* pBtnCommControl = (CButton*)GetDlgItem(IDC_BTN_COMMCONTROL); //��ȡ��ť�Ķ���
	ASSERT(pBtnCommControl);

	CComboBox *pComboBoxComm = (CComboBox*)GetDlgItem(IDC_COMBO_COMM);
	ASSERT(pComboBoxComm);

	int nSel = pComboBoxComm->GetCurSel();
	CString strComm;
	pComboBoxComm->GetLBText(nSel, strComm);//��ȡѡ�е�����

	CComboBox *pComboBoxBaudrate = (CComboBox*)GetDlgItem(IDC_COMBO_BAUDRATE);
	ASSERT(pComboBoxBaudrate);
	nSel = pComboBoxBaudrate->GetCurSel();
	DWORD dwBaudrate = (DWORD)pComboBoxBaudrate->GetItemData(nSel);

	CComboBox *pComboBoxCheckbit = (CComboBox*)GetDlgItem(IDC_COMBO_CHECKBIT);
	ASSERT(pComboBoxCheckbit);
	nSel = pComboBoxCheckbit->GetCurSel();
	BYTE byParity = (BYTE)pComboBoxCheckbit->GetItemData(nSel);

	CComboBox *pComboBoxDatabit = (CComboBox*)GetDlgItem(IDC_COMBO_DATABIT);
	ASSERT(pComboBoxDatabit);
	nSel = pComboBoxDatabit->GetCurSel();
	BYTE byDataSize = (BYTE)pComboBoxDatabit->GetItemData(nSel);

	CComboBox *pComboBoxStopbit = (CComboBox*)GetDlgItem(IDC_COMBO_STOPBIT);
	ASSERT(pComboBoxStopbit);
	nSel = pComboBoxStopbit->GetCurSel();
	BYTE byStopBits = (BYTE)pComboBoxStopbit->GetItemData(nSel);

	if (!bIsOpen)
	{
		
		bIsOpen = gSerialPort.OpenCommm(strComm); //�򿪴���
		if (bIsOpen)
		{
			
			BOOL bRet = gSerialPort.SetCommStata(dwBaudrate, byParity, byDataSize, byStopBits); //���ô�������
			if (!bRet)
			{
				gSerialPort.CloseComm();
				AfxMessageBox(_T("���ô�������ʧ�ܣ�"));
				return;
			}

			bRet = gSerialPort.SetupComm(1024, 1024);  //������������������Ĵ�С
			if (!bRet)
			{
				gSerialPort.CloseComm();
				AfxMessageBox(_T("���ô����������������ʧ�ܣ�"));
				return;
			}
			bRet = gSerialPort.PurgeComm(PURGE_RXABORT | PURGE_RXCLEAR | PURGE_TXABORT | PURGE_TXCLEAR);  //
			if (!bRet)
			{
				gSerialPort.CloseComm();
				AfxMessageBox(_T("�޷�������ڵĴ���״̬��"));
				return;
			}

			bRet=gSerialPort.SetCommMask(EV_RXCHAR);
			if (!bRet)
			{
				gSerialPort.CloseComm();
				AfxMessageBox(_T("���ô����¼�����"));
				return;
			}
			gSerialPort.StartComm();  //��ʼ����ͨ�ţ����̣߳�

			bIsOpen = TRUE;
			pBtnCommControl->SetWindowText(_T("�رմ���"));
		}
		else
		{
			pBtnCommControl->SetWindowText(_T("�򿪴���"));
		}

	}
	else   //ԭ��״̬�Ѿ��򿪺��ڵ����ť���͹رմ���
	{
		gSerialPort.CloseComm();
		bIsOpen = FALSE;
		pBtnCommControl->SetWindowText(_T("�򿪴���"));
	}
}


void CSerialcommunicationDlg::OnBnClickedBtnSend()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

}
