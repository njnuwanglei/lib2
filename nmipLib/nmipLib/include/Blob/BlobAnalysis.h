#pragma once

#include "..\nmipExport.h"
#include <vector>



struct BLOB_INFO_T
{
	RECT rcPos;
	int iArea;
	double dEnergy;
};

struct BLOB_PARAM_T
{
	// 残点最小参数
	int iMinArea;
	double dMinEnergy;
	int iMergeDis;

	// 单点残点
	int iDotDefArea;
	double dDotDefEnergy;

	// 区域残点
	int iDotsCount;
	int iRegionDefArea;
	double dRegionDefEnergy;
};

struct BLOB_RESULT_T
{
	vector<BLOB_INFO_T> vecBlobDef;
	vector<BLOB_INFO_T> vecBlobDot;

	// 区域残点数量
	int iDotsCount;
	// 区域残点面积
	int iRegionDefArea;
	// 区域残点能量
	double dRegionDefEnergy;
};
class NMIP_DLL_API CBlobAnalysis /*:
	public IAlgorithmObject*/
{
public:
	CBlobAnalysis(void);
	~CBlobAnalysis(void);

	int Execute(HObject hoRegion,HObject hoImage);

	BLOB_RESULT_T& GetResult();
	void SetParam(BLOB_PARAM_T tParam);
	BLOB_PARAM_T& GetParam();

	BOOL SaveFile(char* szFilePath);
	BOOL LoadFile(char* szFilePath);
private:
	BLOB_PARAM_T m_tParam;
	BLOB_RESULT_T m_tResult;
};



