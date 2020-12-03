#define _AFXDLL
#define _CRT_SECURE_NO_WARNINGS
#include <afxwin.h>
#include <string.h>
#include "1.h"

BOOL CApp::InitInstance()
{
	m_pMainWnd = new CMainWin;
	m_pMainWnd->ShowWindow(SW_RESTORE);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

CMainWin::CMainWin()
{
	this->Create(0, "Обработка сообщений");
	strcpy(str, "");
	strcpy(pszMouseStr, "");
	nMouseX = nMouseY = nOldMouseX = nOldMouseY = 0;
}

BEGIN_MESSAGE_MAP(CMainWin, CFrameWnd)
	ON_WM_CHAR()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

afx_msg void CMainWin::OnChar(UINT ch, UINT, UINT)
{
	sprintf(str, "%c", ch);
	this->InvalidateRect(0);
}

afx_msg void CMainWin::OnPaint()
{
	CPaintDC dc(this);
	dc.TextOut(nOldMouseX, nOldMouseY, " ", 0);
	dc.TextOut(nMouseX, nMouseY, pszMouseStr);
	dc.TextOut(1, 1, " ");
	dc.TextOut(1, 1, str);
}

afx_msg void CMainWin::OnLButtonDown(UINT, CPoint loc)
{
	nOldMouseX = nMouseX;
	nOldMouseY = nMouseY;
	strcpy(pszMouseStr, "Нажата левая кнопка");
	nMouseX = loc.x;
	nMouseY = loc.y; 
	this->InvalidateRect(0);
}

afx_msg void CMainWin::OnRButtonDown(UINT, CPoint loc)
{
	nOldMouseX = nMouseX;
	nOldMouseY = nMouseY;
	strcpy(pszMouseStr, "Нажата правая кнопка");
	nMouseX = loc.x;
	nMouseY = loc.y;
	this->InvalidateRect(0);
}

CApp App;
