
// MeasurePro.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMeasureProApp:
// �йش����ʵ�֣������ MeasurePro.cpp
//

class CMeasureProApp : public CWinApp
{
public:
	CMeasureProApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMeasureProApp theApp;