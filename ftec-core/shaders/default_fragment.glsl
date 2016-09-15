//This thing is just a poor slave man

struct Light{
	vec3 direction;
	bool enabled;
	bool shadowsEnabled;
	mat4 shadowMatrix;
	sampler2D shadowTexture;
};

uniform Light u_Light;


uniform sampler2D u_MainTexture;

varying vec4 v_WorldPosition;
varying vec4 v_WorldNormal;
varying vec3 v_WorldLightPosition;

varying vec4 v_Color;
varying vec2 v_Uv;
varying float v_Lightness;

void main()
{
	float lightness = v_Lightness;
	
	if(u_Light.shadowsEnabled){
		float bias = 0.005;
		if(texture(u_Light.shadowTexture, vec2(v_WorldLightPosition.x / 2.0 + 0.5, v_WorldLightPosition.y / 2.0 + 0.5)).z < v_WorldLightPosition.z / 2.0 + 0.5 - bias){
			lightness = 0.1;
		}
	}

	vec4 resultColor = v_Color * lightness;
	resultColor.a = 1.0;
    
	gl_FragColor = texture(u_MainTexture, v_Uv) * resultColor;
    
}