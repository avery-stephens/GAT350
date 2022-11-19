#version 430 core

in vec3 reflect_direct;
in vec3 refract_direct;

uniform float i;

out vec4 fcolor;

uniform samplerCube cubeMap;

void main()
{
	vec3 reflect_color = texture(cubeMap, reflect_direct).rgb;
	vec3 refract_color = texture(cubeMap, refract_direct).rgb;

	vec3 color = mix(reflect_color, refract_color, i);
	
	fcolor = texture(cubeMap, color);
}
