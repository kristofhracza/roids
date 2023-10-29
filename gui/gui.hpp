#pragma once

#pragma warning (disable: 4244)

#include <windows.h>
#include <tchar.h>
#include <vector>
#include <CommCtrl.h>

#include "../injector/injector.hpp"

#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif

inline namespace global {
	inline HWND textBoxWindow;
	inline HFONT titleFont = CreateFont(35, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Calibri");
	inline HFONT normalFont = CreateFont(20, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Calibri");
}


LRESULT Wndproc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

class GUI {
public:
	static const int width = 300;
	static const int height = 300;
	
	HINSTANCE hInstance;
	int nCmdShow;
	HWND hWnd;
	
	static HWND textBox;

	static constexpr TCHAR szWindowClass[] = _T("Roids");
	static constexpr TCHAR szTitle[] = _T("Roids DLL Injector");
	HBRUSH bgColour = CreateSolidBrush(RGB(30, 30, 30));

	WNDCLASSEX createWindowClass();
	HWND createWindow();
	void update();

	static const wchar_t* filePrompt(HWND hWnd_);
	static const wchar_t* getPidText();
};