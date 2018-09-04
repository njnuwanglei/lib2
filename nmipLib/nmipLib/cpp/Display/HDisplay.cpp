#include "stdafx.h"
#include "..\..\Include\Display\HDisplay.h"


CHDisplay::CHDisplay(void)
	:CStatic()
{
	m_bDragImageEnable = FALSE;
}


CHDisplay::~CHDisplay(void)
{
	for (int i=0; i<m_vecOverlay.size(); i++)
	{
		CHOverlay* pHOverlay = m_vecOverlay[i];
		delete pHOverlay;
		pHOverlay = NULL;
	}
}

void CHDisplay::SetImage(HObject* pHImage)
{
	m_pHImage = (HImage*)pHImage;
	
	m_hDspWnd.AttachBackgroundToWindow(*m_pHImage);

}

void CHDisplay::Redraw()
{

	HTuple hvPart;
	CalcDispPart(0, 0, m_dMagnification, hvPart);
	//HalconCpp::SetPart(m_hDspWnd,hvPart[0],hvPart[1],hvPart[2],hvPart[3]);
	::SetPart(m_hDspWnd,hvPart[0],hvPart[1],hvPart[2],hvPart[3]);

	m_hDspWnd.ClearWindow();
	m_hDspWnd.SetDraw("margin");
	for (int i=0; i<m_vecOverlay.size(); i++)
	{
		CHOverlay* pHOverlay = m_vecOverlay[i];
		for (int k=0 ;k<pHOverlay->GetDisplayObjectCount(); k++)
		{
			HDisplayObject_T* pObj = pHOverlay->GetDisplayObject(k);

			COLORREF clr = pObj->clr;
			int r = GetRValue(clr);
			int g = GetGValue(clr);
			int b = GetBValue(clr);
			char szClr[32] = "";
			sprintf_s(szClr,"#%02x%02x%02x",r,g,b);
			m_hDspWnd.SetColor(szClr);
			if (pObj->mode == 0)
			{
				//m_hDspWnd.SetDraw("margin");
			}
			else if(pObj->mode == 1)
			{
				m_hDspWnd.SetDraw("fill");
			}
	

			m_hDspWnd.DispRegion(pObj->reg);
 			//m_hDspWnd.DispXld(pObj->xld);
		}
	}

	m_hDspWnd.WriteString("Test");


	//ClearWindow();
// 	DispImage(*m_pHImage);
// // 	
// 	DispArrow(100,100,200,200,3);
}

void CHDisplay::FitSize(BOOL bFitWidth /*= TRUE*/, BOOL bFitHeight /*= TRUE*/)
{

	CRect rcWnd;
	GetWindowRect(&rcWnd);
 	int iWndWidth = rcWnd.Width();
 	int iWndHeight = rcWnd.Height();
	int iImageWidth = m_pHImage->Width();
	int iImageHeight = m_pHImage->Height();
	double dMagX=0,dMagY=0;
	if (bFitWidth)
	{
		dMagX = iWndWidth * 1.0 / iImageWidth;
	}
	if (bFitHeight)
	{
		dMagY = iWndHeight * 1.0 / iImageHeight;
	}
	m_dMagnification = min(dMagX, dMagY);

	if (dMagX <= dMagY)
	{
		m_ptOffset.y =  (iImageHeight * m_dMagnification - iWndHeight) * 0.5;
		m_ptOffset.x = 0;
	}
	else
	{
		m_ptOffset.x = (iImageWidth * m_dMagnification - iWndWidth) * 0.5;
		m_ptOffset.y = 0;
	}

	Redraw();
}

