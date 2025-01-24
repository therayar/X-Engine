#include "XEngine.h"
#include "XEngineWindow.h"
#include "XEngineModel.h"
#include "XEngineShader.h"

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

#include <vector>
#include <fstream>
#include <sstream>

XEngine xEngine;
XEngineWindow xEngineWindow;
XEngineShader xEngineShader;
XEngineModel pyramidModel;

std::vector<GLuint> pyramidModelIndices =
{
    0, 3, 1,
    1, 3, 2,
    2, 3, 0,
    0, 1, 2
};

std::vector<GLfloat> pyramidModelVertices
{
    -1.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 1.0f,
    1.0f, -1.0f, 0.0f,
    0.0f, 1.0f, 0.0f
};

int main(int argc, char* argv[])
{
    xEngineWindow.CreateXEngineWindow("X ENGINE", 1280, 720);

    xEngine.engineWindow = xEngineWindow;
    xEngine.InitializeXEngine();

    pyramidModel.modelShader = xEngineShader;
    pyramidModel.ConstructModel(pyramidModelVertices, pyramidModelIndices);

    xEngineShader.CreateShader();

    xEngineShader.AttachShader("Engine/Shaders/GL_Shader_Vertex.glsl", GL_VERTEX_SHADER);
    xEngineShader.AttachShader("Engine/Shaders/GL_Shader_Fragment.glsl", GL_FRAGMENT_SHADER);

    xEngineShader.LinkShader();

    pyramidModel.FetchModelShaderUniforms();

    while (xEngine.RecieveXEngineWindowEvents())
    {
        xEngine.HandleXEngineWindowEvents();

        xEngineWindow.UpdateXEngineWindowBackgroundColor();

        xEngineShader.UseShader();

        int bufferWidth, bufferHeight;
        SDL_GetWindowSize(xEngineWindow.GetXEngineWindow(), &bufferWidth, &bufferHeight);

        glViewport(0, 0, bufferWidth, bufferHeight);

        pyramidModel.RenderModel();

        xEngine.UpdateXEngine();
    }

    xEngine.DestroyXEngine();

    return 0;
}
