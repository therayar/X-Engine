#pragma once

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_syswm.h>

#include <dwmapi.h>
#include <windows.h>
#include <string>

using std::string;

class XEngineWindow
{
public:
	void CreateXEngineWindow(string windowName, int windowWidth, int windowHeight);
	void HandleXEngineWindowEvents();
	bool RecieveXEngineWindowEvents();
	void ClearXEngineWindow();
	void DestroyXEngineWindow();

	XEngineWindow();
	~XEngineWindow();

	SDL_Window* GetXEngineWindow();

	int windowWidth, windowHeight;

private:
	SDL_Window* engineWindow;
	SDL_Event engineWindowEvent;

	bool recieveEngineWindowUpdates = true;
};

