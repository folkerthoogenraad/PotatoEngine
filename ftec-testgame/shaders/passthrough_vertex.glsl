#version 150

in vec3 position;
in vec2 uv;

out vec2 v_Uv;

void main()
{
	v_Uv = uv;
    gl_Position = vec4(position, 1.0);
}