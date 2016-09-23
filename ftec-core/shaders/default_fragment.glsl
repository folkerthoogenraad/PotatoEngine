#version 150

struct Light{
	vec3 direction;
	bool enabled;
	bool shadowsEnabled;
	mat4 shadowMatrix;
	sampler2D shadowTexture;
};

uniform Light u_Light;
uniform sampler2D u_MainTexture;

in vec4 v_WorldPosition;
in vec4 v_WorldNormal;
in vec4 v_WorldLightPosition;

in vec4 v_Color;
in vec2 v_Uv;
in float v_Lightness;

out vec4 FragColor;

void main()
{
	float lightness = v_Lightness;

	/*if(u_Light.enabled){
		vec4 lightDir = vec4(u_Light.direction, 0.0);
		lightness = dot(-lightDir, v_WorldNormal);
	}*/
	
	if(u_Light.shadowsEnabled){
		float bias = 0.005;

		//if this pixel is in range for the shadow map size
		if(v_WorldLightPosition.x > 0 && v_WorldLightPosition.x < 1 && v_WorldLightPosition.y > 0 && v_WorldLightPosition.y < 1){

			//Is this pixel in the light, or is it in the darkness
			if(texture(u_Light.shadowTexture, v_WorldLightPosition.xy).z < v_WorldLightPosition.z - bias){

				//Shade it, but not too much
				lightness -= 0.4;
			}
		}

	}
	if(lightness < 0.2){
		lightness = 0.2;
	}

	vec4 resultColor = v_Color * lightness;
	resultColor.a = 1.0;
    
	FragColor = texture(u_MainTexture, v_Uv) * resultColor;
}