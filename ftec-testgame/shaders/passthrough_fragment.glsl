#version 150

uniform sampler2D u_MainTexture;

in vec2 v_Uv;

out vec4 FragColor;

void main()
{
    FragColor = texture(u_MainTexture, v_Uv);
}