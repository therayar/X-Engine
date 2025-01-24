#version 450

in vec4 vertexColor;

out vec4 objectColor;

void main()
{
	objectColor = vertexColor;
}