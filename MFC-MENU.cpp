#define _AFXDLL
#define _CRT_SECURE_NO_WARNINGS
#include <afxwin.h>
#include "2.h"
#include "resource.h"

BOOL CApp::InitInstance()
{
	m_pMainWnd = new CMainWin;
	m_pMainWnd->ShowWindow(SW_RESTORE);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

CMainWin::CMainWin()
{

	this->Create(0, "Using menus", WS_OVERLAPPEDWINDOW, rectDefault, NULL, "MYMENU");
}

BEGIN_MESSAGE_MAP(CMainWin, CFrameWnd)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(IDM_ALPHA, OnAlpha)
	ON_COMMAND(IDM_BETA, OnBeta)
	ON_COMMAND(IDM_GAMMA, OnGamma)
	ON_COMMAND(IDM_EPSILON, OnEpsilon)
	ON_COMMAND(IDM_ZETA, OnZeta)
	ON_COMMAND(IDM_ETA, OnEta)
	ON_COMMAND(IDM_THETA, OnTheta)
	ON_COMMAND(IDM_HELP, OnHelp)
END_MESSAGE_MAP()




afx_msg void CMainWin::OnLButtonDown(UINT flags, CPoint loc)
{
	int i;
	i = MessageBox("Press One", "Left Button", MB_ABORTRETRYIGNORE);
	switch (i)
	{
	case IDABORT:
		MessageBox("", "Abort");
		break;
	case IDRETRY:
		MessageBox("", "Retry");
		break;
	case IDIGNORE:
		MessageBox("", "Ignore");
		break;
	default:
		break;
	}
}

afx_msg void CMainWin::OnRButtonDown(UINT flags, CPoint loc)
{
	int i;
	i = MessageBox("Press One", "Right Button", MB_ICONHAND | MB_YESNO);
	switch (i)
	{
	case IDYES:
		MessageBox("", "Yes");
		break;
	case IDNO:
		MessageBox("", "No");
		break;
	default:
		break;
	}
}
afx_msg void CMainWin::OnAlpha()
{
	MessageBox("Alpha", "Alpha");
}

afx_msg void CMainWin::OnBeta()
{
	MessageBox("Beta", "Beta");
}

afx_msg void CMainWin::OnGamma()
{
	MessageBox("Gamma", "Gamma");
}

afx_msg void CMainWin::OnEpsilon()
{
	MessageBox("Epsilon", "Epsilon");
}

afx_msg void CMainWin::OnZeta()
{
	MessageBox("Zeta", "Zeta");
}

afx_msg void CMainWin::OnEta()
{
	MessageBox("Eta", "Eta");
}

afx_msg void CMainWin::OnTheta()
{
	MessageBox("Theta", "Theta");
}

afx_msg void CMainWin::OnHelp()
{
	MessageBox("Menu Demo", "Help");
}
CApp App;
