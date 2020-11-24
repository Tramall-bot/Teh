#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<tchar.h>
#include<commdlg.h>
#include<CommCtrl.h>
#include<fstream>
#include"Resource.h"
TBBUTTON tbb[3] =
{ {STD_FILENEW, ID_FILE_NEW, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, 0},
{STD_FILEOPEN, ID_FILE_OPEN, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, 0},
{STD_FILESAVE, ID_FILE_SAVE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, 0}
};
HINSTANCE hInst;
VOID StatusOut(HWND hStatus, int count, TCHAR* str)
{
	TCHAR text[256];
	_stprintf(text, _T("Строк: %d"), count);
	SendMessage(hStatus, SB_SETTEXT, (WPARAM)0, (LPARAM)text);
	SendMessage(hStatus, SB_SETTEXT, (WPARAM)1, (LPARAM)str);
}
char szClassName[] = "Name";
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	HWND hWnd;
	WNDCLASS wc;
	MSG msg;
	hInst = hInstance;
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
	static OPENFILENAME file;
	static int n, sx, sy;
	static HWND hEdit, hWndToolBar, hWndStatusBar;
	RECT rt;
	int m, k, aWidths[2];
	static TCHAR name[256] = _T("    ");
	char szText[0x7fff];
	std::ifstream in;
	std::ofstream out;
	TCHAR str0[] = _T("Файл");
	TCHAR str1[] = _T("Новый");
	TCHAR str2[] = _T("Открыть");
	TCHAR str3[] = _T("Сохранить");
	TCHAR str4[] = _T("Выход");
	HMENU hMenu;
	HMENU hPopupMenu;
	switch (uMsg) {
	case WM_CREATE:
		hMenu = CreateMenu();
		hPopupMenu = CreatePopupMenu();
		AppendMenu(hPopupMenu, MF_STRING, ID_FILE_NEW, str1);
		AppendMenu(hPopupMenu, MF_STRING, ID_FILE_OPEN, str2);
		AppendMenu(hPopupMenu, MF_STRING, ID_FILE_SAVE, str3);
		AppendMenu(hPopupMenu, MF_STRING, IDM_EXIT, str4);
		AppendMenu(hMenu, MF_POPUP, (UINT)hPopupMenu, str0);
		SetMenu(hWnd, hMenu);
		hWndToolBar = CreateToolbarEx(hWnd, WS_CHILD | WS_VISIBLE | CCS_TOP, 2, 0, HINST_COMMCTRL, IDB_STD_SMALL_COLOR, tbb, 3, 0, 0, 0, 0, sizeof(TBBUTTON));
		hEdit = CreateWindow(WC_EDIT, NULL, WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_AUTOHSCROLL | ES_AUTOVSCROLL, 0, 0, 0, 0, hWnd, (HMENU) 1, hInst, NULL);
		file.lStructSize = sizeof(OPENFILENAME);
		file.hInstance = hInst;
		file.lpstrFilter = _T("Text\0*.txt\0Все файлы\0*.*");
		file.lpstrFile = name;
		file.nMaxFile = 256;
		file.lpstrInitialDir = _T(".\\");
		file.lpstrDefExt = _T("txt");
		hWndStatusBar = CreateWindow(STATUSCLASSNAME, NULL, WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, hWnd, NULL, hInst, NULL);
		break;
	case WM_SIZE:
		sx = LOWORD(lParam);
		sy = HIWORD(lParam);
		aWidths[0] = 100;
		aWidths[1] = sx;
		GetWindowRect(hWndToolBar, &rt);
		m = rt.bottom - rt.top;
		SendMessage(hWndToolBar, TB_AUTOSIZE, 0, 0);
		GetWindowRect(hWndStatusBar, &rt);
		k = rt.bottom - rt.top;
		MoveWindow(hWndStatusBar, 0, sy - k, sx, sy, TRUE);
		SendMessage(hWndStatusBar, SB_SETPARTS, (WPARAM)2, (LPARAM)aWidths);
		StatusOut(hWndStatusBar, n, name);
		MoveWindow(hEdit, 0, m, sx, sy - m - k, TRUE);
		UpdateWindow(hEdit);
		SetFocus(hEdit);
		break;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case ID_FILE_NEW:
			szText[0] = '\0';
			SetWindowTextA(hEdit, szText);
			StatusOut(hWndStatusBar, 0, name);
			break;
		case ID_FILE_OPEN:
			file.lpstrTitle = _T("Открыть файл для чтения");
			file.Flags = OFN_HIDEREADONLY;
			if (!GetOpenFileName(&file)) return 1;
			in.open(name, std::ios::binary);
			in.read(szText, 0x7fff);
			if ((m = in.gcount()) == 0x7fff)
			{
				MessageBox(hWnd, _T("Слишком большой файл"), _T("Edit"), MB_OK | MB_ICONSTOP);
				in.close();
				return 0;
			}
			szText[m] = '\0';
			in.close();
			SetWindowTextA(hEdit, szText);
			n = SendMessage(hEdit, EM_GETLINECOUNT, 0, 0);
			StatusOut(hWndStatusBar, n, name);
			break;
		case ID_FILE_SAVE:
			file.lpstrTitle = _T("Открыть файл для записи");
			file.Flags = OFN_NOTESTFILECREATE | OFN_HIDEREADONLY;
			if (!GetSaveFileName(&file)) return 1;
			out.open(name, std::ios::binary);
			m = GetWindowTextA(hEdit, szText, 0x7fff);
			out.write(szText, m);
			out.close();
			n = SendMessage(hEdit, EM_GETLINECOUNT, 0, 0);
			StatusOut(hWndStatusBar, n, name);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
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

