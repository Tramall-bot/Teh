#include<Windows.h>
#include<tchar.h>
#include"Resource.h"

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
	static BITMAP bm;
	static int cx, cy, m = 0, c = -250;
	static bool move_flag = false;
	switch (uMsg) {
	case WM_CREATE:
		SetTimer(hwnd, 10, 200, NULL);
		hBitmap = LoadBitmap(hinst, MAKEINTRESOURCE(IDB_BITMAP5));
		GetObject(hBitmap, sizeof(bm), &bm);
		hdc = GetDC(hwnd);
		memBit = CreateCompatibleDC(hdc);
		SelectObject(memBit, hBitmap);
		ReleaseDC(hwnd, hdc);
		break;
	case WM_TIMER:
		m += 50;
		c += 50;
		InvalidateRect(hwnd, NULL, TRUE);
		move_flag = !move_flag;
		break;
	case WM_SIZE:
		cx = LOWORD(lParam);
		cy = HIWORD(lParam);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		if (move_flag)
		{
		hBitmap = LoadBitmap(hinst, MAKEINTRESOURCE(IDB_BITMAP4));
		}
		else 
		{
		hBitmap = LoadBitmap(hinst, MAKEINTRESOURCE(IDB_BITMAP5));
		}
		GetObject(hBitmap, sizeof(bm), &bm);
		SelectObject(memBit, hBitmap);
		if (m > cx)
		{
			m = -250;
		}
		BitBlt(hdc, m, cy * 7/10, bm.bmWidth, bm.bmHeight, memBit, 0, 0,  SRCCOPY);
		if (move_flag)
		{
			hBitmap = LoadBitmap(hinst, MAKEINTRESOURCE(IDB_BITMAP6));
		}
		else
		{
			hBitmap = LoadBitmap(hinst, MAKEINTRESOURCE(IDB_BITMAP7));
		}
		GetObject(hBitmap, sizeof(bm), &bm);
		SelectObject(memBit, hBitmap);
		if (c > cx)
		{
			c = -250;
		}
		BitBlt(hdc, c, cy * 7 / 10, bm.bmWidth, bm.bmHeight, memBit, 0, 0, SRCCOPY);
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}
