#pragma once

#include "XEngineShader.h"

#include <GL/glew.h>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

#include <vector>

class XEngineModel
{
public:
	void LoadModel();
	void ConstructModel(std::vector<GLfloat> modelVertices, std::vector<GLuint> modelIndices);
	void RenderModel();
	void DestroyModel();

	void FetchModelShaderUniforms();

	XEngineShader modelShader;

private:
	std::vector<GLfloat> modelVertices;
	std::vector<GLuint> modelIndices;

	GLuint modelVertexArray;
	GLuint modelVertexBuffer, modelIndexBuffer;

	glm::mat4 modelMatrix;

	GLint modelMatrixUniformLocation;
};

