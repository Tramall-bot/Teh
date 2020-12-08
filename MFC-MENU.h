#include <afxwin.h>


class CMainWin : public CFrameWnd {
public:
	CMainWin();
	afx_msg void OnLButtonDown(UINT flags, CPoint loc);
	afx_msg void OnRButtonDown(UINT flags, CPoint loc);
	afx_msg void OnAlpha();
	afx_msg void OnBeta();
	afx_msg void OnGamma();
	afx_msg void OnEpsilon();
	afx_msg void OnZeta();
	afx_msg void OnEta();
	afx_msg void OnTheta();
	afx_msg void OnHelp();
	DECLARE_MESSAGE_MAP()
};

class  CApp : public CWinApp
{
public:
	BOOL InitInstance();
};

