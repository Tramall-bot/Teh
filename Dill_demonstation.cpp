#include<Windows.h>
#include<tchar.h>

WINGDIAPI BOOL WINAPI Triangle(HDC, POINT*);

char szClassName[] = "Name";
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	HWND hWnd;
	WNDCLASS wc;
	MSG msg;
	wc.hInstance = hInstance;
	wc.lpszClassName = szClassName;
	wc.lpfnWndProc = WndProc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszMenuName = NULL;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	if (!RegisterClass(&wc)) return 0;
	hWnd = CreateWindow(szClassName, _T("Каркас"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, HWND_DESKTOP, NULL,
		hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	return 0;

}
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;
	HDC hdc;
	static HPEN hPen;
	static int sx, sy;
	POINT pt[3];
	switch (uMsg) {
	case WM_CREATE:
		hPen = CreatePen(PS_SOLID, 4, RGB(0, 0, 255));
		break;
	case WM_SIZE:
		sx = LOWORD(lParam);
		sy = HIWORD(lParam);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		SelectObject(hdc, hPen);
		pt[0].x = sx / 4;
		pt[0].y = pt[1].y = sy / 4;
		pt[1].x = 3 * sx / 4;
		pt[2].x = sx / 2;
		pt[2].y = sy / 2;
		Triangle(hdc, pt);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		DeleteObject(hPen);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;

}

