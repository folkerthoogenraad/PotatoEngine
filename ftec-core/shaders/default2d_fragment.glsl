#version 150

uniform sampler2D u_Textures[8];

in vec2 v_Uv;
in vec4 v_Color;

out vec4 FragColor;

void main()
{
	FragColor = texture(u_Textures[0], v_Uv) * v_Color;
}