#pragma once

#include "XEngineWindow.h"

#include <GL/glew.h>
#include <SDL.h>

class XEngine
{
public:
	void InitializeXEngine();
	void UpdateXEngine();
	void DestroyXEngine();

	XEngine();
	~XEngine();

	XEngineWindow engineWindow;

private:
	SDL_GLContext engineOpenGLContext;
};

