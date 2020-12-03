#include <afxwin.h>

class CMainWin : public CFrameWnd {
public:
	CMainWin();
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT ID);
	char str[50];
	DECLARE_MESSAGE_MAP()
};

class  CApp: public CWinApp
{
public:
	BOOL InitInstance();
};

