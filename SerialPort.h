#pragma once
#include "ThreadComm.h"
class CSerialPort
{
public:
	CSerialPort();
	~CSerialPort();
public:
	BOOL OpenCommm(CString strComm); //�򿪴��� ,���ھ���һ���ļ�
	BOOL SetCommStata(DWORD dwBaudtate,BYTE byParity,BYTE byByteSize,BYTE byStopBits); //���ô��ڵĲ���
	BOOL SetupComm(DWORD dwInqueue, DWORD dwOutqueue);//������������������Ĵ�С
	BOOL PurgeComm(DWORD dwFlags);//���������
	BOOL SetCommMask(DWORD dwEvtMask); //���ô��ڵ��¼�����
	BOOL WriteFile(IN LPVOID lpBuffer, IN DWORD nNumberOfBytesToRead, OUT LPDWORD lpNumberOfBytesRead, IN LPOVERLAPPED lpOverlapped);
	BOOL ReadFile(OUT LPVOID lpBuffer, IN DWORD nNumberOfBytesToRead, OUT LPDWORD lpNumberOfBytesRead, IN LPOVERLAPPED lpOverlapped);
	BOOL ClearCommError(OUT LPDWORD lpErrors, OUT LPCOMSTAT lpStat); //��д��֮�󣬰Ѵ���ı�־�������
	BOOL GetOverlappedResult(IN LPOVERLAPPED lpOverlapped,OUT LPDWORD lpNumberOfBytesTransferred,IN BOOL bWait);  //�ж�������û���շ����
	void CloseComm();
	void StartComm();


public:
	HANDLE m_hComm;
	CThreadComm m_threadComm;  //�������ݵ��̵߳Ķ�����Ϊ�˴��ڶ����һ����Ա����
};