void CHDisplay::CalcDispPart(int iCenterX, int iCenterY, double dMagnification, HTuple& hvPart)
{
	CRect rcWnd;
	GetWindowRect(&rcWnd);
	int iWndWidth = rcWnd.Width();
	int iWndHeight = rcWnd.Height();
	int iImageWidth = m_pHImage->Width();
	int iImageHeight = m_pHImage->Height();

	double ptImageX1,ptImageX2,ptImageY1,ptImageY2;
	WindowPointToImagePoint(0,0,ptImageX1,ptImageY1);
	WindowPointToImagePoint(iWndWidth,iWndHeight,ptImageX2,ptImageY2);

	hvPart[0] = ptImageY1;
	hvPart[1] = ptImageX1;
	hvPart[2] = ptImageY2;
	hvPart[3] = ptImageX2;
}

void CHDisplay::PreSubclassWindow()
{
	HTuple hWnd = (Hlong)this->m_hWnd;
	CRect rcWnd;
	GetWindowRect(&rcWnd);

	//OpenWindow(0,0,rcWnd.Width()-1,rcWnd.Height()-1,hWnd,"visible","",&m_hvDspWnd);
	//m_hDspWnd.SetHandle(hWnd);
	m_hDspWnd.OpenWindow(0,0,rcWnd.Width()-1,rcWnd.Height()-1,hWnd,"visible","");
	CStatic::PreSubclassWindow();
}
BEGIN_MESSAGE_MAP(CHDisplay, CStatic)
	ON_WM_DESTROY()
	ON_WM_MOUSEWHEEL()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


void CHDisplay::OnDestroy()
{
	CStatic::OnDestroy();

	//HalconCpp::CloseWindow(GetHandle());
	m_hDspWnd.CloseWindow();
}

BOOL CHDisplay::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if (nFlags & MK_CONTROL)
	{
		int iImageWidth = m_pHImage->Width();
		int iImageHeight = m_pHImage->Height();
		CRect rcWnd;
		GetWindowRect(&rcWnd);
		int iWndWidth = rcWnd.Width();
		int iWndHeight = rcWnd.Height();
		ScreenToClient(&pt);
		POINT ptCtrlCenter = pt;//{iWndWidth*0.5,iWndHeight*0.5};
		double xImage,yImage;
		WindowPointToImagePoint(ptCtrlCenter.x,ptCtrlCenter.y,xImage,yImage);


		double a = m_dMagnification * 1.04;
		double b = m_dMagnification / 1.04;
		if (zDelta > 0)
		{
			m_dMagnification = a;
// 			m_ptOffset.x += iImageWidth * m_dMagnification * 0.02;
// 			m_ptOffset.y += iImageHeight * m_dMagnification * 0.02;
		}
		else
		{
			m_dMagnification = b;
// 			m_ptOffset.x -= iImageWidth * m_dMagnification * 0.02;
// 			m_ptOffset.y -= iImageHeight * m_dMagnification * 0.02;
		}
		if(m_dMagnification<= 0.1)  
			m_dMagnification = 0.1;  
		if(m_dMagnification>= 10)  
			m_dMagnification = 10;  
		m_ptOffset.x = -(ptCtrlCenter.x - xImage * m_dMagnification);
		m_ptOffset.y = -(ptCtrlCenter.y - yImage * m_dMagnification);

		Redraw();
	}

	return CStatic::OnMouseWheel(nFlags, zDelta, pt);
}


BOOL CHDisplay::WindowPointToImagePoint (int iWindowX, int iWindowY, double &dImageX, double &dImageY)
{
	dImageX = (iWindowX + m_ptOffset.x)  / m_dMagnification;
	dImageY = (iWindowY + m_ptOffset.y)  / m_dMagnification;
	return TRUE;
}
BOOL CHDisplay::ImagePointToWindowPoint (double dImageX, double dImageY, int &iWindowX, int &iWindowY)
{
	iWindowX = dImageX * m_dMagnification - m_ptOffset.x + 0.5;
	iWindowY = dImageY * m_dMagnification - m_ptOffset.y + 0.5;
	return TRUE;
}

void CHDisplay::OnLButtonDown(UINT nFlags, CPoint point)
{
	SetFocus();
	if (nFlags & MK_CONTROL)
	{
		m_ptDragOrig = point;
		m_ptMousePos = point;
		m_bDragImageEnable = TRUE;

		SetCapture();
	}
	CStatic::OnLButtonDown(nFlags, point);
}


