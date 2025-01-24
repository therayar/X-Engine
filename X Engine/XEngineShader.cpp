#include "XEngineShader.h"

void XEngineShader::CreateShader()
{
    shaderProgram = glCreateProgram();

    if (!shaderProgram)
    {
        return;
    }
}

void XEngineShader::AttachShader(const std::string& shaderPath, GLenum shaderType)
{
    GLuint shader = glCreateShader(shaderType);

    std::string shaderCodeString{ReadShader(shaderPath)};

    const char* shaderCodeCString{shaderCodeString.c_str()};

    const char* shaderCode[1];
    shaderCode[0] = shaderCodeCString;

    GLint codeLength[1];
    codeLength[0] = strlen(shaderCodeCString);

    glShaderSource(shader, 1, shaderCode, codeLength);
    glCompileShader(shader);

    GLint result = 0;
    GLchar eLog[1024] = {0};

    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderInfoLog(shader, 1024, NULL, eLog);
        return;
    }

    glAttachShader(shaderProgram, shader);
}

void XEngineShader::UseShader()
{
    glUseProgram(shaderProgram);
}

void XEngineShader::LinkShader()
{
    GLint result = 0;
    GLchar eLog[1024] = {0};

    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(shaderProgram, sizeof(eLog), nullptr, eLog);
        return;
    }

    glValidateProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(shaderProgram, sizeof(eLog), nullptr, eLog);
        return;
    }

    GLint shaderUniformsNumber = 0;
    glGetProgramiv(shaderProgram, GL_ACTIVE_UNIFORMS, &shaderUniformsNumber);

    for (GLint i = 0; i < shaderUniformsNumber; ++i)
    {
        char uniformName[256];
        GLsizei uniformLength;
        GLint uniformSize;
        GLenum uniformType;

        glGetActiveUniform(shaderProgram, i, sizeof(uniformName), &uniformLength, &uniformSize, &uniformType, uniformName);
        GLint uniformLocation = glGetUniformLocation(shaderProgram, uniformName);

        if (uniformLocation == -1)
        {
            continue;
        }

        std::string uniformNameString(uniformName);

        shaderUniformLocations[uniformNameString] = uniformLocation;
    }
}

void XEngineShader::DestroyShader()
{
    if (shaderProgram)
    {
        GLint attachedShadersNumber{0};
        glGetProgramiv(shaderProgram, GL_ATTACHED_SHADERS, &attachedShadersNumber);

        if (attachedShadersNumber > 0)
        {
            GLuint* shaders = new GLuint[attachedShadersNumber];
            glGetAttachedShaders(shaderProgram, attachedShadersNumber, NULL, shaders);

            for (GLint i = 0; i < attachedShadersNumber; ++i)
            {
                glDetachShader(shaderProgram, shaders[i]);
                glDeleteShader(shaders[i]);
            }

            delete[] shaders;
        }

        glDeleteProgram(shaderProgram);
        shaderProgram = 0;
    }
}

GLuint XEngineShader::FetchShader()
{
    return shaderProgram;
}

GLint XEngineShader::FetchShaderUniform(const std::string& uniformName)
{
    auto it = shaderUniformLocations.find(uniformName);
    if (it != shaderUniformLocations.end())
    {
        return it->second;
    }
    else
    {
        return 0;
    }
}

std::string XEngineShader::ReadShader(const std::string& filePath)
{
    std::ifstream shaderFile(filePath, std::ios::in);
    if (!shaderFile.is_open())
    {
        return "";
    }

    std::stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();

    return shaderStream.str();
}