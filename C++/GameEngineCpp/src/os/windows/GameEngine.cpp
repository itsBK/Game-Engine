// GameEngineCpp.cpp : Defines the entry point for the application.
//
// #include <numbers>
// #include "GameEngineCpp.h"
// #include "Application.cpp"
// 
// using namespace std;
// using namespace GameEngine::Math;
// 
// int main()
// {
// 	GameEngine::Application::getInstance();
// 	/*
// 	Vector3 vec1(0, 0, 4);
// 	double angle = std::numbers::pi / 2;
// 	Vector3 vec2 = Matrix3x3::rotate(angle, 0, angle) * vec1;
// 
// 	cout << "Vector3(" << vec1.x << ", "
// 		<< vec1.y << ", " << vec1.z << ")." << endl;
// 	cout << "Vector3(" << vec2.x << ", "
// 		<< vec2.y << ", " << vec2.z << ")." << endl;
// 	*/
// 
// 	return 0;
// }
#ifndef UNICODE
#define UNICODE
#endif

#include <iostream>
#include <windows.h>

LRESULT CALLBACK WindowProcedure(HWND window, unsigned int msg, WPARAM wp, LPARAM lp)
{
	return DefWindowProc(window, msg, wp, lp);
}

int main()
{
	const wchar_t CLASS_NAME[] = L"Sample Window Class";

	WNDCLASSEX wcex;
	HINSTANCE hInstance = GetModuleHandle(NULL);

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WindowProcedure;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = CLASS_NAME;
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			L"Call to RegisterClassEx failed!",
			L"Can't create class",
			NULL);

		return 1;
	}

	// Create the window.

	HWND hwnd = CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW,                              // Optional window styles.
		CLASS_NAME,                     // Window class
		L"Learn to Program Windows",    // Window text
		WS_OVERLAPPEDWINDOW,            // Window style

		// Size and position
		CW_USEDEFAULT, CW_USEDEFAULT,
		500, 100,
		NULL,       // Parent window    
		NULL,       // Menu
		hInstance,  // Instance handle
		NULL        // Additional application data
	);

	if (!hwnd)
	{
		MessageBox(NULL,
			L"Call to CreateWindow failed!",
			L"Can't create window",
			NULL);

		return 1;
	}

	ShowWindow(hwnd, SC_RESTORE);
	UpdateWindow(hwnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}