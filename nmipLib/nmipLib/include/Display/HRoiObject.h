#pragma once
#include "..\nmipExport.h"

#include "afxwin.h"
//////////////////////////////////////////////////////////////////////////
// CHRoiObject
class NMIP_DLL_API CHRoiObject
{
public:
    CHRoiObject();
	// 基类一定需要有虚函数，不然typeid不能正确识别？？？
	virtual ~CHRoiObject();  
	void SetColor(COLORREF clr);
	COLORREF GetColor();
	void SetLineWidth(int iWidth);
	HDrawingObject* GetRoiObject();

protected:
	HDrawingObject m_hDrawingObj;
	COLORREF m_clr;
}; 

//////////////////////////////////////////////////////////////////////////
// CHRoiLine
struct HLine_T
{
	POINT st;
	POINT ed;
};
class NMIP_DLL_API CHRoiLine:
	public CHRoiObject
{
public:
	void SetData(HLine_T hLine);
	void SetData(int iXs, int iYs, int iXe, int iYe);
	HLine_T GetData();
private:
	HLine_T m_hLine;
};
//////////////////////////////////////////////////////////////////////////
// CHRoiRect
struct HRect_T
{
	POINT st;
	POINT ed;
};
class NMIP_DLL_API CHRoiRect:
	public CHRoiObject
{
public:
	void SetData(HRect_T hRect);
	void SetData(int iXs, int iYs, int iXe, int iYe);
	HRect_T GetData();
private:
	HRect_T m_hRect;
};


//////////////////////////////////////////////////////////////////////////
// CHRoiCircle
struct HCircle_T
{
	POINT center;
	double radius;
};
class NMIP_DLL_API CHRoiCircle:
	public CHRoiObject
{
public:
	void SetData(HCircle_T hCircle);
	void SetData(int iX, int iY, double dRadius);
	HCircle_T GetData();
private:
	HCircle_T m_hCircle;

};

//////////////////////////////////////////////////////////////////////////
// CHRoiEllipse
struct HEllipse_T
{
	POINT center ;
	double  axisX ;
	double  axisY ;
	double  angle ;
};
class NMIP_DLL_API CHRoiEllipse:
	public CHRoiObject
{
public:
	void SetData(HEllipse_T hEllipse);
	void SetData(int iX, int iY, double dAxisX, double dAxisY, double dAngle);
	HEllipse_T GetData();
private:
	HEllipse_T m_hEllipse;
};


//////////////////////////////////////////////////////////////////////////
// CHRoiRect2
struct HRect2_T
{
	POINT center;
	double length1;
	double length2;
	double angle;
};

class NMIP_DLL_API CHRoiRect2:
	public CHRoiObject
{
public:
	void SetData(HRect2_T hRect);
	void SetData(int iXs, int iYs, double dLength1, double dLength2, double dAngle);
	HRect2_T GetData();
private:
	HRect2_T m_hRect;

};

