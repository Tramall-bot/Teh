#define _AFXDLL
#define _CRT_SECURE_NO_WARNINGS
#include <afxwin.h>
#include <string.h>
#include <time.h>
#include "1.h"

BOOL CApp::InitInstance()
{
	m_pMainWnd = new CMainWin;
	m_pMainWnd->ShowWindow(SW_RESTORE);
	m_pMainWnd->UpdateWindow();
	m_pMainWnd->SetTimer(1, 500, 0);
	return TRUE;
}

CMainWin::CMainWin()
{
	RECT rect;
	rect.left = rect.top = 10;
	rect.right = 200;
	rect.bottom = 80;
	strcpy(str, "");
	this->Create(0, "CLOCK", WS_OVERLAPPEDWINDOW, rect);
}

BEGIN_MESSAGE_MAP(CMainWin, CFrameWnd)
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_WM_TIMER()
END_MESSAGE_MAP()

afx_msg void CMainWin::OnTimer(UINT ID)
{
	CTime curtime = CTime::GetCurrentTime();
	tm* newtime;
	tm tm1;
	newtime = curtime.GetLocalTm(&tm1);
	sprintf(str, asctime(newtime));
	str[strlen(str) - 1] = '\0';
	this->InvalidateRect(0);
}
afx_msg void CMainWin::OnPaint()
{
	CPaintDC dc(this);
	dc.TextOut(1, 1, " ", 3);
	dc.TextOut(1, 1, str);
}

afx_msg void CMainWin::OnDestroy()
{
	KillTimer(1);
}

CApp App;
