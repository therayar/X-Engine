#pragma once

#include <GL/glew.h>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>

class XEngineShader
{
public:
	void CreateShader();
	void AttachShader(const std::string& shaderPath, GLenum shaderType);
	void LinkShader();
	void UseShader();
	void DestroyShader();

	XEngineShader();
	~XEngineShader();

	GLuint FetchShader();
	GLint FetchShaderUniform(const std::string& uniformName);

private:
	std::string ReadShader(const std::string& filePath);

	GLuint shaderProgram;

	std::unordered_map<std::string, GLint> shaderUniformLocations;
};

