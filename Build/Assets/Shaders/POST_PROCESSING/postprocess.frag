#version 430 core 
  
in vec2 texcoord; 
  
out vec4 fcolor; 

uniform float screen_height = 600.0; 

uniform float offset; 
  
uniform sampler2D textureMap; 

const float THICC = 0.9; //mess with this for different values
  
void main() 
{ 
	vec3 color = texture(textureMap, texcoord).rgb; 

	//normal
	fcolor = texture(textureMap, texcoord); 

	//	// black and white effect
	//float avg = (color.r + color.g + color.b) / 3.0; 
	//fcolor = vec4(vec3(avg), 1); 
	
	//invert effect 	
	//fcolor = vec4(1.0 - color, 1);


	////scanlines effect
	//// get the screen y position (uv coordinates range 0 <-> 1) 
	//int y = int(texcoord.y * screen_height); 
	//// set the alpha based on the modulus of the y position 
	//float alpha = (y % 3 != 0) ? 1 : 0;
	//
	//fcolor = vec4(color.rgb * (0.9), alpha); 

	////WAVE effect
	//vec2 ttexcoord = texcoord; 
	//ttexcoord.x += sin(ttexcoord.y * 30.0 + offset) / 100.0; 
	//fcolor = texture(textureMap, ttexcoord);

	//ONLINE SCANLINE effect
    //vec2 p = vec2(floor(gl_FragCoord.x), floor(gl_FragCoord.y));
	//fcolor = vec4((step(0.01, mod(p.y, 6.0)) * (1.0 - THICC) + THICC) * color, 1);
} 