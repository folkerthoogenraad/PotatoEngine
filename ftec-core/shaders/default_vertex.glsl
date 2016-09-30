#version 150

uniform mat4 u_MatrixModel;
uniform mat4 u_MatrixView;
uniform mat4 u_MatrixProjection;

struct Light{
	vec3 direction;
	bool enabled;
	bool shadowsEnabled;
	mat4 shadowMatrix;
	sampler2D shadowTexture;
};

uniform Light u_Light;

in vec3 position;
in vec3 normal;
in vec2 uv;

out vec2 v_Uv;

out vec4 v_WorldPosition;
out vec4 v_WorldNormal;
out vec4 v_WorldLightPosition;

out vec4 v_Color;
out float v_Lightness;


void main()
{
	vec4 worldNormal = u_MatrixModel * vec4(normal, 0.0);

	float lightness = 0.0;

	if(u_Light.enabled){
		vec4 lightDir = vec4(u_Light.direction, 0.0);
		lightness = dot(-lightDir, worldNormal);

		if(u_Light.shadowsEnabled){
			v_WorldLightPosition = (u_Light.shadowMatrix * u_MatrixModel * vec4(position, 1.0)) / 2.0 + 0.5;
		}
	}
	
	if(lightness < 0.2){
		lightness = 0.2;
	}
	
	v_WorldPosition = u_MatrixModel * vec4(position, 1.0);
	v_WorldNormal = worldNormal;
	v_Uv = uv;
	v_Lightness = lightness;
	
	v_Color =  vec4(1.0,1.0,1.0,1.0);
	v_Color.a = 1.0;
    gl_Position = u_MatrixProjection * u_MatrixView * u_MatrixModel * vec4(position, 1.0);
}