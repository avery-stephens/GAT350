#version 430 core

#define POINT  0 
#define DIRECTIONAL 1 
#define SPOTLIGHT 2
#define MAX_LIGHTS 5

in vec3 position;
in vec2 texcoord;
in mat3 tbn;

out vec4 fcolor; //pixel to draw

uniform struct Light
{
	int type;
	vec3 color;
	vec4 position;
	vec3 direction; 
	float cutoff; 
	float exponent;
} lights[MAX_LIGHTS];

uniform struct Material
{
	vec3 color;
	float shininess;
	vec2 uv_tiling;
	vec2 uv_offset;
} material;

uniform int light_count;
uniform vec3 ambient_color;
 
layout (binding = 0) uniform sampler2D diffuseMap; //diffuse map
layout (binding = 1) uniform sampler2D normalMap; //norm map

void phong(Light light, vec3 position, vec3 normal, out vec3 diffuse, out vec3 specular)
{
	// direction vector to light 
	vec3 light_dir = (light.type == DIRECTIONAL) ? normalize(-light.direction) : normalize(vec3(light.position) - position); 
	// if spotlight, compute intensity based on angle to cutoff 
	float spot_intensity = 1; 
	if (light.type == SPOTLIGHT) 
	{ 
		// get cosine of light direction and direction vector from light 
		float cosine = dot(light.direction, -light_dir); 
		// get angle using acos() of the cosine (returns the angle) 
		float angle = acos(cosine); 
  
		// if angle less than light.cutoff, set spot intensity else set to 0 (outside) 
		spot_intensity = (angle < light.cutoff) ? pow(cosine, light.exponent) : 0; 
	} 
	
	//AMBIENT
	//DIFFUSE

	// calculate light intensity with dot product (normal * light direction)
	float intensity = max(dot(light_dir, normal), 0) * spot_intensity; 
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

	fcolor = vec4(ambient_color, 1) * texture(diffuseMap, texcoord); 

	vec3 normal = texture(normalMap, ttexcoord).rgb;
	normal = (normal * 2) - 1;
	normal = normalize(tbn * normal);

	for (int i = 0; i < light_count; i++) 
	{ 
		vec3 diffuse; 
		vec3 specular; 
  
		phong(lights[i], position, normal, diffuse, specular); 
		fcolor += (vec4(diffuse, 1) * texture(diffuseMap, texcoord)) + vec4(specular, 1); 
	} 
	//calulate diffuse
	vec4 texture_color = texture(diffuseMap, ttexcoord);
	//fcolor = vec4(diffuse, 1) * texture_color + vec4(specular, 1);
} 