#include<Windows.h> // хедер с основными функциями Win api
#include<tchar.h> // хедер с типом TCHAR, включающий функции для работы с разной кодировкой
#include "menudemo.h" // хедер, в котором объявлены замены индефекаторов со слов на цифры

HBRUSH hBlueBrush, hYellowBrush; // глобальное объявление синей и жёлтой кисточки

LRESULT CALLBACK WndProc(
	HWND, // дескритор от главного окна
	UINT, // структура MSG от главного окна
	WPARAM, // доп данные от главного окна
	LPARAM); // доп данные от главного окна

int WINAPI WinMain( // объявление главного окна
	HINSTANCE hInstance, //Дескриптор текущего приложения
	HINSTANCE hPrevInstance, //Дескриптор предыдущего приложения
	LPSTR lpCmdLine, //Командная строка
	int nCmdShow) { //Режим отображения окна

	MSG msg; //Структура для хранения сообщения
	HWND hMainWnd; //Дескриптор главного окна программы
	TCHAR szClassName[] = _T("menudemo"); // переменная с именем класса окна
	WNDCLASSEX wc; //Класс окна

	wc.cbSize = sizeof(wc); // размер класса
	wc.style = CS_HREDRAW | CS_VREDRAW; //Стиль окна
	wc.lpfnWndProc = WndProc; // Процедура класса окна
	wc.cbClsExtra = 0; // дополнительные
	wc.cbWndExtra = 0; // данные
	wc.hInstance = hInstance; // дескриптор класса
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); //Стандартная иконка
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); //Стандартный курсор
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //
	wc.lpszMenuName = _T("menudemo"); // Имя меню
	wc.lpszClassName = szClassName; //Имя класса окна
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION); // Стандартная маленькая иконка

	if (!RegisterClassExW(&wc)) { // проверка на то, зарегистрировался ли класс
		MessageBoxW(NULL, _T("Cannot registr class"), _T("Error"), MB_OK); // если класс не зарегестрирован, то вывод сообщения об ошибки
		return 0; // завершение программы
	} 
	hMainWnd = CreateWindow( // создание главного окна
		szClassName, // имя главного окна
		_T("menudemo"), // Заголовок главного окна 
		WS_OVERLAPPEDWINDOW, //Стиль окна
		CW_USEDEFAULT, //x
		CW_USEDEFAULT, //y Размеры окна
		CW_USEDEFAULT, //Width
		CW_USEDEFAULT, //Height
		NULL, //Дескриптор родительской информации нет
		NULL, //Нет меню
		hInstance, // Дескриптор приложения
		NULL); //Дополнительной информации нет
 
	if (!hMainWnd) { //проверка на то, создалось ли окно
		MessageBox(NULL, _T("Cannot create main window"), _T("Error"), MB_OK); //если не создалось, вывод сообщения об ошибки
		return 0; //завершение программы
	} 

	ShowWindow(hMainWnd, nCmdShow); //Показать окно
	while (GetMessage(&msg, NULL, 0, 0)) { //Процесс приёма сообщений
		TranslateMessage(&msg); //Функция трансляции кодов нажатой клавиши
		DispatchMessageW(&msg); //Посылает сообщение функции WndProc()
	} 
	return 0; 
} 
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) { //
	HMENU hMenu; // объявления меню
	static int iColorID[5] = { WHITE_BRUSH, LTGRAY_BRUSH, GRAY_BRUSH,
		DKGRAY_BRUSH, BLACK_BRUSH }; // объявления цветов, на которые будет меняться фон при выборе пунктов меню
	static int iSelection = IDM_WHITE; //Стандартный цвет, использующийся для вычесления выбранного цвета
	switch (uMsg) { // switch для правильно обработки сообщения
	case WM_COMMAND: // case, вызванный выбором пункта меню
		hMenu = GetMenu(hWnd); // получения контекста меню
		switch (LOWORD(wParam)) // switch, для правильной обработки сообщения, полученного от меню
		{ 
		case IDM_NEW: 
		case IDM_OPEN: 
		case IDM_SAVE: 
		case IDM_SAVEAS: // ряд case, которые имеют одинаковый функционал
			MessageBeep(0); // функция для воспроизведения звука
			return 0; 
		case IDM_EXIT: // Сообщение от меню о закрытии главного окна
			SendMessage(hWnd, WM_CLOSE, 0, 0L); // Функция для отправки сообщения о закрытии главного окна
			return 0; 
		case IDM_UNDO: 
		case IDM_CUT: 
		case IDM_COPY:
		case IDM_PASTE: 
		case IDM_DEL: // ряд case, которые имеют одинаковый функционал
			MessageBeep(0); // функция для воспроизведения звука
			return 0; 
		case IDM_WHITE: 
		case IDM_LTGRAY: 
		case IDM_GRAY: 
		case IDM_DKGRAY: 
		case IDM_BLACK: // ряд case, которые имеют одинаковый функционал
			CheckMenuItem(hMenu, iSelection, MF_UNCHECKED); // задание пердыдущего пункта меню цвета как не отмеченного
			iSelection = LOWORD(wParam); // выбор нового пункта меню цвета
			CheckMenuItem(hMenu, iSelection, MF_CHECKED); // задание новго пункта меню цвета как отмеченного
			SetClassLong(hWnd, GCL_HBRBACKGROUND, (LONG)GetStockObject(iColorID[LOWORD(wParam) - IDM_WHITE])); //Задача заднего фона по вычислению стандартного цвета из выбранного пункта меню 
			InvalidateRect(hWnd, NULL, TRUE); // Стерание рабочей области
			return 0; 
		case IDM_START: // сообщение об запуске таймера
			if (SetTimer(hWnd, 1, 1000, NULL)) // проверка на существование таймера и одновременный его запуск
			{ 
				EnableMenuItem(hMenu, IDM_START, MF_GRAYED); // задача пунка меню запуска таймера как недоступного
				EnableMenuItem(hMenu, IDM_STOP, MF_ENABLED); // задача пункта меню остановки таймера как доступного
			} 
			return 0; 
		case IDM_STOP: // сообщение об остановке таймера
			KillTimer(hWnd, 1); // остановка таймера
			EnableMenuItem(hMenu, IDM_START, MF_ENABLED); // задача пунка меню запуска таймера как доступного
			EnableMenuItem(hMenu, IDM_STOP, MF_GRAYED); // задача пункта меню остановки таймера как недоступного
			return 0; 
		case IDM_HELP: // сообщение об открытии документации или средства обратной свзяи
			MessageBox(hWnd, _T("No Help"), _T("menudemo"), MB_ICONEXCLAMATION | MB_OK); // диалоговое окно для пункта help
			return 0; 
		case IDM_ABOUT: // сообщение об открытии дополнительной информации о программе
			MessageBox(hWnd, _T("Menu Demonstration"), _T("menudemo"), MB_ICONEXCLAMATION | MB_OK); // диалоговое окно для пункта about
			return 0; 
		} 
		break; 
	case WM_DESTROY: // сообщение об завершении работы программы
		PostQuitMessage(0); // Функция для завершения работы программы
		break; 
	default: // все не специфицированные сообщения
		return DefWindowProc(hWnd, uMsg, wParam, lParam); // функция обработки всех стандартных сообщений
	} 
	return 0; 
	 
} 
