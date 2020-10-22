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
	int a, b;
	static int figure, width;
	static COLORREF color;
	HBRUSH oldbrush, hbrush;
	HPEN oldpen, hpen;
	RECT rt;
	switch (uMsg) {
	case WM_CREATE:
		figure = 0;
		width = 1;
		color = RGB(255, 255, 255);
		break;
	case WM_COMMAND:
		hMenu = GetMenu(hWnd);
		switch (LOWORD(wParam))
		{
		case RECTANGLE:
			figure = 0;
			break;
		case ELLIPSE:
			figure = 1;
			break;
		case THIN:
			width = 1;
			break;
		case THICK:
			width = 2;
			break;
		case RED:
			color = RGB(255, 0, 0);
			break;
		case GREEN:
			color = RGB(0, 255, 0);
			break;
		case BLUE:
			color = RGB(0, 0, 255);
			break;
		}
		InvalidateRect(hWnd, NULL, 1);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rt);
		a = rt.right;
		b = rt.bottom;
		hpen = CreatePen(PS_SOLID, width, 0);
		oldpen = (HPEN)SelectObject(hdc, hpen);
		hbrush = CreateSolidBrush(color);
		oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
		if (figure==0)
		{
			Rectangle(hdc, a / 4, b / 4, a * 3 / 4, b * 3 / 4);
		}
		else
		{
			Ellipse(hdc, a / 4, b / 4, a * 3 / 4, b * 3 / 4);
		}
		SelectObject(hdc, oldpen);
		SelectObject(hdc, oldbrush);
		DeleteObject(hpen);
		DeleteObject(hbrush);
		EndPaint(hWnd, &ps);
		break;
	case WM_SIZE:
		InvalidateRect(hWnd, NULL, 1);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;

}
