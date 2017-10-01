#version 150

uniform sampler2D u_Textures[8];

in vec2 v_Uv;
in vec4 v_Color;
flat in int v_TextureIndex;

out vec4 FragColor;

void main()
{
	FragColor = texture(u_Textures[v_TextureIndex], v_Uv) * v_Color;
	
}