#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<tchar.h>
#include"Header.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE hinst;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	TCHAR szAppName[] = _T("MainFrame");
	HWND hWnd;
	MSG msg;
	WNDCLASSEX wc;
	hinst = hInstance;
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
	if (!RegisterClassExW(&wc)) {
		MessageBoxW(NULL, _T("Cannot registr class"), _T("Error"), MB_OK);
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


LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;
	HDC hdc;
	HBITMAP hBitmap;
	static HDC memBit;
	RECT rt;
	int i, x, y, p, q;
	static int k;
	static bool Capture;
	static POINT pts[3];
	static BITMAP bm;
	static HPEN hPen;
	switch (uMsg) {
	case WM_CREATE:
		hBitmap = LoadBitmap(hinst, MAKEINTRESOURCE(IDB_BITMAP3));
		GetObject(hBitmap, sizeof(bm), &bm);
		hPen = CreatePen(PS_SOLID, 4, RGB(0, 0, 255));
		GetClientRect(hwnd, &rt);
		x = (rt.right - bm.bmWidth) / 2;
		y = (rt.bottom - bm.bmHeight) / 2;
		pts[0].x = pts[2].x = x;
		pts[0].y = pts[1].y = y;
		pts[1].x = x + bm.bmWidth;
		pts[2].y = y + bm.bmHeight;
		hdc = GetDC(hwnd);
		memBit = CreateCompatibleDC(hdc);
		SelectObject(memBit, hBitmap);
		ReleaseDC(hwnd, hdc);
		break;
	case WM_LBUTTONDOWN:
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		for ( k = 0; k < 3; k++)
		{
			p = x - pts[k].x;
			q = y - pts[k].y;
			if (p*p +q*q < 16)
			{
				SetCapture(hwnd);
				Capture = true;
				return 0;
			}
		}
		break;
	case WM_MOUSEMOVE:
		if (Capture)
		{
			pts[k].x = LOWORD(lParam);
			pts[k].y = HIWORD(lParam);
			InvalidateRect(hwnd,NULL, TRUE);
		}
		break;
	case WM_LBUTTONUP:
		if (Capture)
		{
			ReleaseCapture();
			Capture = false;
		}
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		PlgBlt(hdc, pts, memBit, 0, 0, bm.bmWidth, bm.bmHeight, 0, 0, 0);
		SelectObject(hdc, (HPEN)hPen);
		for ( i = 0; i < 3; i++)
		{
			Ellipse(hdc, pts[i].x - 4, pts[i].y - 4, pts[i].x + 4, pts[i].y + 4);
		}
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		DeleteDC(memBit);
		DeleteObject(hPen);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;

}
