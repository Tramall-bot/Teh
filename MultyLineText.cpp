#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<tchar.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
TCHAR text[] = _T("Текст для вывода в окне");
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	HWND hMainWnd;
	TCHAR szClassName[] = _T("MyClass");
	MSG msg;
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
	wc.lpszClassName = szClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	if (!RegisterClassExW(&wc)) {
		MessageBoxW(NULL, _T("Cannot registr class"), _T("Error"), MB_OK);
		return 0;
	}
	hMainWnd = CreateWindow(szClassName, _T("A Hello1 Application"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL,
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
	SIZE size;
	TEXTMETRIC tm;
	RECT rt;
	TCHAR str[256];
	switch (uMsg) {
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		SetBkColor(hdc, RGB(255, 255, 0));
		SetTextColor(hdc, RGB(0, 0, 128));
		TextOut(hdc, 0, 0, text, _tcslen(text));
		SetBkMode(hdc, TRANSPARENT);
		SelectObject(hdc, GetStockObject(ANSI_VAR_FONT));
		GetTextMetrics(hdc, &tm);
		_stprintf(str, _T("tmHeight = %d\ntmInternalLeading = %d\n\
			emExternalLeading = %d\ntmAscent = %d\ntmDescent = %d\n"),
			tm.tmHeight, tm.tmInternalLeading, tm.tmExternalLeading,
			tm.tmAscent, tm.tmDescent);
		SetRect(&rt, 0, 20, 150, 100);
		DrawText(hdc, str, _tcslen(str), &rt, DT_LEFT);
		GetTextExtentPoint32(hdc, text, _tcslen(text), &size);
		_stprintf(str, _T("Ширина строки = %d\nВысота строки = %d"), size.cx, size.cy);
		SetRect(&rt, 0, 100, 150, 150);
		DrawText(hdc, str, _tcslen(str), &rt, DT_LEFT);

		SelectObject(hdc, GetStockObject(ANSI_FIXED_FONT));
		SetBkMode(hdc, OPAQUE);
		SetTextColor(hdc, RGB(255, 0, 0));
		SetBkColor(hdc, RGB(0, 0, 255));
		TextOut(hdc, 0, 140, _T("Бурыкин Алексей ANSI_FIXED_FONT"), 31);

		SelectObject(hdc, GetStockObject(DEVICE_DEFAULT_FONT));
		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, RGB(0, 255, 0));
		SetBkColor(hdc, RGB(0, 0, 255));
		TextOut(hdc, 0, 155, _T("Бурыкин Алексей DEVICE_DEFAULT_FONT"), 35);

		SelectObject(hdc, GetStockObject(DEFAULT_GUI_FONT));
		SetBkMode(hdc, OPAQUE);
		SetTextColor(hdc, RGB(0, 0, 255));
		SetBkColor(hdc, RGB(255, 0, 0));
		TextOut(hdc, 0, 180, _T("Бурыкин Алексей DEFAULT_GUI_FONT"), 32);

		SelectObject(hdc, GetStockObject(SYSTEM_FIXED_FONT));
		SetBkMode(hdc, OPAQUE);
		SetTextColor(hdc, RGB(0, 255, 0));
		SetBkColor(hdc, RGB(255, 0, 255));
		TextOut(hdc, 0, 195, _T("Бурыкин Алексей SYSTEM_FIXED_FONT"), 33);

		SelectObject(hdc, GetStockObject(SYSTEM_FONT));
		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, RGB(255, 0, 0));
		SetBkColor(hdc, RGB(0, 0, 255));
		TextOut(hdc, 0, 210, _T("Бурыкин Алексей SYSTEM_FONT"), 27);

		SelectObject(hdc, GetStockObject(ANSI_VAR_FONT));
		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, RGB(128, 0, 128));
		SetBkColor(hdc, RGB(0, 0, 255));
		TextOut(hdc, 0, 230, _T("Бурыкин Алексей ANSI_VAR_FONT"), 29);

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
