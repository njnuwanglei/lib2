/*!
 * \file FindCoin.h
 * \date 2018/07/13 13:33
 *
 * \author WangLei
 * Contact: wanglei@njzb.cbpm.cn
 *
 * \brief 
 * �ڸ��ӱ����в���Բ�λ���Ӳ������λ��
 * TODO: long description
 *
 * \note
*/
#pragma once
#include "..\nmipExport.h"


struct FINDCOIN_RESULT_T
{
	// Ӳ����������λ��
	POINTF ptCenter;
	// Ӳ��ʵ�ʰ뾶
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
	// ����Ӳ�ұ�׼�뾶
	void SetCoinRadius(int iRadius);
	// ���ñ߲���ǿϵ�� Ĭ�ϲ���ֵΪ�㣬Ϊ��ʱ��ʾ���ñ�Ե��ǿ����
	// ͬ���Դͼ���Ƽ���Ϊ1-2
	void SetEnhanceCoeff(double dCoeff);
	// hoImage:����λ�Ҷ�ͼ��
	int Execute(HObject hoImage);
	FINDCOIN_RESULT_T& GetResult();

private:
	HTuple m_hvModelID;
	FINDCOIN_RESULT_T m_tResult;
	FINDCOIN_PARAM_T m_tParam;
};

