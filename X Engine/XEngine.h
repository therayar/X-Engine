#pragma once

#include "XEngineWindow.h"

#include <GL/glew.h>
#include <SDL.h>

class XEngine
{
public:
	void InitializeXEngine();
	void HandleXEngineWindowEvents();
	bool RecieveXEngineWindowEvents();
	void UpdateXEngine();
	void DestroyXEngine();

	XEngine();
	~XEngine();

	XEngineWindow engineWindow;

private:
	SDL_GLContext engineOpenGLContext;
	SDL_Event engineWindowEvent;

	bool recieveXEngineUpdates = true;
};

