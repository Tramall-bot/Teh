#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<tchar.h>
#include"Resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
static int radio, check1, check2, scrlh, scrlv, lIndex, cIndex;
int* val[] = { &radio, &check1, &check2, &scrlh, &scrlv, &lIndex, &cIndex };
LPCWSTR combo[] = { _T("aa"),_T("bb"),_T("cc") };
LPCWSTR list[] = { _T("string 1"), _T("string 2"), _T("string 3") };
LPCWSTR ctrl = _T("Элементы управления :");
LPCWSTR str_control[] = { _T("Radio Button"), _T("Check Button 1"), _T("Check Button 2"), _T("HScroll Pos"), _T("VScroll Pos"), _T("List Box Index"),_T("Comb Box Index") };
const int HNUM = 10, VNUM = 100;
const int List_size = 3, Combo_size = 3;
const int INTERVAL = 20;
INT_PTR CALLBACK Dialog1(HWND, UINT, WPARAM, LPARAM);
TCHAR szAppName[] = _T("BigDialog");
HINSTANCE hInst;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	HWND hWnd;
	WNDCLASSEX wc;
	MSG lpMsg;
	hInst = hInstance;
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW +1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szAppName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	if (!RegisterClassEx(&wc)) return 0;
	hWnd = CreateWindow(szAppName, _T("Демонстрация списков"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, (HWND)NULL, (HMENU)NULL,
		hInstance, (LPSTR)NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&lpMsg, NULL, 0, 0)) {
		TranslateMessage(&lpMsg);
		DispatchMessageW(&lpMsg);
	}
	return (int)lpMsg.wParam;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR str[256];
	int i;
	HMENU hMenu, hPopupMenu;
	TCHAR str0[] = _T("Диалог");
	TCHAR str1[] = _T("Открыть");
	switch (msg)
	{
	case WM_CREATE:
		hMenu = CreateMenu();
		hPopupMenu = CreatePopupMenu();
		AppendMenu(hPopupMenu, MF_STRING, ID_STDDIALOG, str1);
		AppendMenu(hMenu, MF_POPUP, (UINT)hPopupMenu, str0);
		SetMenu(hwnd, hMenu);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_STDDIALOG:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hwnd, Dialog1);
			break;
		case IDM_EXIT:
			DestroyWindow(hwnd);
			break;
		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		TextOut(hdc, 0, 0, ctrl, _tcslen(ctrl));
		for ( i = 0; i < 7;)
		{
			_stprintf(str, _T("%s = %d"), str_control[i], *val[i]);
			TextOut(hdc, 0, ++i * INTERVAL, str, _tcslen(str));
		}
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

INT_PTR CALLBACK Dialog1(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static int radio, check1, check2, scrlh, scrlv;
	static HWND hScroll, vScroll, hWndList, hWndComboBox;
	int i;
	switch (msg)
	{
	case WM_INITDIALOG:
		radio = ::radio;
		CheckRadioButton(hDlg, IDC_RADIO1, IDC_RADIO3, IDC_RADIO1 + radio);
		check1 = ::check1;
		SendDlgItemMessage(hDlg, IDC_CHECK1, BM_SETCHECK, check1, 0);
		check2 = ::check2;
		SendDlgItemMessage(hDlg, IDC_CHECK2, BM_SETCHECK, check2, 0);

		scrlh = ::scrlh;
		SetDlgItemInt(hDlg, IDC_HSCR, scrlh, 0);
		hScroll = GetDlgItem(hDlg, IDC_SCROLLBAR2);
		SetScrollRange(hScroll, SB_CTL, 0, HNUM, FALSE);
		SetScrollPos(hScroll, SB_CTL, scrlh, TRUE);

		scrlv = ::scrlv;
		SetDlgItemInt(hDlg, IDC_VSCR, scrlv, 0);
		vScroll = GetDlgItem(hDlg, IDC_SCROLLBAR1);
		SetScrollRange(vScroll, SB_CTL, 0, VNUM, FALSE);
		SetScrollPos(vScroll, SB_CTL, scrlv, TRUE);

		hWndList = GetDlgItem(hDlg, IDC_LIST1);
		for ( i = 0; i < List_size; i++)
		{
			SendMessage(hWndList, LB_ADDSTRING, 0, (LPARAM)list[i]);
		}
		SendMessage(hWndList, LB_SETCURSEL, lIndex, 0);
		hWndComboBox = GetDlgItem(hDlg, IDC_COMBO1);
		for ( i = 0; i < Combo_size; i++)
		{
			SendMessage(hWndComboBox, CB_ADDSTRING, 0, (LPARAM)combo[i]);
		}
		SendMessage(hWndComboBox, CB_SETCURSEL, cIndex, 0);
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			lIndex = SendMessage(hWndList, LB_GETCURSEL, 0, 0);
			cIndex = SendMessage(hWndComboBox, CB_GETCURSEL, 0, 0);
			::radio = radio;
			::check1 = check1;
			::check2 = check2;
			::scrlh = scrlh;
			::scrlv = scrlv;
			InvalidateRect(GetParent(hDlg), NULL, TRUE);
		case IDCANCEL:
			return EndDialog(hDlg, 0);
		case IDC_CHECK1:
			check1 = ~check1;
			SendDlgItemMessage(hDlg, IDC_CHECK1, BM_SETCHECK, check1, 0);
			return TRUE;
		case IDC_CHECK2:
			check2 = ~check2;
			SendDlgItemMessage(hDlg, IDC_CHECK2, BM_SETCHECK, check2, 0);
			return TRUE;
		case IDC_RADIO1:
			radio = 0;
			break;
		case IDC_RADIO2:
			radio = 1;
			break;
		case IDC_RADIO3:
			radio = 2;
			break;
		}
		CheckRadioButton(hDlg, IDC_RADIO1, IDC_RADIO3, IDC_RADIO1 + radio);
		return TRUE;
	case WM_HSCROLL:
		switch (LOWORD(wParam))
		{
		case SB_LINELEFT:
			scrlh--;
			break;
		case SB_LINERIGHT:
			scrlh++;
			break;
		case SB_PAGELEFT:
			scrlh -= HNUM / 2;
			break;
		case SB_PAGERIGHT:
			scrlh += HNUM / 2;
			break;
		case SB_THUMBTRACK:
		case SB_THUMBPOSITION:
			scrlh = HIWORD(wParam);
			break;
		}
		scrlh = max(0, min(scrlh, HNUM));
		if (scrlh != GetScrollPos(hScroll, SB_CTL)) {
			SetScrollPos(hScroll, SB_CTL, scrlh, TRUE);
			SetDlgItemInt(hDlg, IDC_HSCR, scrlh, 0);
		}
		return TRUE;
	case WM_VSCROLL:
		switch (LOWORD(wParam))
		{
		case SB_LINEUP:
			scrlv--;
			break;
		case SB_LINEDOWN:
			scrlv++;
			break;
		case SB_PAGEUP:
			scrlv -= VNUM / 10;
			break;
		case SB_PAGEDOWN:
			scrlv += VNUM / 10;
			break;
		case SB_THUMBTRACK:
		case SB_THUMBPOSITION:
			scrlv = HIWORD(wParam);
			break;
		}
		scrlv = max(0, min(scrlv, VNUM));
		if (scrlv != GetScrollPos(vScroll, SB_CTL)) {
			SetScrollPos(vScroll, SB_CTL, scrlv, TRUE);
			SetDlgItemInt(hDlg, IDC_VSCR, scrlv, 0);
		}
		return TRUE;
	default:
		return FALSE;
	}
	return FALSE;
}
