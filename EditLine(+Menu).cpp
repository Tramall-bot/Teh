#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<tchar.h>
TCHAR szClassName[] = _T("PopPad1");
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	HWND hWnd;
	WNDCLASSEX wc;
	MSG msg;
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = _T("Menu");
	wc.lpszClassName = szClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&wc);
	hWnd = CreateWindow(szClassName, szClassName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL,
		hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	return msg.wParam;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	int cx = 0, cy, temp;
	TCHAR temp2[255] = { 0 };
	TCHAR temp3[15] = _T("Line count = ");
	TCHAR temp4[20] = _T("Offset = ");
	TCHAR temp5[18] = _T("Line Length = ");
	TCHAR temp6[41] = _T("First index = ");
	TCHAR temp7[41] = _T(" Last index = ");
	static HWND hwndEdit;
	HMENU hMenu, hPopupMenu;
	switch (uMsg) {
	case WM_CREATE:
		hwndEdit = CreateWindow(_T("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | WS_BORDER | ES_LEFT | ES_MULTILINE | ES_AUTOHSCROLL | ES_AUTOVSCROLL, 0, 0, 0, 0, hWnd, (HMENU)1, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
		hMenu = CreateMenu();
		hPopupMenu = CreatePopupMenu();
		AppendMenu(hPopupMenu, MF_STRING, 2, _T("Paste"));
		AppendMenu(hPopupMenu, MF_STRING, 3, _T("Replase Selected"));
		AppendMenu(hPopupMenu, MF_STRING, 4, _T("Get Line Count"));
		AppendMenu(hPopupMenu, MF_STRING, 8, _T("Select All"));
		AppendMenu(hPopupMenu, MF_STRING, 9, _T("Get Line's First and Last index"));
		AppendMenu(hPopupMenu, MF_STRING, 5, _T("Get Offset"));
		AppendMenu(hPopupMenu, MF_STRING, 6, _T("Get Line Length"));
		AppendMenu(hPopupMenu, MF_STRING, 7, _T("Get Line"));
		AppendMenu(hMenu, MF_POPUP, (UINT)hPopupMenu, _T("Here"));
		SetMenu(hWnd, hMenu);
		break;
	case WM_SETFOCUS:
		SetFocus(hwndEdit);
		break;
	case WM_SIZE:
		cx = LOWORD(lParam);
		cy = HIWORD(lParam);
		MoveWindow(hwndEdit, 0, 0, cx-200, cy-200, TRUE);
		break;
	case WM_COMMAND:
		hMenu = GetMenu(hWnd);
		if (LOWORD(wParam) == 1)
			if (HIWORD(wParam) == EN_ERRSPACE or HIWORD(wParam) == EN_MAXTEXT)
				MessageBox(hWnd, _T("Edit control out of space"), szClassName, MB_OK | MB_ICONSTOP);
		if (LOWORD(wParam) == 2)
			SendMessage(hwndEdit, WM_PASTE, 0, 0);
		if (LOWORD(wParam) == 3)
			SendMessage(hwndEdit, EM_REPLACESEL, 0, (LPARAM)_T("Text"));
		if (LOWORD(wParam) == 4) {
			temp = SendMessage(hwndEdit, EM_GETLINECOUNT, 0, 0);
			SendMessage(hwndEdit, EM_REPLACESEL, 0, (LPARAM)_tcscat(temp3, _itot(temp, temp2, 10)));
		}
		if (LOWORD(wParam) == 5) {
			temp = SendMessage(hwndEdit, EM_LINEINDEX,-1, 0);
			SendMessage(hwndEdit, EM_REPLACESEL, 0, (LPARAM)_tcscat(temp4, _itot(temp, temp2, 10)));
		}
		if (LOWORD(wParam) == 6) {
			temp = SendMessage(hwndEdit, EM_LINELENGTH, -1, 0);
			SendMessage(hwndEdit, EM_REPLACESEL, 0, (LPARAM)_tcscat(temp5, _itot(temp, temp2, 10)));
		}
		if (LOWORD(wParam) == 7) {
			temp2[0] = '0';
			temp = SendMessage(hwndEdit, EM_GETLINE, 0,(LPARAM) temp2);
			temp2[temp] = '\0';
			SendMessage(hwndEdit, EM_REPLACESEL, 0, (LPARAM)temp2);
		}
		if (LOWORD(wParam) == 8)
			SendMessage(hwndEdit, EM_SETSEL, 0, -1);
		if (LOWORD(wParam) == 9)
		{
			temp = SendMessage(hwndEdit, EM_GETSEL,0,0);
			SendMessage(hwndEdit, EM_REPLACESEL, 0, (LPARAM)_tcscat(_tcscat(temp6, _itot(LOWORD(temp), temp2, 10)), _tcscat(temp7, _itot(HIWORD(temp), temp2, 10))));
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;

}
