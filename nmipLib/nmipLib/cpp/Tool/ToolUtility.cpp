#include "stdafx.h"
#include "..\..\include/Tool/ToolUtility.h"


CToolUtility::CToolUtility(void)
{
}


CToolUtility::~CToolUtility(void)
{
}


CString CToolUtility::GetAppPath()
{
	TCHAR tszBuf[MAX_PATH] = {'\0'};
	GetModuleFileName( NULL, tszBuf, MAX_PATH);
	CString strDir, tmpDir;
	tmpDir = tszBuf;
	strDir = tmpDir.Left( tmpDir.ReverseFind('\\') );
	return strDir;
}


void CToolUtility::ConvertImagePtrToHObject(unsigned char* ucpImageData, int iWidth, int iHeight,
							  int iChannel, HObject& hoImage)
{
	if (iChannel == 1)
	{
		GenImage1(&hoImage,"byte",iWidth,iHeight,(Hlong)ucpImageData);
	}
	else if (iChannel == 3)
	{
		GenImageInterleaved(&hoImage,(Hlong)ucpImageData,"bgr",iWidth,iHeight,-1,"byte",iWidth,iHeight,0,0,-1,0);
	}
}

void CToolUtility::ConvertHObjectToImagePtr(HObject hoImage, unsigned char* ucpImageData,
										 int& iWidth, int& iHeight)
{
	HTuple width,height,hvType;
	HTuple hv_Ptr;
	GetImagePointer1(hoImage,&hv_Ptr,&hvType,&width,&height);
	iWidth = width[0].I();
	iHeight = height[0].I();

	ucpImageData = (unsigned char*)hv_Ptr[0].L();
}
