#include "XEngineModel.h"

void XEngineModel::LoadModel()
{

}

void XEngineModel::ConstructModel(std::vector<GLfloat> modelVertices, std::vector<GLuint> modelIndices)
{
    this->modelVertices = modelVertices;
    this->modelIndices = modelIndices;

    glGenVertexArrays(1, &modelVertexArray);
    glBindVertexArray(modelVertexArray);

    glGenBuffers(1, &modelIndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, modelIndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->modelIndices.size() * sizeof(this->modelIndices[0]), this->modelIndices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &modelVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, modelVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, this->modelVertices.size() * sizeof(this->modelVertices[0]), this->modelVertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void XEngineModel::RenderModel()
{
    modelMatrix = 1.0f;

    modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.0f, 0.0f));

    modelMatrix = glm::rotate(modelMatrix, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f, 0.5f, 0.5f));

    glUniformMatrix4fv(modelShader.FetchShaderUniform("model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));

    glBindVertexArray(modelVertexArray);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, modelIndexBuffer);

    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(modelIndices.size()), GL_UNSIGNED_INT, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void XEngineModel::DestroyModel()
{

}

void XEngineModel::FetchModelShaderUniforms()
{
    modelMatrixUniformLocation = modelShader.FetchShaderUniform("model");
}