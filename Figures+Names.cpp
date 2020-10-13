#include<Windows.h>
#include<windowsx.h>
#include<tchar.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HPEN hRedPen, hGreenPen, hBluePen, hOrangePen;
HBRUSH hRedBrush, hGreenBrush, hBlueBrush, hGoldBrush;
POINT pt[6] = { {550,40},{575,140},{500,75}, {600,75}, {525,140}, {550,40} };
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
	TCHAR szText1[] = _T("Rectangle( )");
	TCHAR szText2[] = _T("Ellipse( )");
	TCHAR szText3[] = _T("Pie( )");
	TCHAR szText4[] = _T("Chord( )");
	TCHAR szText5[] = _T("Бурыкин Алексей");
	switch (uMsg) {
	case WM_CREATE:
		hRedPen = CreatePen(PS_SOLID, 4, RGB(150, 0, 0));
		hGreenPen = CreatePen(PS_SOLID, 10, RGB(0, 150, 0));
		hBluePen = CreatePen(PS_SOLID, 20, RGB(0, 0, 150));
		hOrangePen = CreatePen(PS_SOLID, 10, RGB(255, 165, 0));
		hRedBrush = CreateSolidBrush(RGB(255, 120, 120));
		hGreenBrush = CreateSolidBrush(RGB(120, 255, 120));
		hBlueBrush = CreateSolidBrush(RGB(120, 120, 255));
		hGoldBrush = CreateSolidBrush(RGB(255, 255, 0));
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		SetBkColor(hdc, RGB(200, 200, 100));
		SetTextColor(hdc, RGB(0, 0, 200));
		TextOut(hdc, 25, 5, szText1, _tcslen(szText1));
		TextOut(hdc, 155, 5, szText2, _tcslen(szText2));
		TextOut(hdc, 280, 5, szText3, _tcslen(szText3));
		TextOut(hdc, 395, 5, szText4, _tcslen(szText4));
		TextOut(hdc, 500, 5, szText5, _tcslen(szText5));
		Rectangle(hdc, 10, 40, 110, 140);
		SelectPen(hdc, hRedPen);
		SelectBrush(hdc, hRedBrush);
		Ellipse(hdc, 130, 40, 230, 140);
		SelectPen(hdc, hGreenPen);
		SelectBrush(hdc, hGreenBrush);
		Pie(hdc, 250, 40, 350, 140, 350, 140, 250, 140);
		SelectPen(hdc, hBluePen);
		SelectBrush(hdc, hBlueBrush);
		Chord(hdc, 370, 40, 470, 140, 470, 125, 370, 125);
		SelectPen(hdc, hOrangePen);
		Polyline(hdc, pt, 6);
		BeginPath(hdc);
		Polyline(hdc, pt, 5);
		CloseFigure(hdc);
		EndPath(hdc);
		SelectObject(hdc, hGoldBrush);
		SetPolyFillMode(hdc, WINDING);
		FillPath(hdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		DeleteObject(hRedPen);
		DeleteObject(hGreenPen);
		DeleteObject(hBluePen);
		DeleteObject(hRedBrush);
		DeleteObject(hGreenBrush);
		DeleteObject(hBlueBrush);
		DeleteObject(hOrangePen);
		DeleteObject(hGoldBrush);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;

}
