#include "stdafx.h"
#include "ThreadComm.h"
#include "SerialcommunicationDlg.h"
#include "SerialPort.h"
#include "resource.h"	
#include <string>
using namespace std;
CThreadComm::CThreadComm()
{
}


CThreadComm::~CThreadComm()
{
}
bool falg = false;

void CThreadComm::run()
{
	Sleep(100);
	CSerialcommunicationDlg* pSerialcommunicationDlg = (CSerialcommunicationDlg*)AfxGetApp()->m_pMainWnd;   //��ȡ�Ի���Ķ���
	if (NULL == pSerialcommunicationDlg)    //�⼸�в�ע�ͻ���ʾIDD_SERIALCOMMUNICATION_DIALOGδʶ��Ĵ���
	{
		return;
	}

	CSerialPort *pSerialPort = (CSerialPort*)GetThreadData();
	if (NULL == pSerialPort) return;  //�ж�ָ���Ƿ����

	//�жϴ��ڴ������û�����ݣ�ֻҪ�����ݽ��������ڵĻ�������ͻ�����һ������ı�־λ���������жϴ����־λ�����뻺����������û������
	DWORD dwError = 0;
	COMSTAT comStat; //�����մ����״̬
	BOOL bRet = TRUE;
	//TCHAR recvTemp[512]; //������ջ��������ݵ���ʱ����
	char recvTemp[512];
	ZeroMemory(recvTemp, sizeof(recvTemp));

	char recvBuf[4096]; //������ջ��������ݵ�ʵ�ʱ���
	//TCHAR recvBuf[4096]; //������ջ��������ݵ�ʵ�ʱ���
	ZeroMemory(recvBuf, sizeof(recvBuf));

	DWORD dwRead = 0;
	int nLength = 0;
	

	pSerialPort->ClearCommError(&dwError, &comStat);
	if (comStat.cbInQue > 0)  //�жϴ���״̬�е����뻺������cbInQue���Ƿ����0,����0˵�������ݹ����ˣ��������Ϳ�������������
	{
		OVERLAPPED overlappedRead;
		ZeroMemory(&overlappedRead, sizeof(overlappedRead));//�Ȱ�overlappedRead����������
		overlappedRead.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);   //�ڶ�������TRUE��ʾ�¼����Զ�����������������FALSE��ʾԭ�ȵ�״̬�����ź�״̬���������ź�״̬��FALSE��ʾ���ź�״̬
			                        //������źŹ���ʱ������¼��ͻᱻ����
		
		/*OVERLAPPED m_osRead;
		memset(&m_osRead, 0, sizeof(OVERLAPPED));
		m_osRead.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
		dwRead = min(dwRead, (DWORD)comStat.cbInQue);*/

		if (comStat.cbInQue < 512)
		{
			bRet = pSerialPort->ReadFile(recvTemp, comStat.cbInQue, &dwRead, &overlappedRead); //dwRead��ʾʵ�ʶ��˶��ٸ�
		}
		else
		{
			bRet = pSerialPort->ReadFile(recvTemp, 500, &dwRead, &overlappedRead);  //ÿ�ζ�500���ֽ�
		}

		if (comStat.cbInQue >= dwRead)  //�жϻ���������ֵ�Ƿ���ڵ��ڶ�ȡ����ֵ�����ж��Ƿ����
		{
			memcpy(recvBuf + nLength, recvTemp, dwRead);
			nLength += dwRead;
		}

		if (comStat.cbInQue == dwRead)  //�ж��Ƿ���꣬����֮�����ʾ����
		{
			nLength = 0;
			CEdit* pEditRecv = (CEdit*)pSerialcommunicationDlg->GetDlgItem(IDC_EDIT_RECV);
			if (pEditRecv)
			{
				CString strRecv;
				pEditRecv->GetWindowText(strRecv);
				strRecv += recvBuf;
				strRecv += "\r\n";
				pEditRecv->SetWindowText(strRecv);
			}
			string DirectStr;
			string subDirectStr;
			DirectStr = recvTemp;
			subDirectStr=DirectStr.substr(0, DirectStr.find(DirectStr[0], 3));
			
		
			if (subDirectStr == "RZminus")
			{
				//pSerialcommunicationDlg->InitComboBox(); //���·�3���ַ����ɿ��������ַ���
				falg = true;
			}


		}		


		if (!bRet)  //�ж��Ƿ��ص���bRet����FALSE˵������û������
		{
			if (ERROR_IO_PENDING == GetLastError())  //�ж������Ƿ񱻹��𣬹������������
			{
				while (!bRet)
				{
					bRet = pSerialPort->GetOverlappedResult(NULL, &dwRead, TRUE);
					if (GetLastError() != ERROR_IO_INCOMPLETE)    //�ж��Ƿ���������û�������������
					{
						pSerialPort->ClearCommError(&dwError, &comStat);  //���������������
						break;
					}
				}
			}
		}
	}
	Sleep(50);  //��ʱ50ms�������ݴ��뻺����
	if ((comStat.cbInQue == 0) && falg)
	{
		pSerialcommunicationDlg->InitComboBox();
		falg = false;
	}
		
}