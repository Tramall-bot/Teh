#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<tchar.h>
#include<cmath>
#include "menudemo.h"
HBRUSH hBlueBrush, hGreenBrush;
int sw;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	HWND hMainWnd;
	TCHAR szClassName[] = _T("menudemo");
	MSG msg;
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
	HMENU hMenu, hPopupMenu, hPopupMenu2;
	TCHAR str0[] = _T("Фон");
	TCHAR str1[] = _T("Синий");
	TCHAR str2[] = _T("Зелёный"); 
	TCHAR str3[] = _T("Выход");
	TCHAR str4[] = _T("Признаки");
	switch (uMsg) {
	case WM_COMMAND:
		hMenu = GetMenu(hWnd);
		switch (LOWORD(wParam))
		{
		case MI_BLUE:
			sw = 1;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case MI_GREEN:
			sw = 2;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case MI_EXIT:
			DestroyWindow(hWnd);
		}
		break;
	case WM_CREATE:
		hBlueBrush = CreateSolidBrush(RGB(100, 100, 255));
		hGreenBrush = CreateSolidBrush(RGB(100, 255, 100));
		hMenu = CreateMenu();
		hPopupMenu = CreatePopupMenu();
		hPopupMenu2 = CreatePopupMenu();
		AppendMenu(hPopupMenu, MF_STRING, MI_BLUE, str1);
		AppendMenu(hPopupMenu, MF_STRING, MI_GREEN, str2);
		AppendMenu(hPopupMenu, MF_SEPARATOR, 0, NULL);
		AppendMenu(hPopupMenu, MF_STRING, MI_EXIT, str3);

		AppendMenu(hPopupMenu2, MF_STRING, MI_EN, str1);
		AppendMenu(hPopupMenu2, MF_STRING, MI_DIS, str2);
		AppendMenu(hPopupMenu2, MF_SEPARATOR, 0, NULL);
		AppendMenu(hPopupMenu2, MF_STRING, MI_GR, str3);

		AppendMenu(hMenu, MF_POPUP,(UINT)hPopupMenu, str0);
		AppendMenu(hMenu, MF_POPUP, (UINT)hPopupMenu2, str4);
		
		EnableMenuItem(hMenu, MI_GR, MF_GRAYED);
		EnableMenuItem(hMenu, MI_DIS, MF_DISABLED);
		SetMenu(hWnd, hMenu);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		if (sw==1)
		{
			FillRect(hdc, &ps.rcPaint, hBlueBrush);
		}
		if (sw==2)
		{
			FillRect(hdc, &ps.rcPaint, hGreenBrush);
		}
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;

}
