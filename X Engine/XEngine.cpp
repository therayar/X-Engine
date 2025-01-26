#include "XEngine.h"

void XEngine::InitializeXEngine()
{
    if (SDL_WasInit(0) == 0)
    {
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
        {
            return;
        }
    }

    // Creating and Setting OpenGl Context
    engineOpenGLContext = SDL_GL_CreateContext(engineWindow.GetXEngineWindow());
    if (!engineOpenGLContext)
    {
        SDL_DestroyWindow(engineWindow.GetXEngineWindow());
        SDL_Quit();

        return;
    }

    SDL_GL_MakeCurrent(engineWindow.GetXEngineWindow(), engineOpenGLContext);

    // Initializing GLEW and checking for errors
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        SDL_GL_DeleteContext(engineOpenGLContext);
        SDL_Quit();

        return;
    }

    glEnable(GL_DEPTH_TEST);
}

void XEngine::UpdateXEngine()
{
    glUseProgram(0);

    SDL_GL_SwapWindow(engineWindow.GetXEngineWindow());
}

void XEngine::DestroyXEngine()
{
    if (engineOpenGLContext)
    {
        SDL_GL_DeleteContext(engineOpenGLContext);
        engineOpenGLContext = nullptr;
    }

    if (engineWindow.GetXEngineWindow())
    {
        SDL_DestroyWindow(engineWindow.GetXEngineWindow());
    }

    SDL_Quit();
}

XEngine::XEngine() : 
    engineOpenGLContext(nullptr),
    engineWindow(XEngineWindow())
{

}

XEngine::~XEngine()
{
    DestroyXEngine();
}
