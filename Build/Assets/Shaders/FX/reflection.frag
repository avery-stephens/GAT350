#version 430 core

in vec3 reflect_direct;

out vec4 fcolor;

layout (binding = 0) uniform samplerCube cubeMap;

void main()
{
	fcolor = texture(cubeMap, reflect_direct);
}
