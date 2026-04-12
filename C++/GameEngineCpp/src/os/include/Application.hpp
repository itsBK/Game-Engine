#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

namespace GameEngine {
class Application {

private:
	Application();
	Application(const Application&) = delete;
	//void operator=(Application const&);

public:
	static Application& getInstance() {
		static Application instance;
		return instance;
	}

};

};