#pragma once

class CThread
{
public:
	CThread();
	~CThread();
public:
	void Start();
	void Stop();

public:
	virtual void SetThreadData(DWORD dwParam); //�����߳��е�����
	virtual DWORD GetThreadData();            //��ȡ�����߳��еĴ���ָ��
	virtual void run();
public:
	static DWORD ThreadProc(LPVOID pParam);  //�̵߳Ļص�����

public:
	HANDLE m_hThread;
	bool m_bExit; //�߳��Ƿ��˳��ı�־λ
	DWORD m_dwParam;
};

