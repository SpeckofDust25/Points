#include <Windows.h>
#include "PointWindow.h"

#ifndef UNICODE
#define UNICODE
#endif

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow) {

	Orange::PointWindow* point_window = new Orange::PointWindow(L"Main Window", L"DesktopApplication", hInstance, nCmdShow);
	point_window->CreateMainWindow(400, 100, CW_USEDEFAULT, CW_USEDEFAULT);
	point_window->SetBackgroundColor(RGB(0, 0, 0));

	//Main Message Loop
	MSG msg;
	while (GetMessageW(&msg, NULL, 0, 0) > 0) {
		TranslateMessage(&msg);	//Translates Keystrokes
		DispatchMessage(&msg);	//Tells the operating system to call the window procedure of the window that is the target of the message
	}

	delete point_window;
	return (int)msg.wParam;
}