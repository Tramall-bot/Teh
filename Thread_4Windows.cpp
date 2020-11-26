#include<Windows.h>
#include<tchar.h>
#include<process.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

typedef struct
{
	HWND hwnd;
	int cxClient;
	int cyClient;
	int cyChar;
	BOOL bKill;
}
PARAMS, * PPARAMS;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	TCHAR szAppName[] = _T("MainFrame");
	MSG msg;
	HWND hWnd;
	WNDCLASSEX wc;
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szAppName;
	wc.hIconSm = LoadIcon(hInstance, szAppName);
	//Регистрируем класс окна
	if (!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Cannot registr class", "Error", MB_OK);
		return 0;
	}
	//Создаем основное окно приложения
	hWnd = CreateWindow(szAppName, _T("Каркас"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL,
		hInstance, NULL);

	if (!hWnd) {
		MessageBox(NULL, _T("Cannot create main window"), _T("Error"), MB_OK);
		return 0;
	}

	ShowWindow(hWnd, nCmdShow);
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	return msg.wParam;

}
int CheckBottom(HWND hwnd, int cyClient, int cyChar, int iLine)
{
	if (iLine * cyChar + cyChar > cyClient)
	{
		InvalidateRect(hwnd, NULL, TRUE);
		UpdateWindow(hwnd);
		iLine = 0;
	}
	return iLine;
}
VOID Thred1(PVOID pvoid) {
	int iNum = 0, iLine = 0;
	char szBuffer[16];
	HDC hdc;
	PPARAMS pparams = (PPARAMS)pvoid;
	while (!pparams->bKill) {
		if (iNum < 0)
			iNum = 0;
		iLine = CheckBottom(pparams->hwnd, pparams->cyClient, pparams->cyChar, iLine);
		wsprintf(szBuffer, "%d", iNum++);
		hdc = GetDC(pparams->hwnd);
		TextOut(hdc, 0, iLine * pparams->cyChar, szBuffer, strlen(szBuffer));
		ReleaseDC(pparams->hwnd, hdc);
		iLine++;
	}
	_endthread();
}
LRESULT APIENTRY WndProc1(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static PARAMS params;
	switch (msg)
	{
	case WM_CREATE:
		params.hwnd = hwnd;
		params.cyChar = HIWORD(GetDialogBaseUnits());
		_beginthread(Thred1, 0, &params);
		break;
	case WM_SIZE:
		params.cyClient = HIWORD(lParam);
		break;
	case WM_DESTROY:
		params.bKill = TRUE;
		break;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}


VOID Thred2(PVOID pvoid) {
	int iNum = 1, iLine = 0, i, iSqrt;
	char szBuffer[16];
	HDC hdc;
	PPARAMS pparams = (PPARAMS)pvoid;
	while (!pparams->bKill) {
		do
		{
			if (++iNum < 0)
				iNum = 0;
			iSqrt = (int)sqrt(iNum);
			for ( i = 2; i <= iSqrt; i++)
			{
				if (iNum % i == 0)
					break;
			}
		} while (i <= iSqrt);
		iLine = CheckBottom(pparams->hwnd, pparams->cyClient, pparams->cyChar, iLine);
		wsprintf(szBuffer, "%d", iNum++);
		hdc = GetDC(pparams->hwnd);
		TextOut(hdc, 0, iLine * pparams->cyChar, szBuffer, strlen(szBuffer));
		ReleaseDC(pparams->hwnd, hdc);
		iLine++;
	}
	_endthread();
}

LRESULT APIENTRY WndProc2(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static PARAMS params;
	switch (msg)
	{
	case WM_CREATE:
		params.hwnd = hwnd;
		params.cyChar = HIWORD(GetDialogBaseUnits());
		_beginthread(Thred2, 0, &params);
		break;
	case WM_SIZE:
		params.cyClient = HIWORD(lParam);
		break;
	case WM_DESTROY:
		params.bKill = TRUE;
		break;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}



VOID Thred3(PVOID pvoid) {
	int iNum = 0, iLine = 0, iNext = 1, iTemp;
	char szBuffer[16];
	HDC hdc;
	PPARAMS pparams = (PPARAMS)pvoid;
	while (!pparams->bKill) {
		if (iNum < 0)
		{
			iNum = 0;
			iNext = 1;
		}
		iLine = CheckBottom(pparams->hwnd, pparams->cyClient, pparams->cyChar, iLine);
		wsprintf(szBuffer, "%d", iNum++);
		hdc = GetDC(pparams->hwnd);
		TextOut(hdc, 0, iLine * pparams->cyChar, szBuffer, strlen(szBuffer));
		ReleaseDC(pparams->hwnd, hdc);
		iTemp = iNum;
		iNum = iNext;
		iNext += iTemp;
		iLine++;
	}
	_endthread();
}
LRESULT APIENTRY WndProc3(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static PARAMS params;
	switch (msg)
	{
	case WM_CREATE:
		params.hwnd = hwnd;
		params.cyChar = HIWORD(GetDialogBaseUnits());
		_beginthread(Thred3, 0, &params);
		break;
	case WM_SIZE:
		params.cyClient = HIWORD(lParam);
		break;
	case WM_DESTROY:
		params.bKill = TRUE;
		break;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}


VOID Thred4(PVOID pvoid) {
	int iDiametr;
	HDC hdc;
	PPARAMS pparams = (PPARAMS)pvoid;
	while (!pparams->bKill) {
		InvalidateRect(pparams->hwnd, NULL, TRUE);
		UpdateWindow(pparams->hwnd);
		iDiametr = rand() % (max(1, min(pparams->cxClient, pparams->cyClient)));
		hdc = GetDC(pparams->hwnd);
		Ellipse(hdc, (pparams->cxClient - iDiametr) / 2, (pparams->cyClient - iDiametr) / 2, (pparams->cxClient + iDiametr) / 2, (pparams->cyClient + iDiametr) / 2);
		ReleaseDC(pparams->hwnd, hdc);
	}
	_endthread();
}
LRESULT APIENTRY WndProc4(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static PARAMS params;
	switch (msg)
	{
	case WM_CREATE:
		params.hwnd = hwnd;
		params.cyChar = HIWORD(GetDialogBaseUnits());
		_beginthread(Thred4, 0, &params);
		break;
	case WM_SIZE:
		params.cyClient = HIWORD(lParam);
		params.cxClient = LOWORD(lParam);
		break;
	case WM_DESTROY:
		params.bKill = TRUE;
		break;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	static LPCSTR szChildClass[4] = { "Child1", "Child2", "Child3", "Child4" };
	static HWND hwndChild[4];
	static WNDPROC ChildProc[] = { WndProc1, WndProc2, WndProc3, WndProc4 };
	HINSTANCE hInstance;
	int i, cxClient, cyClient;
	WNDCLASSEX wc;
	switch (uMsg) {
	case WM_CREATE:
		hInstance = (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE);
		wc.cbSize = sizeof(wc);
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = hInstance;
		wc.hIcon = NULL;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		wc.lpszMenuName = NULL;
		wc.hIconSm = NULL;
		for (i = 0; i < 4; i++)
		{
			wc.lpfnWndProc = ChildProc[i];
			wc.lpszClassName = szChildClass[i];
			RegisterClassEx(&wc);
			hwndChild[i] = CreateWindow(szChildClass[i], NULL, WS_CHILDWINDOW | WS_BORDER | WS_VISIBLE, 0, 0, 0, 0, hwnd, (HMENU)i, hInstance, NULL);
		}
		break;
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		for(i = 0; i < 4; i++)
			MoveWindow(hwndChild[i], (i % 2) * cxClient / 2, (i > 1)* cyClient / 2, cxClient / 2, cyClient / 2, TRUE);
		break;
	case WM_CHAR:
		if (wParam == '\x18')
			DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}
