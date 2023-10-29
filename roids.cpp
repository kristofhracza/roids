#pragma warning (disable: 6387)

#include "injector/injector.hpp"
#include "gui/gui.hpp"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	GUI RoidsGui;
	RoidsGui.hInstance = hInstance;
	RoidsGui.nCmdShow = nCmdShow;

	RoidsGui.update();
}