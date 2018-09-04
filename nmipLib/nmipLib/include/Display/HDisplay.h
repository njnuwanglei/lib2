#pragma once
#include "..\nmipExport.h"

#include "afxwin.h"
#include "HOverlay.h"
#include "HRoiObject.h"
struct POINT_D
{
	double x;
	double y;
};
class NMIP_DLL_API CHDisplay :
	public CStatic
{
public:
	CHDisplay(void);
	~CHDisplay(void);

	void SetImage(HObject* pHImage);
	void Redraw();
	//
	void FitSize(BOOL bFitWidth = TRUE, BOOL bFitHeight = TRUE);
	BOOL WindowPointToImagePoint (int iWindowX, int iWindowY, double &dImageX, double &dImageY);  
    BOOL ImagePointToWindowPoint (double dImageX, double dImageY, int &iWindowX, int &iWindowY);  

	CHOverlay* CreateOverlay();

	void AddRoi(CHRoiObject* pHRoi);
	void DeleteRoi(int iIndex);
	void DeleteRoi(CHRoiObject* pHRoi);
	void DeleteAllRoi();
	CHRoiObject* GetRoi(int iIndex);
	int GetRoiCount();
	void SetRoiVisible(CHRoiObject* pHRoi, BOOL bVisible = TRUE);
private:
	HImage* m_pHImage;
	HWindow m_hDspWnd;
	double m_dMagnification;
	POINT_D m_ptOffset;
	POINT m_ptDragOrig;
	POINT m_ptMousePos;
	BOOL m_bDragImageEnable;

	vector<CHOverlay*> m_vecOverlay;
	vector<CHRoiObject*> m_vecRoi;

	void CalcDispPart(int iCenterX, int iCenterY, double dMagnification, HTuple& hvPart);
public:
	virtual void PreSubclassWindow();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnDestroy();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