void CHDisplay::OnLButtonUp(UINT nFlags, CPoint point)
{

//	if (nFlags & MK_CONTROL)
	{
		if (TRUE == m_bDragImageEnable)
		{
			m_bDragImageEnable = FALSE;
			ReleaseCapture();
		}
	}

	CStatic::OnLButtonUp(nFlags, point);
}


void CHDisplay::OnMouseMove(UINT nFlags, CPoint point)
{
	if (nFlags & MK_CONTROL)
	{	
		if (TRUE == m_bDragImageEnable)
		{
			HCURSOR hCur  =  LoadCursor( NULL  , IDC_HAND ) ;
			::SetCursor(hCur);

			m_ptOffset.x -= point.x - m_ptMousePos.x;
			m_ptOffset.y -= point.y - m_ptMousePos.y;
			m_ptMousePos = point;
			Redraw();


			HTuple hWnd = (Hlong)this->m_hWnd;
			CRect rcWnd;
			GetWindowRect(&rcWnd);
			ClientToScreen(&point);
			if (!rcWnd.PtInRect(point))
			{
				m_bDragImageEnable = FALSE;
				ReleaseCapture();
			}
			else
			{
				SetCapture();
			}
		
		}
	}

	CStatic::OnMouseMove(nFlags,point);
}

CHOverlay* CHDisplay::CreateOverlay()
{
	CHOverlay* pHOverlay = new CHOverlay();
	m_vecOverlay.push_back(pHOverlay);
	return pHOverlay;
}

void CHDisplay::AddRoi(CHRoiObject* pHRoi)
{
	m_vecRoi.push_back(pHRoi);
// 	CString str(typeid(*pHRoi).name());
// 	CString str1(typeid(CHRoiRect).name());
// 	if (0 == strcmp(typeid(*pHRoi).name(), typeid(CHRoiRect).name()))
// 	{
// 		CHRoiRect *pObj = (CHRoiRect*)pHRoi;
// 		HRect_T tRect = pObj->GetData();
// 
// 	}
    SetRoiVisible(pHRoi);
}

void CHDisplay::DeleteRoi(int iIndex)
{
	if (iIndex < GetRoiCount())
	{
		m_vecRoi.erase(m_vecRoi.begin()+iIndex);
		SetRoiVisible(m_vecRoi[iIndex],FALSE);
	}
}
void CHDisplay::DeleteRoi(CHRoiObject* pHRoi)
{
	vector<CHRoiObject*>::iterator it = m_vecRoi.begin();
	for(;it != m_vecRoi.end();)
	{
		if(*it == pHRoi)
		{
			it = m_vecRoi.erase(it);
			SetRoiVisible(pHRoi,FALSE);
		}
		else
			++it;
	}
}
void CHDisplay::DeleteAllRoi()
{
	m_vecRoi.clear();
}
CHRoiObject* CHDisplay::GetRoi(int iIndex)
{
	if (iIndex < GetRoiCount())
	{
		return m_vecRoi[iIndex];
	}
	else
	{
		return NULL;
	}
}
int CHDisplay::GetRoiCount()
{
	return m_vecRoi.size();
}

void CHDisplay::SetRoiVisible(CHRoiObject* pHRoi, BOOL bVisible)
{
	if (bVisible)
	{
		m_hDspWnd.AttachDrawingObjectToWindow(*pHRoi->GetRoiObject());
	}
	else
	{
		m_hDspWnd.DetachDrawingObjectFromWindow(*pHRoi->GetRoiObject());
	}
}


BOOL CHDisplay::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message==WM_KEYDOWN)
	{
		BOOL bCtrl=::GetKeyState(VK_CONTROL)&0xF0000000;
		if (bCtrl)
		{
			if (pMsg->wParam == 'W' || pMsg->wParam == 'w')
			{
				FitSize(1,1);
			}
		}
	}

	return CStatic::PreTranslateMessage(pMsg);
}
