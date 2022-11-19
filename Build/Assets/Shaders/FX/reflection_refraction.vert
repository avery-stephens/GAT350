#version 430 core 

in layout(location = 0) vec3 vposition;
in layout(location = 2) vec3 vnormal;
uniform float ri = 1;

out vec3 reflect_direct;
out vec3 refract_direct;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	vec3 position = vec3(model * vec4(vposition, 1));
	vec3 normal = normalize(mat3(model) * vnormal);

	vec3 camera_pos = vec3(inverse(view)[3]); 
	vec3 view_dir = normalize(position - camera_pos);
	reflect_direct = reflect(view_dir, normal);
	refract_direct = refract(view_dir, normal, 1/ri);

	mat4 mvp = projection * view * model;
	gl_Position = mvp * vec4(vposition, 1.0);
}