#pragma once

#ifdef BASE_CAMERA_LIB
#define BASE_CAMERA_API __declspec(dllexport)
#else
#define BASE_CAMERA_API __declspec(dllimport)
#endif