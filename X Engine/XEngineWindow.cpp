#include "XEngineWindow.h"

void XEngineWindow::CreateXEngineWindow(string windowName, int windowWidth, int windowHeight)
{
    // Checking if SDL is initialized and if not then initializing it
    if (SDL_WasInit(0) == 0)
    {
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
        {
            return;
        }
    }

    // Setting SDL attributes for OpenGL
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 8);

    engineWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if (!engineWindow)
    {
        SDL_Quit();

        return;
    }

    // Get the native window handle (HWND)
    SDL_SysWMinfo wmInfo;
    SDL_VERSION(&wmInfo.version);
    if (SDL_GetWindowWMInfo(engineWindow, &wmInfo) == SDL_FALSE)
    {
        SDL_DestroyWindow(engineWindow);
        SDL_Quit();
        return;
    }

    HWND hwnd = wmInfo.info.win.window;

    DWORD captionBarColor = RGB(25, 26, 28);
    DWORD captionBarTextColor = RGB(235, 245, 255);
    DWORD captionBarBorderColor = RGB(60, 64, 68);
    HRESULT captionBarColorResult = DwmSetWindowAttribute(hwnd, DWMWA_CAPTION_COLOR, &captionBarColor, sizeof(captionBarColor));
    HRESULT captionBarTextColorResult = DwmSetWindowAttribute(hwnd, DWMWA_TEXT_COLOR, &captionBarTextColor, sizeof(captionBarTextColor));
    HRESULT captionBarBorderColorResult = DwmSetWindowAttribute(hwnd, DWMWA_BORDER_COLOR, &captionBarBorderColor, sizeof(captionBarBorderColor));

    if (FAILED(captionBarColorResult) || FAILED(captionBarTextColorResult) || FAILED(captionBarBorderColorResult))
    {
        return;
    }
}

void XEngineWindow::HandleXEngineWindowEvents()
{
    while (SDL_PollEvent(&engineWindowEvent))
    {
        if (engineWindowEvent.type == SDL_QUIT)
        {
            recieveEngineWindowUpdates = false;
        }

        if (engineWindowEvent.type == SDL_WINDOWEVENT && engineWindowEvent.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
        {
            int bufferWidth, bufferHeight;
            SDL_GetWindowSize(engineWindow, &bufferWidth, &bufferHeight);

            glViewport(0, 0, bufferWidth, bufferHeight);
        }
    }
}

bool XEngineWindow::RecieveXEngineWindowEvents()
{
    return recieveEngineWindowUpdates;
}

void XEngineWindow::ClearXEngineWindow()
{
    glClearColor(0.035f, 0.040f, 0.045f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void XEngineWindow::DestroyXEngineWindow()
{
    if (engineWindow)
    {
        SDL_DestroyWindow(engineWindow);

        engineWindow = nullptr;
    }
}

SDL_Window* XEngineWindow::GetXEngineWindow()
{
    return engineWindow;
}

XEngineWindow::XEngineWindow() : 
    windowWidth(0),
    windowHeight(0),
    engineWindow(nullptr)
{

}

XEngineWindow::~XEngineWindow()
{
    DestroyXEngineWindow();
}

