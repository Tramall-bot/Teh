#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<tchar.h>
#include<commdlg.h>
#include<CommCtrl.h>
#include<fstream>
#include"Resource.h"

const DWORD MaxLength = 0x7fff;
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
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&wc);
	hWnd = CreateWindow(szClassName, szClassName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL,
		hInstance, NULL);
	if (!SetTimer(hWnd, 1, 50, NULL))
		return FALSE;
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	return msg.wParam;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;
	HDC hdc;
	static TCHAR name[256] = _T("");
	static OPENFILENAME file;
	DWORD result;
	static HANDLE hFile;
	static char text[MaxLength];
	static int sx, sy;
	static DWORD nCharRead;
	RECT rt;
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
		file.lStructSize = sizeof(OPENFILENAME);
		file.hInstance = hInst;
		file.lpstrFilter = _T("Text\0*.txt\0Все файлы\0*.*");
		file.lpstrFile = name;
		file.nMaxFile = 256;
		file.lpstrInitialDir = _T(".\\");
		file.lpstrDefExt = _T("txt");
		break;
	case WM_SIZE:
		sx = LOWORD(lParam);
		sy = HIWORD(lParam);
		break;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case ID_FILE_NEW:
			nCharRead = 0;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case ID_FILE_OPEN:
			file.lpstrTitle = _T("Открыть файл для чтения");
			file.Flags = OFN_HIDEREADONLY;
			if (!GetOpenFileName(&file)) return 1;
			hFile = CreateFile(name, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			ReadFile(hFile, text, MaxLength, &nCharRead, NULL);
			CloseHandle(hFile);
			if (nCharRead == MaxLength)
			{
				MessageBox(hWnd, _T("Слишком большой файл"), _T("Неудачное открытие файла"), MB_YESNO | MB_ICONHAND);
				return 0;
			}
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case ID_FILE_SAVE:
			file.lpstrTitle = _T("Открыть файл для записи");
			file.Flags = OFN_NOTESTFILECREATE;
			if (!GetSaveFileName(&file)) return 1;
			hFile = CreateFile(name, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			WriteFile(hFile, text, nCharRead, &result, NULL);
			CloseHandle(hFile);
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
		SetRect(&rt, 0, 0, sx, sy);
		DrawText(hdc, text, nCharRead, &rt, DT_LEFT);
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

