
// MeasureProDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MeasurePro.h"
#include "MeasureProDlg.h"
#include "afxdialogex.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

Herror HDrawObjCallback(long DrawID, long WindowHandle,char *type)
{
// 	CMeasureProDlg* pWnd = (CMeasureProDlg*)(AfxGetApp()->GetMainWnd());
// 	HTuple hvParam;
// 	GetDrawingObjectParams(pWnd->m_hoDrawRect.GetHandle(),((HTuple("row1").Append("column1")).Append("row2").Append("column2")),&hvParam);
// 
// 	CString strInfo;
// 	strInfo.Format("Pos:%3d,%3d,%3d,%3d",hvParam[0].I(),hvParam[1].I(),hvParam[2].I(),hvParam[3].I());
// 	pWnd->SetDlgItemText(IDC_STATIC_TEXT,strInfo);
	return 0;
}

CMeasureProDlg::CMeasureProDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMeasureProDlg::IDD, pParent)
{
	AfxInitRichEdit2();

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	GenImageConst(&m_hoImage,"byte",640,480);





	m_bDispRect = FALSE;
	m_bDispLine = FALSE;

}

void CMeasureProDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_IMAGE, m_hDisp);
}

BEGIN_MESSAGE_MAP(CMeasureProDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_LOAD_IMAGE, &CMeasureProDlg::OnBnClickedButtonLoadImage)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_ON, &CMeasureProDlg::OnBnClickedButtonOn)
	ON_BN_CLICKED(IDC_BUTTON_OFF, &CMeasureProDlg::OnBnClickedButtonOff)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON1, &CMeasureProDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_FIND_COIN, &CMeasureProDlg::OnBnClickedButtonFindCoin)
END_MESSAGE_MAP()


// CMeasureProDlg ��Ϣ�������

BOOL CMeasureProDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	// Image Disp Init
	m_hDisp.SetImage(&m_hoImage);
	m_pHOverlay = m_hDisp.CreateOverlay();
//	HalconCpp::SetFont(m_hvDspWnd,"-����-12-*-*-*-*-1-");


	m_hRoiRect.SetData(300,300,100,100,0.5);
	m_hRoiRect.SetLineWidth(1);
	m_hRoiRect.SetColor(RGB(0,255,0));
	m_hDisp.AddRoi(&m_hRoiRect);

	m_hRoiCircle.SetData(200,200,50);
	m_hDisp.AddRoi(&m_hRoiCircle);
	m_hEllipse.SetData(200,200,100,200,0.1);
	m_hDisp.AddRoi(&m_hEllipse);
	m_hEllipse.SetColor(RGB(255,255,0));
	m_hEllipse.SetLineWidth(1);
	m_hRoiLine.SetData(200,200,400,400);
	m_hDisp.AddRoi(&m_hRoiLine);

	

// 	m_hoDrawRect.CreateDrawingObjectRectangle1(100,100,200,200);
// 	m_hoDrawRect2.CreateDrawingObjectRectangle1(100,100,200,200);
// 	m_hoDrawRect.SetDrawingObjectCallback(HTuple("on_resize"),HDrawObjCallback);
// 	m_hoDrawRect.SetDrawingObjectCallback(HTuple("on_drag"),HDrawObjCallback);
// 	m_hoDrawRect2.SetDrawingObjectCallback(HTuple("on_resize"),HDrawObjCallback);
// 	m_hoDrawRect2.SetDrawingObjectCallback(HTuple("on_drag"),HDrawObjCallback);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMeasureProDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}


HCURSOR CMeasureProDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



		
void CMeasureProDlg::OnBnClickedButtonLoadImage()
{
	CFileDialog dlg(TRUE, _T(".bmp"), _T(""));
	if(IDOK == dlg.DoModal())
	{
		CString strPathName = dlg.GetPathName();
		ReadImage(&m_hoImage,strPathName.GetBuffer(strPathName.GetLength()));

// 		HTuple hvWidth,hvHeight;
// 		GetImageSize(m_hoImage,&hvWidth,&hvHeight);
// 		SetPart(m_hvDspWnd,0,0,hvHeight-1,hvWidth-1);
// 		DispObj(m_hoImage,m_hvDspWnd);
// 		
 		
 		m_hDisp.SetImage(&m_hoImage);
		m_hDisp.FitSize(1,1);
// 		HRegion reg;
// 		reg.GenCircle(200,200,100);
// 		m_pHOverlay->DrawRegion(reg,RGB(255,0,0));
// 		reg.GenRectangle2(300,300,1,200,50);
// 		m_pHOverlay->DrawRegion(reg,RGB(0,0,255));
         m_hDisp.Redraw();

	}
}







