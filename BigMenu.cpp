#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<tchar.h>
#include<windowsx.h>
#include "menudemo.h"

HBRUSH hBlueBrush, hYellowBrush;
int sw;
HPEN hpen;
MSG msg;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	HWND hMainWnd;
	TCHAR szClassName[] = _T("menudemo");
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(wc));
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = _T("menudemo");
	wc.lpszClassName = szClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	if (!RegisterClassExW(&wc)) {
		MessageBoxW(NULL, _T("Cannot registr class"), _T("Error"), MB_OK);
		return 0;
	}
	hMainWnd = CreateWindow(szClassName, _T("menudemo"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL,
		hInstance, NULL);

	if (!hMainWnd) {
		MessageBox(NULL, _T("Cannot create main window"), _T("Error"), MB_OK);
		return 0;
	}
	ShowWindow(hMainWnd, nCmdShow);
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	return 0;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;
	HMENU hMenu;
	static int iColorID[5] = { WHITE_BRUSH, LTGRAY_BRUSH, GRAY_BRUSH, DKGRAY_BRUSH, BLACK_BRUSH };
	static int iSelection = IDM_WHITE;
	switch (uMsg) {
	case WM_COMMAND:
		hMenu = GetMenu(hWnd);
		switch (LOWORD(wParam))
		{
		case IDM_NEW:
		case IDM_OPEN:
		case IDM_SAVE:
		case IDM_SAVEAS:
			MessageBeep(0);
			return 0;
		case IDM_EXIT:
			SendMessage(hWnd, WM_CLOSE, 0, 0L);
			return 0;
		case IDM_UNDO:
		case IDM_CUT:
		case IDM_COPY:
		case IDM_PASTE:
		case IDM_DEL:
			MessageBeep(0);
			return 0;
		case IDM_WHITE:
		case IDM_LTGRAY:
		case IDM_GRAY:
		case IDM_DKGRAY:
		case IDM_BLACK:
			CheckMenuItem(hMenu, iSelection, MF_UNCHECKED);
			iSelection = LOWORD(wParam);
			CheckMenuItem(hMenu, iSelection, MF_CHECKED);
			SetClassLong(hWnd, GCL_HBRBACKGROUND, (LONG)GetStockObject(iColorID[LOWORD(wParam) - IDM_WHITE]));
			InvalidateRect(hWnd, NULL, TRUE);
			return 0;
		case IDM_START:
			if (SetTimer(hWnd, 1, 1000, NULL))
			{
				EnableMenuItem(hMenu, IDM_START, MF_GRAYED);
				EnableMenuItem(hMenu, IDM_STOP, MF_ENABLED);
			}
			return 0;
		case IDM_STOP:
			KillTimer(hWnd, 1);
			EnableMenuItem(hMenu, IDM_START, MF_ENABLED);
			EnableMenuItem(hMenu, IDM_STOP, MF_GRAYED);
			return 0;
		case IDM_HELP:
			MessageBox(hWnd, _T("No Help"), _T("menudemo"), MB_ICONEXCLAMATION | MB_OK);
			return 0;
		case IDM_ABOUT:
			MessageBox(hWnd, _T("Menu Demonstration"), _T("menudemo"), MB_ICONEXCLAMATION | MB_OK);
			return 0;
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
