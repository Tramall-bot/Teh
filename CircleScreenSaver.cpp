#include<Windows.h>
#include<tchar.h>
#include"Resource.h"
#include <math.h>
const int SPAN = 10;
char szClassName[] = "Name";
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE hInst;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	HWND hWnd;
	WNDCLASSEX wc;
	MSG msg;
	hInst = hInstance;
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = _T("menu");
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
	HDC hdc;
	PAINTSTRUCT ps;
	int mx, my;
	static double mod, vx, vy, xt, yt;
	static HDC memDC;
	static HPEN hpen;
	static int x, y, cx, cy, scrx, scry;
	static HBITMAP hCircle;
	static bool play;
	switch (uMsg) {
	case WM_CREATE:
		hpen = CreatePen(PS_SOLID, 4, RGB(255, 0, 0));
		hCircle = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_CIRCLE));
		hdc = GetDC(hWnd);
		memDC = CreateCompatibleDC(hdc);
		SelectObject(memDC, hCircle);
		ReleaseDC(hWnd, hdc);
		break;
	case WM_SIZE:
		scrx = LOWORD(lParam);
		scry = HIWORD(lParam);
		x = (cx = scrx / 2) - 16;
		y = (cy = scry / 2) - 16;
		break;
	case WM_LBUTTONDOWN:
		if (!play)
		{
			mx = LOWORD(lParam);
			my = HIWORD(lParam);
			vx = mx - cx;
			vy = my - cy;
			mod = sqrt(vx * vx + vy * vy);
			vx = vx / mod;
			vy = vy / mod;
			hdc = GetDC(hWnd);
			SelectObject(hdc, hpen);
			MoveToEx(hdc, cx, cy, 0);
			LineTo(hdc, mx, my);
			LineTo(hdc, mx - (vx - vy) * SPAN, my - (vy + vx) * SPAN);
			MoveToEx(hdc, mx - (vx + vy) * SPAN, my - (vy - vx) * SPAN, 0);
			LineTo(hdc, mx, my);
			ReleaseDC(hWnd, hdc);
			play = true;
		}
		break;
	case WM_TIMER:
		hdc = GetDC(hWnd);
		BitBlt(hdc, x, y, 32, 32, NULL, 0, 0, PATCOPY);
		if (x + 31 > scrx || x < 1) vx = -vx;
		if (y + 31 > scry || y < 1) vy = -vy;
		xt += vx * 10;
		yt += vy * 10;
		x = int(xt + 0.5);
		y = int(yt + 0.5);
		BitBlt(hdc, x, y, 32, 32, memDC, 0, 0, SRCCOPY);
		ReleaseDC(hWnd, hdc);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_PLAY_BEGIN:
			SetTimer(hWnd, 1, (int)(sqrt(double(cx * cx + cy * cy)) / mod) * 10, NULL);
			xt = x;
			yt = y;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case ID_PLAY_END:
			KillTimer(hWnd, 1);
			x = cx - 16;
			y = cy - 16;
			InvalidateRect(hWnd, NULL, TRUE);
			play = false;
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		BitBlt(hdc, x, y, 32, 32, memDC, 0, 0, SRCCOPY);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		DeleteDC(memDC);
		DeleteObject(hpen);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;

}

