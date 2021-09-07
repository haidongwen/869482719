#include "stdafx.h"
#include "SerialPort.h"


CSerialPort::CSerialPort()
{
	m_hComm = NULL;
}


CSerialPort::~CSerialPort()
{
	CloseComm();
}


void CSerialPort::StartComm()
{
	m_threadComm.SetThreadData((DWORD)this); //�Ѵ���ָ������뵽�߳���
	m_threadComm.Start();  //

}

BOOL CSerialPort::OpenCommm(CString strComm)
{
	if (NULL == m_hComm)
	{
		//USES_CONVERSION;
		//LPCWSTR wszClassName = A2CW(W2A(strComm));

		m_hComm = CreateFile((TCHAR*)(LPCTSTR)strComm,//COM1��
			GENERIC_READ | GENERIC_WRITE, //�������д
			0, //��ռ��ʽ
			NULL,
			OPEN_EXISTING, //�򿪶����Ǵ���
			FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, //�ص���ʽ
			NULL);

		if (INVALID_HANDLE_VALUE == m_hComm)
		{
			int nError = GetLastError(); //���ش�������
			return FALSE;
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CSerialPort::SetCommStata(DWORD dwBaudtate, BYTE byParity, BYTE byByteSize, BYTE byStopBits)
{
	if (NULL == m_hComm) return FALSE;
	DCB dcb;
	BOOL bRet = ::GetCommState(m_hComm, &dcb);
	if (!bRet)
	{
		if (m_hComm)
		{
			CloseHandle(m_hComm);
			m_hComm = NULL;
		}
		return FALSE;
	}
	dcb.BaudRate = dwBaudtate;
	dcb.ByteSize = byByteSize;
	dcb.Parity = byParity;
	dcb.StopBits = byStopBits;
	bRet = ::SetCommState(m_hComm, &dcb);  //::SetCommState(m_hComm, &dcb)����ǰ�����;;��ʾ���ñ�׼��SetCommState������������������д�����SetCommState����
	if (!bRet)
	{
		if (m_hComm)
		{
			CloseHandle(m_hComm);
			m_hComm = NULL;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSerialPort::SetupComm(DWORD dwInqueue, DWORD dwOutqueue)
{
	if (NULL == m_hComm) return FALSE;

	return ::SetupComm(m_hComm, dwInqueue, dwOutqueue);
}

BOOL CSerialPort::PurgeComm(DWORD dwFlags)
{
	if (NULL == m_hComm) return FALSE;
	return ::PurgeComm(m_hComm, dwFlags);
}

BOOL CSerialPort::SetCommMask(DWORD dwEvtMask)
{
	if (NULL == m_hComm) return FALSE;
	return ::SetCommMask(m_hComm, dwEvtMask);
}

BOOL CSerialPort::WriteFile(IN LPVOID lpBuffer, IN DWORD nNumberOfBytesToRead, OUT LPDWORD lpNumberOfBytesRead, IN LPOVERLAPPED lpOverlapped)
{
	if (NULL == m_hComm) return FALSE;
	return ::WriteFile(m_hComm, lpBuffer, nNumberOfBytesToRead, lpNumberOfBytesRead, lpOverlapped);
}


BOOL CSerialPort::ReadFile(OUT LPVOID lpBuffer, IN DWORD nNumberOfBytesToRead, OUT LPDWORD lpNumberOfBytesRead, IN LPOVERLAPPED lpOverlapped)
{
	if (NULL == m_hComm) return FALSE;
	return ::ReadFile(m_hComm, lpBuffer, nNumberOfBytesToRead, lpNumberOfBytesRead, lpOverlapped);
}
BOOL CSerialPort::ClearCommError(OUT LPDWORD lpErrors, OUT LPCOMSTAT lpStat)
{
	if (NULL == m_hComm) return FALSE;
	return ::ClearCommError(m_hComm, lpErrors, lpStat);
}
BOOL CSerialPort::GetOverlappedResult(IN LPOVERLAPPED lpOverlapped, OUT LPDWORD lpNumberOfBytesTransferred, IN BOOL bWait)
{
	if (NULL == m_hComm) return FALSE;
	return ::GetOverlappedResult(m_hComm, lpOverlapped, lpNumberOfBytesTransferred, bWait);
}
void CSerialPort::CloseComm()
{
	m_threadComm.Stop();//�ر��߳�
	if (m_hComm)
	{
		CloseHandle(m_hComm); //�رմ��ھ��
		m_hComm = NULL;
	}

}