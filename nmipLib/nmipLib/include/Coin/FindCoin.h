/*!
 * \file FindCoin.h
 * \date 2018/07/13 13:33
 *
 * \author WangLei
 * Contact: wanglei@njzb.cbpm.cn
 *
 * \brief 
 * 在复杂背景中查找圆形或环形硬币所在位置
 * TODO: long description
 *
 * \note
*/
#pragma once
#include "..\nmipExport.h"


struct FINDCOIN_RESULT_T
{
	// 硬币所在中心位置
	POINTF ptCenter;
	// 硬币实际半径
	int iRadius;
};

struct FINDCOIN_PARAM_T
{
	int iCoinRadius;
	double dEnhanceCoeff;
};

class NMIP_DLL_API CFindCoin
{
public:
	CFindCoin(void);
	~CFindCoin(void);
	// 设置硬币标准半径
	void SetCoinRadius(int iRadius);
	// 设置边部增强系数 默认参数值为零，为零时表示不用边缘增强功能
	// 同轴光源图像推荐设为1-2
	void SetEnhanceCoeff(double dCoeff);
	// hoImage:待定位灰度图像
	int Execute(HObject hoImage);
	FINDCOIN_RESULT_T& GetResult();

private:
	HTuple m_hvModelID;
	FINDCOIN_RESULT_T m_tResult;
	FINDCOIN_PARAM_T m_tParam;
};

