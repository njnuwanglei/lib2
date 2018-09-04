#include "stdafx.h"
#include "..\..\Include\Display\HOverlay.h"


CHOverlay::CHOverlay(void)
{
}


CHOverlay::~CHOverlay(void)
{
	ClearOverlay();
}


void CHOverlay::DrawRegion(HRegion hReg, COLORREF clr)
{
// 	HDisplayObject_T hDspObj;
// 	hDspObj.reg = hReg;
// 	hDspObj.clr = clr;
// 	hDspObj.mode = 0;
// 	m_vecDispObj.push_back(hDspObj);

	bool newReg = true;

	for(int i=0; i<m_vecDispObj.size(); i++)
	{

		if(m_vecDispObj[i].clr == clr)
		{
			ConcatObj(m_vecDispObj[i].reg,hReg,&m_vecDispObj[i].reg);
			newReg = false;
			break;
		}
	}
	if (newReg)
	{
		HDisplayObject_T hDspObj;
		hDspObj.reg = hReg;

		hDspObj.clr = clr;
		hDspObj.mode = 0;
		m_vecDispObj.push_back(hDspObj);
	}
}



void CHOverlay::ClearOverlay()
{
	m_vecDispObj.clear();
}

HDisplayObject_T* CHOverlay::GetDisplayObject (int i)
{
	return &m_vecDispObj[i];
}
int CHOverlay::GetDisplayObjectCount ()
{
	return m_vecDispObj.size();
}