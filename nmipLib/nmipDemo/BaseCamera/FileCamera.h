#pragma once
#include "basecamera.h"
#include "baseexports.h"
class CDialogImageList;
class BASE_CAMERA_API CFileCamera :
	public CBaseCamera
{
public:
	CFileCamera(void);
	~CFileCamera(void);

	bool Open();
	bool Close();
	bool StartCapture();
	void SetCallbackFn(ImageDataCallback CallbackFn,const void* pCallbackData  = 0 );
	bool StopCapture();
	void ShowCameraView();
private:
	int m_iStartIndex;
	int m_iMode;
	bool m_bCapture;

	CDialogImageList* m_pImgListView;
};
