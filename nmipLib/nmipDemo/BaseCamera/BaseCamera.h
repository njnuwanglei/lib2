#pragma once
//#include "baseexports.h"
//#include "BaseImage.h"
// #define CAMERA_TYPE_EURESYS
// #ifdef CAMERA_TYPE_POINTGREY
// 	typedef void (*ImageDataCallback)(void* pImage, const void* pCallbackData );
// #endif
// #ifdef CAMERA_TYPE_EURESYS
// 	typedef void (*ImageDataCallback)(void* pImage, const void* pCallbackData);
// #endif
typedef void (*ImageDataCallback)(void* pImage, const void* pCallbackData);
typedef void (*ImageDataCallbackEx)(void* pImage);
class CBaseCamera
{
public:


public:
	CBaseCamera(void){};
	virtual ~CBaseCamera(void){};

	virtual bool Open() = 0;
	virtual bool Close() = 0;
	virtual bool StartCapture() = 0;
	virtual bool StopCapture() = 0;
	
};

