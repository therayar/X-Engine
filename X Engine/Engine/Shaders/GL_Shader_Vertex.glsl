#version 450

layout (location = 0) in vec3 position;

out vec4 vertexColor;

uniform mat4 model;

void main()
{
	gl_Position = model * vec4(position, 1.0);

	vertexColor = vec4(clamp(position, 0.0f, 1.0f), 1.0f);
}