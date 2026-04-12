#include "Application.h"

#include <cstddef>

using namespace GameEngine;

Application::Application() {
	HINSTANCE hInstance = GetModuleHandle(NULL);
	WNDCLASS wc = { };

	//wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = L"Window Test";

	RegisterClass(&wc);
	HWND hwnd = CreateWindowEx(
		0,
		L"Window Test",
		L"learn you moron",
		WS_OVERLAPPEDWINDOW,
		5, 5, 200, 200,
		NULL, NULL, hInstance, NULL);

	if (hwnd == NULL) {
		return;
	}

	ShowWindow(hwnd, 0);
}
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}