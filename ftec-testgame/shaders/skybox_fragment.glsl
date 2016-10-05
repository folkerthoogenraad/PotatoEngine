#version 150

uniform samplerCube u_Skybox;

in vec3 v_Skybox;

out vec4 FragColor;

void main () 
{
	FragColor = texture (u_Skybox, v_Skybox);
}