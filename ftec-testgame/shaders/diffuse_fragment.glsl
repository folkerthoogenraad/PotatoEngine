#version 150

uniform sampler2D u_Textures[8];

struct Data {
	vec2 uv;
	vec3 position;
	vec3 normal;
	vec3 tangent;
};

in Data v;

out vec4 FragColor;

void main()
{
	float lighting = max(0.4, dot(-v.normal, normalize(vec3(0.0,-2.0,1.0))));

	FragColor = texture(u_Textures[0], v.uv) * vec4(lighting, lighting, lighting, 1.0); 
}