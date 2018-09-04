#pragma once

#ifdef NMIP_DLL_EXPORTS
#define NMIP_DLL_API __declspec(dllexport)
#else
#define NMIP_DLL_API __declspec(dllimport)
#endif

#include "halconcpp.h"
using namespace HalconCpp;
using namespace std;