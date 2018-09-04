
// MeasureProDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"


#include "afxwin.h"




//#define USE_FILE_CAMERA

// CMeasureProDlg �Ի���
class CMeasureProDlg : public CDialogEx
{
// ����
public:
	CMeasureProDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MEASUREPRO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
//	HTuple m_hvDspWnd;

	CHOverlay *m_pHOverlay;

	CHRoiRect2 m_hRoiRect;
	CHRoiCircle m_hRoiCircle;
	CHRoiEllipse m_hEllipse;

	CHRoiLine m_hRoiLine;

	BOOL m_bDispRect;
	BOOL m_bDispLine;


	HObject m_hoImage;
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	void Redraw();
public:
	afx_msg void OnBnClickedButtonLoadImage();
	afx_msg void OnDestroy();


// 	HTuple m_hvDrawLineID;
// 	HTuple m_hvDrawRect2ID;
	afx_msg void OnBnClickedButtonOn();
	afx_msg void OnBnClickedButtonOff();
	afx_msg void OnClose();
	CHDisplay m_hDisp;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButtonFindCoin();
};


Herror HDrawObjCallback(long DrawID, long WindowHandle,char *type);