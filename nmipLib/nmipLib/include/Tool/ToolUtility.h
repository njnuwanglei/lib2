#pragma once
#include "stdafx.h"
#include "..\nmipExport.h"

class NMIP_DLL_API CToolUtility
{
public:
	CToolUtility();
	~CToolUtility();

	static CString GetAppPath();
	// ��֧��UC8��RGB24
	static void ConvertImagePtrToHObject(unsigned char* ucpImageData, int iWidth, int iHeight,
		int iChannel, HObject& hoImage);


private:

};
