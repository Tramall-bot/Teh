#include <windows.h>
#include <tchar.h>


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
TCHAR WinName[] = _T("MainFrame");
int APIENTRY _tWinMain(HINSTANCE This, 
	HINSTANCE Prev, 
	int mode) 
{
	HWND hWnd;
	MSG msg; 
	WNDCLASS wc; 
	wc.hInstance = This; 
	wc.lpszClassName = WinName; 
	wc.lpfnWndProc = WndProc; 
	wc.style = CS_HREDRAW | CS_VREDRAW; 
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); 
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); 
	wc.lpszMenuName = NULL; 
	wc.cbClsExtra = 0; 
	wc.cbWndExtra = 0; 
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	if (!RegisterClass(&wc)) return 0; 
	hWnd = CreateWindow(WinName, 
		_T("Каркас приложения"), 
		WS_OVERLAPPEDWINDOW, 
		CW_USEDEFAULT, 
		CW_USEDEFAULT, 
		CW_USEDEFAULT,
		CW_USEDEFAULT, 
		HWND_DESKTOP, 
		NULL, 
		This, 
		NULL); 
	ShowWindow(hWnd, mode); 
	
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg); 
		DispatchMessage(&msg); 
	}
	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT messege,
	WPARAM wParam, LPARAM lParam) { 
	switch (messege)
	{
	case WM_DESTROY: PostQuitMessage(0);
		break; 
	default: return DefWindowProc(hWnd, messege, wParam, lParam);
	}
	return 0;
}
