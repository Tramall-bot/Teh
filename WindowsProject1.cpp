#include <windows.h>
#include <tchar.h>

/*
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	MessageBox(NULL, L"Hello, Win32 world!", L"Hello from Message Box", MB_OK);
	return 0;
}
*/

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
TCHAR WinName[] = _T("MainFrame");
int APIENTRY _tWinMain(HINSTANCE This, // Дескрипотор текущего приложения
	HINSTANCE Prev, // В современных системах всегда 0
	LPTSTR cmd, // Командная строка
	int mode) // Режим отображения окна
{
	HWND hWnd; // Дескриптор главного окна программы
	MSG msg; // Структура для хранения сообщения
	WNDCLASS wc; // Класс окна
	wc.hInstance = This; // Определение класса окна
	wc.lpszClassName = WinName; // Имя класса окна
	wc.lpfnWndProc = WndProc; // Функция окна
	wc.style = CS_HREDRAW | CS_VREDRAW; // Стиль окна
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); // Стандартная икона
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); // Стандартный курсор
	wc.lpszMenuName = NULL; // Нет меню
	wc.cbClsExtra = 0; // Нет дополнительных данных класса
	wc.cbWndExtra = 0; // Нет дополнительных данных окна
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	if (!RegisterClass(&wc)) return 0; // Регистрация класса окна
	// Создание окна
	hWnd = CreateWindow(WinName, // Имя класса окна
		_T("Каркас приложения"), // Заголовок окна
		WS_OVERLAPPEDWINDOW, // Стиль окна
		CW_USEDEFAULT, // х
		CW_USEDEFAULT, // у
		CW_USEDEFAULT, // Width
		CW_USEDEFAULT, // Height
		HWND_DESKTOP, // Дескрипт приложения
		NULL, // Нет меню
		This, // Дескриптор приложения
		NULL); // Дополнительной информации нет
	ShowWindow(hWnd, mode); // Показать окно
	// Цикл обработки сообщений
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg); // Функция трансляции кодов нажатой клавиши
		DispatchMessage(&msg); // Посылает сообщения функции WndProc
	}
	return 0;
}
// Оконная функция вызывается ОС
// и получает сообщение из очереди для данного приложения
LRESULT CALLBACK WndProc(HWND hWnd, UINT messege,
	WPARAM wParam, LPARAM lParam) { // Обработчик сообщений
	switch (messege)
	{
	case WM_DESTROY: PostQuitMessage(0);
		break; //Завершении программы
	default: return DefWindowProc(hWnd, messege, wParam, lParam);
	}
	return 0;
}
