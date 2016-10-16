#version 150

uniform mat4 u_MatrixModel;
uniform mat4 u_MatrixView;
uniform mat4 u_MatrixProjection;

in vec3 position;
in vec2 uv;
in vec4 color;

out vec2 v_Uv;
out vec4 v_Color;

void main()
{
	v_Uv = uv;
	v_Color = color;

	gl_Position = u_MatrixProjection * u_MatrixView * u_MatrixModel * vec4(position, 1.0);
}