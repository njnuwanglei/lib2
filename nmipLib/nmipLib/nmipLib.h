// nmipLib.h : nmipLib DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CnmipLibApp
// �йش���ʵ�ֵ���Ϣ������� nmipLib.cpp
//

class CnmipLibApp : public CWinApp
{
public:
	CnmipLibApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
