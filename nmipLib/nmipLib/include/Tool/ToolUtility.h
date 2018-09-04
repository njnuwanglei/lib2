#pragma once
#include "stdafx.h"
#include "..\nmipExport.h"

class NMIP_DLL_API CToolUtility
{
public:
	CToolUtility();
	~CToolUtility();

	static CString GetAppPath();
	// 仅支持UC8和RGB24
	static void ConvertImagePtrToHObject(unsigned char* ucpImageData, int iWidth, int iHeight,
		int iChannel, HObject& hoImage);

	// 仅支持UC8 ucpImageData 不做内存管理
	static void ConvertHObjectToImagePtr(HObject hoImage, unsigned char* ucpImageData, 
		int& iWidth, int& iHeight);

private:

};
