#version 430 core

in vec2 texcoord;

out vec4 fcolor;

const float screen_height = 600.0;

uniform float offset;

uniform sampler2D textureMap;

void main() 
{ 
	vec3 color = texture(textureMap, texcoord).rrb; 

	// invert 
	fcolor = vec4(0.7 - color, 1); 
} 
