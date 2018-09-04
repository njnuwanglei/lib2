#include "stdafx.h"
#include "..\..\include\Coin\FindCoin.h"

CFindCoin::CFindCoin(void)
{
	m_hvModelID = NULL;
	m_tParam.iCoinRadius = 100;
	m_tParam.dEnhanceCoeff = 0;
	SetCoinRadius(m_tParam.iCoinRadius);
}

CFindCoin::~CFindCoin(void)
{
	if (m_hvModelID != NULL)
	{
		ClearShapeModel(m_hvModelID);
	}
}

int CFindCoin::Execute(HObject hoImage)
{

	HTuple hvImageWidth, hvImageHeight;
	GetImageSize(hoImage, &hvImageWidth, &hvImageHeight);
	
	HObject hoEnhancedImage;
	if (m_tParam.dEnhanceCoeff != 0)
	{
		MultImage(hoImage, hoImage, &hoEnhancedImage, m_tParam.dEnhanceCoeff, 0);
	}
	else
	{
		hoEnhancedImage = hoImage;
	}
	HTuple hvRow, hvColumn, hvScale, hvScore, hvAngle;
	FindScaledShapeModel(hoEnhancedImage, m_hvModelID, 0, 0, 0.90, 1.1, 0.3, 1, 0.5, "least_squares", 4, 0.9, &hvRow, &hvColumn, &hvAngle, &hvScale, &hvScore);
	if (hvRow.TupleLength() > 0)
	{
		m_tResult.ptCenter.x = hvColumn[0].D();
		m_tResult.ptCenter.y = hvRow[0].D();
		m_tResult.iRadius = m_tParam.iCoinRadius*hvScale[0].D();
	}
	else
	{
		return -1;
	}
	return 0;
}


void CFindCoin::SetCoinRadius(int iRadius)
{
	m_tParam.iCoinRadius = iRadius;
	HObject hoCircle;
	GenCircleContourXld(&hoCircle, 0, 0, iRadius, 0, 6.28318, "positive", 1);
	if (m_hvModelID != NULL)
	{
		ClearShapeModel(m_hvModelID);
	}
	CreateScaledShapeModelXld(hoCircle, "auto", 0, 0, "auto", 0.90, 1.1, "auto", "auto", "ignore_local_polarity", 15, &m_hvModelID);
}

void CFindCoin::SetEnhanceCoeff(double dCoeff)
{
	m_tParam.dEnhanceCoeff = dCoeff;
}


FINDCOIN_RESULT_T& CFindCoin::GetResult()
{
	return m_tResult;
}
