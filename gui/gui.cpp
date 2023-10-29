#include "gui.hpp"

LRESULT Wndproc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	HWND status = NULL;

	switch (msg) {
		case WM_DESTROY: {
			PostQuitMessage(0);
			return 0;
		}
		case WM_COMMAND: {
			switch (LOWORD(wParam)) {
				case 1: {
					const wchar_t* filePath = GUI::filePrompt(hWnd);
					DLLInjectorParams::fileName = filePath;
				
					int id = wcstol(GUI::getPidText(), 0, 10);
					bool success = DLLInjector::loadDLL(id);

					if (success) {
						status = CreateWindow(L"STATIC", L"Injection succesful", WS_VISIBLE | WS_CHILD | SS_CENTER | SS_CENTERIMAGE, 0, 100, GUI::width, 50, hWnd, NULL, NULL, NULL);
					}
					else {
						status = CreateWindow(L"STATIC", L"Injection failed", WS_VISIBLE | WS_CHILD | SS_CENTER | SS_CENTERIMAGE, 0, 100, GUI::width, 50, hWnd, NULL, NULL, NULL);
					}
					SendMessage(status, WM_SETFONT, WPARAM(global::normalFont), TRUE);
					break;
				}
			}
		}
		case WM_CTLCOLORSTATIC:{
			HDC hdcStatic = (HDC)wParam;
			
			SetTextColor(hdcStatic, RGB(2, 137, 255));
			SetBkColor(hdcStatic, RGB(30, 30, 30));

			return (LRESULT)GetStockObject(NULL_BRUSH);
			break;
		}
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

WNDCLASSEX GUI::createWindowClass() {
	WNDCLASSEX wcex{ };

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = Wndproc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = bgColour;
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);
	RegisterClassEx(&wcex);

	return wcex;
}


HWND GUI::createWindow() {
	createWindowClass();
	HWND hWnd = CreateWindowEx(WS_EX_CLIENTEDGE,szWindowClass,szTitle,WS_OVERLAPPED | WS_VISIBLE | WS_SYSMENU | WS_CAPTION,CW_USEDEFAULT, CW_USEDEFAULT,width, height,NULL,NULL,hInstance,NULL);

	HWND title = CreateWindow(L"STATIC", L"Roids", WS_VISIBLE | WS_CHILD | SS_CENTER | SS_CENTERIMAGE, 0, 10, width, 50, hWnd, NULL, NULL, NULL);

	HWND status = CreateWindow(L"STATIC", L"Status:", WS_VISIBLE | WS_CHILD | SS_CENTER | SS_CENTERIMAGE, 0, 100, GUI::width, 20, hWnd, NULL, NULL, NULL);
	HWND button = CreateWindow(L"BUTTON", L"Inject DLL", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_FLAT, 5, (height - 85), 100, 40, hWnd, (HMENU)1, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
	global::textBoxWindow = CreateWindow(L"EDIT", L"", WS_BORDER | WS_CHILD | WS_VISIBLE,width - 125, (height - 70), 100, 20, hWnd, (HMENU)2, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);


	SendMessage(title, WM_SETFONT, WPARAM(global::titleFont), TRUE);
	SendMessage(status, WM_SETFONT, WPARAM(global::normalFont), TRUE);
	SendMessage(button, WM_SETFONT, WPARAM(global::normalFont), TRUE);
	SendMessage(global::textBoxWindow, WM_SETFONT, WPARAM(global::normalFont), TRUE);

	return hWnd;
}

void GUI::update() {
	hWnd = createWindow();
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}


const wchar_t* GUI::filePrompt(HWND hWnd_) {
	LPWSTR filebuff = new wchar_t[MAX_PATH];

	OPENFILENAME open = { 0 };
	open.lStructSize = sizeof(OPENFILENAME);
	open.hwndOwner = hWnd_;
	open.lpstrFilter = L"Image Files(.dll)\0*.dll;\0\0";
	open.lpstrCustomFilter = NULL;
	open.lpstrFile = filebuff;
	open.lpstrFile[0] = '\0';
	open.nMaxFile = MAX_PATH;
	open.nFilterIndex = 1;
	open.lpstrInitialDir = NULL;
	open.lpstrTitle = L"Select DLL\0";
	open.nMaxFileTitle = (DWORD)wcslen(open.lpstrTitle);
	open.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER;

	if (GetOpenFileName(&open)){
		return open.lpstrFile;
	}

	return 0;
}


const wchar_t* GUI::getPidText() {
	wchar_t buff[MAX_PATH];
	GetWindowText(global::textBoxWindow, buff, MAX_PATH);
	return buff;
}
