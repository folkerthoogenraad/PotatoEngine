#version 150

//------------------------------------------------------------------//
// Structures
//------------------------------------------------------------------//
struct DirectionalLight{
	vec3 direction;
	vec3 color;
	float intensity;
	bool enabled;
};

struct Data {
	vec2 uv;
	vec3 position;
	vec3 normal;
	vec3 tangent;
};

//------------------------------------------------------------------//
// Uniforms
//------------------------------------------------------------------//
uniform sampler2D u_Textures[8];

//------------------------------------------------------------------//
// Inputs
//------------------------------------------------------------------//
in Data v;

//------------------------------------------------------------------//
// Outputs
//------------------------------------------------------------------//
out vec4 FragColor;

//------------------------------------------------------------------//
// Declarations
//------------------------------------------------------------------//


//------------------------------------------------------------------//
// Implementations
//------------------------------------------------------------------//
void main()
{
	FragColor = vec4(v.normal, 1.0);//texture(u_Textures[0], v.uv) * dot(normalize(v.normal), -normalize(vec3(1.0,-1.0,1.0)));
	FragColor.a = 1.0;
}