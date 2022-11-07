#version 430 core

in vec3 position;
//in vec3 normal;
in vec2 texcoord;
in mat3 tbn;

out vec4 fcolor; //pixel to draw

struct Light
{
	vec3 ambient;
	vec3 color;
	vec4 position;
};

struct Material
{
	vec3 color;
	float shininess;
	vec2 uv_tiling;
	vec2 uv_offset;
};
 
uniform Light light;
uniform Material material;

 
layout (binding = 0) uniform sampler2D diffuseMap; //diffuse map
layout (binding = 1) uniform sampler2D normalMap; //norm map
//layout (binding = 2) uniform sampler2D emmissiveMap; //emmissive map

void phong(vec3 position, vec3 normal, out vec3 ambient, out vec3 diffuse, out vec3 specular)
{
	//AMBIENT
	ambient = light.ambient * material.color;

	//DIFFUSE
	//calculate light direction
	vec3 light_dir = normalize(vec3(light.position) - position);
	// calculate light intensity with dot product (normal * light direction)
	float intensity = max(dot(light_dir, normal), 0);
	//calculate diffuse
	diffuse = light.color * material.color * intensity;
 
	// SPECULAR
	specular = vec3(0);
	if (intensity > 0)
	{
		vec3 reflection = reflect(-light_dir, normal);
		vec3 view_dir = normalize(-vec3(position));
		intensity = max(dot(reflection, view_dir), 0);
		intensity = pow(intensity, material.shininess);
		specular = light.color * material.color * intensity; //1, 1, 1
	}
}
 
void main()
{
	vec2 ttexcoord = (texcoord * material.uv_tiling) + material.uv_offset;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	vec3 normal = texture(normalMap, ttexcoord).rgb;

	normal = (normal * 2) - 1;
	normal = normalize(tbn * normal);

	phong(position, normal, ambient, diffuse, specular);

	//calulate diffuse
	vec4 texture_color = texture(diffuseMap, ttexcoord);
	fcolor = vec4(ambient + diffuse, 1) * texture_color + vec4(specular, 1);
} 