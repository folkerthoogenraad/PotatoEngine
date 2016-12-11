#version 150

uniform sampler2D u_Textures[8];

in vec2 v_Uv;
in vec4 v_Color;

out vec4 FragColor;

void main()
{
	//The commented code is for rendering text. This should have a different shader for sure
	FragColor = texture(u_Textures[0], v_Uv) * v_Color; //vec4(1.0,1.0, 1.0,texture(u_Textures[0], v_Uv).r) * v_Color;
}