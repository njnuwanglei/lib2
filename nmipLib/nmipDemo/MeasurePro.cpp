
// MeasurePro.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "MeasurePro.h"
#include "MeasureProDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// #include "dog_api.h"
// #pragma comment(lib,"libdog_windows_x64_3150854.lib")
// unsigned char vendor_code[] =
// 	"TGth46Wmwpwr4zTbvUEHbX3eJEk3a/xcx2GExW65fEcs1s+HDM5MwfKmIqgrPtzDpu6REWub"
// 	"e8WyiARBr5dH8x8Nm/UG9jAcEXa31GonKu+ZA3xSVn/SAg0GhUdSijf9g7rDrt4eq7hykw+3"
// 	"CFS1W0Cc6zFjsou1AXDL1XsJr3hbgheuan3vTgj+EecJcmPS95Ecasr3BuN11kaaDNMSZHlJ"
// 	"16+TzjehawHjWA1ooh56ggudexNxMexYPug8GLU2klUCtFKo2udral9xMEVcqpOGo6sZJdEy"
// 	"6kDd3TuSd9VDl6AKeD5LZB7WSeaWCQGT0NDrjisHUTzQwARLfOLFjpwjdXSE6za6sYQ2M6fZ"
// 	"MNyuhfS0YFKMMVCQjYlnCDtP9+UTsKtt2RJXu+sROKyU6EIpOmNX6R3tBix8zRPzDJ1qhOx9"
// 	"RbpPBVFlhB1InaWJCLRwf9x6OJnYPfti4oGlZUB9OgVp4wB7eXXH125xiob7gxURfmWokuUT"
// 	"F/qCyXhGmdu/7shOJRwUfJmuUcLC3DXPwQq66lZSh+IHIT6rLUhiQ+TUG3tiP2r2Jm+FTvQK"
// 	"SJj2dIK0aLGU4kU51gL/zbskKMTOMHS4LbgA2hnO53Xbf4+XGXVA/e/Uidc2QO/zNJgF9b7J"
// 	"1MvjzMwsnWeDp28LaJRr/33M+2kiati7ejp0WXIvDRVESl2grfSn7YewnO3H0PAZUDCk71eN"
// 	"5K+BAUSTFZxuqK8aoRwW2p9WwEpu00JvUitRBNwj1WQoU5RSDyeVgBPFVS1kYu9EdTaRQmcX"
// 	"trvxEMkFnJKaMg/D6wm4Y5fBork9la87qGoVT/Rexan7QS3XvODIOOV54eo7KK/mmuyJ81aa"
// 	"YQy8DOShOKMgtzwA0johr4j911GMa2r0QqIwpCKt7WLJELksdVZZwLylA6EjPd3NeyiuyBNr"
// 	"p2zgIhB9VoWwDdIJ1Cfde70VLDWEVRAeL0dbtP8d/XK8VA==";
// 	
// 	
// CMeasureProApp

BEGIN_MESSAGE_MAP(CMeasureProApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMeasureProApp ����

CMeasureProApp::CMeasureProApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CMeasureProApp ����

CMeasureProApp theApp;


// CMeasureProApp ��ʼ��

BOOL CMeasureProApp::InitInstance()
{
//TODO: call AfxInitRichEdit2() to initialize richedit2 library.
	CWinApp::InitInstance();


	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ���Windows Native���Ӿ����������Ա��� MFC �ؼ�����������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));



	CMeasureProDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}
	else if (nResponse == -1)
	{
// 		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
// 		TRACE(traceAppMsg, 0, "����: ������ڶԻ�����ʹ�� MFC �ؼ������޷� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS��\n");
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

