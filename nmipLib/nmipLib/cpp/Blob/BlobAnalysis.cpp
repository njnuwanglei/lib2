

//#include "..\..\stdafx.h"
#include "stdafx.h"
#include "..\..\include\Blob\BlobAnalysis.h"

#define MAX_BLOB_AREA   10000000
#define MAX_BLOB_ENERGY 10000000

CBlobAnalysis::CBlobAnalysis(void)
{
	BLOB_PARAM_T& tParam = GetParam();
	tParam.iMinArea = 2;
	tParam.dMinEnergy = 0.3;
	tParam.iMergeDis = 5;

	tParam.iDotDefArea = 50;
	tParam.dDotDefEnergy = 3.0;

	tParam.iDotsCount = 10;
	tParam.iRegionDefArea = 1000;
	tParam.dRegionDefEnergy = 20.0;
}


CBlobAnalysis::~CBlobAnalysis(void)
{
}


int CBlobAnalysis::Execute(HObject hoRegion,HObject hoImage)
{
	BLOB_PARAM_T& tParam = GetParam();
	BLOB_RESULT_T& tResult = GetResult();
	// Init
	int iRet = 0;
	tResult.vecBlobDef.clear();
	tResult.vecBlobDot.clear();
	tResult.iDotsCount = 0;
	tResult.iRegionDefArea = 0;
	tResult.dRegionDefEnergy = 0;


	HObject hoConnection;
	Connection(hoRegion,&hoConnection);
	
	HTuple hvEnergy,hvArea,hvRow,hvCol;
	// 统计区域缺陷
	HObject hoSelectTemp,hoMinDef;
	SelectShape(hoConnection,&hoSelectTemp,"area","and",tParam.iMinArea,MAX_BLOB_AREA);
	SelectGray(hoSelectTemp,hoImage,&hoMinDef,"area","and",tParam.dMinEnergy,MAX_BLOB_ENERGY);
	AreaCenterGray(hoMinDef,hoImage,&hvEnergy,&hvRow,&hvCol);
	AreaCenter(hoMinDef,&hvArea,&hvRow,&hvCol);
	HTuple hvRow1,hvCol1,hvRow2,hvCol2;
	SmallestRectangle1(hoMinDef,&hvRow1,&hvCol1,&hvRow2,&hvCol2);

	HTuple hvAreaSum,hvEnergySum;
	TupleSum(hvArea,&hvAreaSum);
	TupleSum(hvEnergy,&hvEnergySum);
	tResult.iDotsCount = hvArea.TupleLength();
	if (tResult.iDotsCount > 0)
	{
		tResult.iRegionDefArea = hvAreaSum[0];
		tResult.dRegionDefEnergy = hvEnergySum[0];

		BLOB_INFO_T tBlob;
		for (int i=0; i<tResult.iDotsCount; i++)
		{
			tBlob.iArea = hvArea[i];
			tBlob.dEnergy = hvEnergy[i];
			tBlob.rcPos.top = hvRow1[i].I();
			tBlob.rcPos.left = hvCol1[i].I();
			tBlob.rcPos.bottom = hvRow2[i].I();
			tBlob.rcPos.right = hvCol2[i].I();
			tResult.vecBlobDot.push_back(tBlob);
		}


	}
	// 统计单点缺陷
	HObject hoUnion;
	Union1(hoMinDef,&hoUnion);
	HObject hoMerge;
	ClosingCircle(hoUnion,&hoMerge,tParam.iMergeDis);
	HObject hoDotDef;
	Connection(hoMerge,&hoConnection);
	SelectShape(hoConnection,&hoSelectTemp,"area","and",tParam.iDotDefArea,MAX_BLOB_AREA);
	SelectGray(hoSelectTemp,hoImage,&hoDotDef,"area","and",tParam.dDotDefEnergy,MAX_BLOB_ENERGY);

	AreaCenterGray(hoDotDef,hoImage,&hvEnergy,&hvRow,&hvCol);
	AreaCenter(hoDotDef,&hvArea,&hvRow,&hvCol);
	SmallestRectangle1(hoDotDef,&hvRow1,&hvCol1,&hvRow2,&hvCol2);

	

	int iDefCount = hvArea.TupleLength();
	if (iDefCount > 0)
	{
		BLOB_INFO_T tBlob;
		for (int i=0; i<iDefCount; i++)
		{
			tBlob.iArea = hvArea[i];
			tBlob.dEnergy = hvEnergy[i];
			tBlob.rcPos.top = hvRow1[i].I();
			tBlob.rcPos.left = hvCol1[i].I();
			tBlob.rcPos.bottom = hvRow2[i].I();
			tBlob.rcPos.right = hvCol2[i].I();

			tResult.vecBlobDef.push_back(tBlob);
		}
	}

	if (iDefCount > 0)
	{
		iRet = 1;
	}
	else if(tResult.iDotsCount >= tParam.iDotsCount &&
		tResult.iRegionDefArea >= tParam.iRegionDefArea &&
		tResult.dRegionDefEnergy >= tParam.dRegionDefEnergy)
	{
		iRet = 2;
	}
	return iRet;
}

BLOB_RESULT_T& CBlobAnalysis::GetResult()
{
	return m_tResult;
}
void CBlobAnalysis::SetParam(BLOB_PARAM_T tParam)
{
	m_tParam = tParam;
}
BLOB_PARAM_T& CBlobAnalysis::GetParam()
{
	return m_tParam;
}

#include<iostream>
#include <fstream>
BOOL CBlobAnalysis::SaveFile(char* szFilePath)
{
	ofstream os(szFilePath, ios_base::out | ios_base::binary);
	os.write(reinterpret_cast<char *>( &m_tParam), sizeof(m_tParam));
	os.close();
	return TRUE;
}
BOOL CBlobAnalysis::LoadFile(char* szFilePath)
{
	ifstream is(szFilePath, ios_base::out | ios_base::binary);
	is.read(reinterpret_cast<char *>( &m_tParam), sizeof(m_tParam));
	is.close();
	return TRUE;
}