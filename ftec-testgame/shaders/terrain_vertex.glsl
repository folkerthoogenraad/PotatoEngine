#version 150

//------------------------------------------------------------------//
// Structures
//------------------------------------------------------------------//
struct Data {
	vec2 uv;
	vec3 position;
	vec3 normal;
	vec3 tangent;
};

//------------------------------------------------------------------//
// Uniforms
//------------------------------------------------------------------//
uniform mat4 u_MatrixModel;
uniform mat4 u_MatrixView;
uniform mat4 u_MatrixProjection;

//------------------------------------------------------------------//
// Inputs
//------------------------------------------------------------------//
in vec3 position;
in vec3 normal;
in vec3 tangent;
in vec2 uv;

//------------------------------------------------------------------//
// Outputs
//------------------------------------------------------------------//
out Data v;

//------------------------------------------------------------------//
// Declarations
//------------------------------------------------------------------//


//------------------------------------------------------------------//
// Implementations
//------------------------------------------------------------------//
void main()
{
	v.position = vec3(u_MatrixProjection * u_MatrixView * u_MatrixModel * vec4(position, 1.0));
	v.normal = vec3(u_MatrixModel * vec4(normal, 0.0));
	v.tangent = vec3(u_MatrixModel * vec4(tangent, 0.0));
	v.uv = uv;

	//Tell opengl how much we love it
	gl_Position = u_MatrixProjection * u_MatrixView * u_MatrixModel * vec4(position, 1.0);
}