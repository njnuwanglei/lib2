
// MeasurePro.cpp : 定义应用程序的类行为。
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


// CMeasureProApp 构造

CMeasureProApp::CMeasureProApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CMeasureProApp 对象

CMeasureProApp theApp;


// CMeasureProApp 初始化

BOOL CMeasureProApp::InitInstance()
{
//TODO: call AfxInitRichEdit2() to initialize richedit2 library.
	CWinApp::InitInstance();


	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 激活“Windows Native”视觉管理器，以便在 MFC 控件中启用主题
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));



	CMeasureProDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}
	else if (nResponse == -1)
	{
// 		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
// 		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}

