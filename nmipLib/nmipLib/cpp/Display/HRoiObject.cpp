#include "stdafx.h"
#include "..\..\Include\Display\HRoiObject.h"

CHRoiObject::CHRoiObject()
{
// 	SetColor(RGB(255,0,0));
// 	SetLineWidth(1);
    m_clr = RGB(255,0,0);
}

CHRoiObject::~CHRoiObject()
{
}

HDrawingObject* CHRoiObject::GetRoiObject()
{
	return &m_hDrawingObj;
}

void CHRoiObject::SetColor(COLORREF clr)
{
	m_clr = clr;
	int r = GetRValue(clr);
	int g = GetGValue(clr);
	int b = GetBValue(clr);
	char szClr[32] = "";
	sprintf_s(szClr,"#%02x%02x%02x",r,g,b);
	m_hDrawingObj.SetDrawingObjectParams("color",szClr);	

}
COLORREF CHRoiObject::GetColor()
{
	return m_clr;
}
void CHRoiObject::SetLineWidth(int iWidth)
{
	SetDrawingObjectParams(m_hDrawingObj.GetHandle(),"line_width",iWidth);
	// 以下代码出错，原因未知
	//m_hDrawingObj.SetDrawingObjectParams("line_width",iWidth);
}


//////////////////////////////////////////////////////////////////////////
// CHRoiLine
//////////////////////////////////////////////////////////////////////////
void CHRoiLine::SetData(HLine_T hLine)
{
	SetData(hLine.st.x,hLine.st.y,hLine.ed.x,hLine.ed.y);
}
void CHRoiLine::SetData(int iXs, int iYs, int iXe, int iYe)
{
	m_hLine.st.x = iXs;
	m_hLine.st.y = iYs;
	m_hLine.ed.x = iXe;
	m_hLine.ed.y = iYe;
	m_hDrawingObj.CreateDrawingObjectLine(iYs,iXs,iYe,iXe);
}
HLine_T CHRoiLine::GetData()
{
	HTuple hvParams;
	hvParams = m_hDrawingObj.GetDrawingObjectParams(
		HTuple("row1").Append("column1").Append("row2").Append("column2"));
	m_hLine.st.x = hvParams[1].L();
	m_hLine.st.y = hvParams[0].L();
	m_hLine.ed.x = hvParams[3].L();
	m_hLine.ed.y = hvParams[2].L();

	return m_hLine;
}

//////////////////////////////////////////////////////////////////////////
// CHRoiRect 
//////////////////////////////////////////////////////////////////////////
void CHRoiRect::SetData(HRect_T hRect)
{
	SetData(hRect.st.x,hRect.st.y,hRect.ed.x,hRect.ed.y);
}

void CHRoiRect::SetData(int iXs, int iYs, int iXe, int iYe)
{
	m_hRect.st.x = iXs;
	m_hRect.st.y = iYs;
	m_hRect.ed.x = iXe;
	m_hRect.ed.y = iYe;
	m_hDrawingObj.CreateDrawingObjectRectangle1(iYs,iXs,iYe,iXe);
}

HRect_T CHRoiRect::GetData()
{
	HTuple hvParams;
	hvParams = m_hDrawingObj.GetDrawingObjectParams(
		HTuple("row1").Append("column1").Append("row2").Append("column2"));
	m_hRect.st.x = hvParams[1].L();
	m_hRect.st.y = hvParams[0].L();
	m_hRect.ed.x = hvParams[3].L();
	m_hRect.ed.y = hvParams[2].L();
	return m_hRect;
}


//////////////////////////////////////////////////////////////////////////
// CHRoiCircle 
//////////////////////////////////////////////////////////////////////////
void CHRoiCircle::SetData(HCircle_T hCircle)
{
	SetData(hCircle.center.x,hCircle.center.y,hCircle.radius);
}
void CHRoiCircle::SetData(int iX, int iY, double dRadius)
{
	m_hCircle.center.x = iX;
	m_hCircle.center.y = iY;
	m_hCircle.radius = dRadius;
	m_hDrawingObj.CreateDrawingObjectCircle(iY,iX,dRadius);
}
HCircle_T CHRoiCircle::GetData()
{
	HTuple hvParams;
	hvParams = m_hDrawingObj.GetDrawingObjectParams(
		HTuple("row").Append("column").Append("radius"));

	m_hCircle.center.x = hvParams[1].D();
	m_hCircle.center.y = hvParams[0].D();
	m_hCircle.radius = hvParams[2].D();
	return m_hCircle;
}

//////////////////////////////////////////////////////////////////////////
// CHRoiEllipse
//////////////////////////////////////////////////////////////////////////
void CHRoiEllipse::SetData(HEllipse_T hEllipse)
{
	SetData(hEllipse.center.x, hEllipse.center.y, hEllipse.axisX, hEllipse.axisY, hEllipse.angle);
}
void CHRoiEllipse::SetData(int iX, int iY, double dAxisX, double dAxisY, double dAngle)
{
	m_hEllipse.center.x = iX;
	m_hEllipse.center.y = iY;
	m_hEllipse.axisX = dAxisX;
	m_hEllipse.axisY = dAxisY;
	m_hEllipse.angle = dAngle;

	m_hDrawingObj.CreateDrawingObjectEllipse(iY,iX,dAngle,dAxisY,dAxisX);
}

/*
'row': Row coordinate of the center of the ellipse.

'column': Column coordinate of the center of the ellipse.

'phi': Orientation of the first half axis in radians.

'radius1': Length of the first half axis.

'radius2': Length of the second half axis.
 */
HEllipse_T CHRoiEllipse::GetData()
{
	HTuple hvParams;
	hvParams = m_hDrawingObj.GetDrawingObjectParams(
		HTuple("row").Append("column").Append("phi").Append("radius1").Append("radius2"));

	m_hEllipse.center.x = hvParams[1].D();
	m_hEllipse.center.y = hvParams[0].D();
	m_hEllipse.axisX = hvParams[4].D();
	m_hEllipse.axisY = hvParams[3].D();
	m_hEllipse.angle = hvParams[2].D();

	return m_hEllipse;
}



//////////////////////////////////////////////////////////////////////////
// CHRoiRect2
//////////////////////////////////////////////////////////////////////////
void CHRoiRect2::SetData(HRect2_T hRect)
{
	SetData(hRect.center.x,hRect.center.y,hRect.length1,hRect.length2, hRect.angle);
}
void CHRoiRect2::SetData(int iXs, int iYs, double dLength1, double dLength2, double dAngle)
{
	m_hRect.center.x = iXs;
	m_hRect.center.y = iYs;
	m_hRect.length1 = dLength1;
	m_hRect.length2 = dLength2;
	m_hRect.angle = dAngle;
	m_hDrawingObj.CreateDrawingObjectRectangle2(iYs,iXs,dAngle,dLength1,dLength2);
}
/*
'row': Row coordinate of the center of the rectangle.

'column': Column coordinate of the center of the rectangle.

'phi': Orientation of the first half axis in radians.

'length1': Length of the first half axis.

'length2': Length of the second half axis.
*/
HRect2_T CHRoiRect2::GetData()
{
	HTuple hvParams;
	hvParams = m_hDrawingObj.GetDrawingObjectParams(
		HTuple("row").Append("column").Append("phi").Append("length1").Append("length2"));
	m_hRect.center.x = hvParams[1].D();
	m_hRect.center.y = hvParams[0].D();
	m_hRect.length1 = hvParams[3].D();
	m_hRect.length2 = hvParams[4].D();
	m_hRect.angle = hvParams[2].D();	
	
	return m_hRect;
}
