
// Serialcommunication.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "SerialPort.h"

// CSerialcommunicationApp: 
// �йش����ʵ�֣������ Serialcommunication.cpp
//

class CSerialcommunicationApp : public CWinApp
{
public:
	CSerialcommunicationApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSerialcommunicationApp theApp;
extern CSerialPort gSerialPort; //����һ��ȫ�ֵĴ��ڶ���