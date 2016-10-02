#version 150

in vec3 position;
in vec3 normal;
in vec3 tangent;
in vec2 uv;

struct Light{
	vec4 direction;
	bool enabled;
};

struct Data {
	vec2 uv;
	vec3 position;
	vec3 normal;
	vec3 tangent;
};

uniform mat4 u_MatrixModel;
uniform mat4 u_MatrixView;
uniform mat4 u_MatrixProjection;

out Data v;

void main()
{
	v.normal = vec3(u_MatrixModel * vec4(normal, 0.0));
	v.tangent = vec3(u_MatrixModel * vec4(tangent, 0.0));
	v.position = vec3(u_MatrixModel * vec4(position, 1.0));
	v.uv = uv;
	
    gl_Position = u_MatrixProjection * u_MatrixView * vec4(v.position, 1.0);
}