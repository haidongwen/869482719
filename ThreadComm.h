#pragma once
#include "Thread.h"
class CThreadComm :public CThread   //����һ��������CThreadComm
{
public:
	CThreadComm();
	~CThreadComm();

public:
	virtual void run();
};

