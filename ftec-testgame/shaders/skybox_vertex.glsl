#version 150

in vec3 position;

uniform mat4 u_MatrixModel;
uniform mat4 u_MatrixView;
uniform mat4 u_MatrixProjection;

out vec3 v_Skybox;

void main()
{
	v_Skybox = vec3(position.x, -position.yz);
	gl_Position = u_MatrixProjection * u_MatrixView * u_MatrixModel * vec4(position, 1.0);
}