void CMeasureProDlg::OnDestroy()
{

	CDialogEx::OnDestroy();

}



void CMeasureProDlg::OnBnClickedButtonOn()
{
// 	AttachDrawingObjectToWindow(m_hvDspWnd,m_hoDrawRect);
// 	AttachDrawingObjectToWindow(m_hvDspWnd,m_hvDrawRect2ID);
// 	m_hoDrawRect.SetDrawingObjectParams("line_width",1);
// 	m_hoDrawRect2.SetDrawingObjectParams("line_width",1);
// 	
// 	
	m_hDisp.SetRoiVisible(&m_hRoiLine);
	m_hDisp.SetRoiVisible(&m_hRoiRect);
	m_hDisp.SetRoiVisible(&m_hRoiCircle);
	m_hDisp.SetRoiVisible(&m_hEllipse);
	

}


void CMeasureProDlg::OnBnClickedButtonOff()
{
// 	DetachDrawingObjectFromWindow(m_hvDspWnd,m_hoDrawRect.GetHandle());
// 	DetachDrawingObjectFromWindow(m_hvDspWnd,m_hoDrawRect2.GetHandle());
// 	
// 	
// 	
// 	m_pHOverlay->ClearOverlay();
// 	HRect2_T hRect = m_hRoiRect.GetData();
// 	HCircle_T hCircle = m_hRoiCircle.GetData();
// 	HEllipse_T hEllipse = m_hEllipse.GetData();
// 	HLine_T hLine = m_hRoiLine.GetData();
// 
// 	m_hDisp.SetRoiVisible(&m_hRoiRect,0);
// 	m_hDisp.SetRoiVisible(&m_hRoiCircle,0);
// 	m_hDisp.SetRoiVisible(&m_hEllipse,0);
// 	m_hDisp.SetRoiVisible(&m_hRoiLine,0);
// 
// 	HRegion reg;
//  	reg.GenCircle(hCircle.center.y,hCircle.center.x,hCircle.radius);
//  	m_pHOverlay->DrawRegion(reg,m_hRoiCircle.GetColor());
// 	reg.GenRectangle2(hRect.center.y,hRect.center.x,hRect.angle,hRect.length1,hRect.length2);
// 	m_pHOverlay->DrawRegion(reg,m_hRoiRect.GetColor());
// 	reg.GenEllipse(hEllipse.center.y,hEllipse.center.x,hEllipse.angle,hEllipse.axisY,hEllipse.axisX);
// 	m_pHOverlay->DrawRegion(reg,m_hEllipse.GetColor());
// 
// 	
// 	reg.GenRegionLine(hLine.st.y,hLine.st.x,hLine.ed.y,hLine.ed.x);
// 	m_pHOverlay->DrawRegion(reg,m_hRoiLine.GetColor());
// 
// 
// 	m_hDisp.Redraw();

}


void CMeasureProDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//m_hvDrawRectID.Clear();
	CDialogEx::OnClose();
}


void CMeasureProDlg::OnBnClickedButton1()
{
	HRegion reg;
    reg.GenRectangle2(500,500,1,100,100);
	//m_pHOverlay->DrawRegion(reg,m_hRoiLine.GetColor());
	m_hDisp.Redraw();

}

void CMeasureProDlg::OnBnClickedButtonFindCoin()
{
	CFindCoin fd;
	fd.SetCoinRadius(250);
	fd.SetEnhanceCoeff(0.1);
	fd.Execute(m_hoImage);
	FINDCOIN_RESULT_T tResult = fd.GetResult();
	HRegion reg;
	reg.GenCircle(tResult.ptCenter.y, tResult.ptCenter.x, tResult.iRadius);
	m_pHOverlay->ClearOverlay();
	m_pHOverlay->DrawRegion(reg, m_hRoiLine.GetColor());
	m_hDisp.Redraw();
}
