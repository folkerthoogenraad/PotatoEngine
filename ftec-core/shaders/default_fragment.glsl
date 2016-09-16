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

		//if this pixel is in range for the shadow map size
		if(v_WorldLightPosition.x > 0 && v_WorldLightPosition.x < 1 && v_WorldLightPosition.y > 0 && v_WorldLightPosition.y < 1){

			//Is this pixel in the light, or is it in the darkness
			if(texture(u_Light.shadowTexture, v_WorldLightPosition.xy).z < v_WorldLightPosition.z - bias){

				//Shade it, but not too much
				if(lightness > 0.4){
					lightness = 0.4;
				}
			}
		}

	}

	lightness = floor(lightness * 5.0) / 5.0;
	if(lightness < 0.2){
		lightness = 0.2;
	}

	vec4 resultColor = v_Color * lightness;
	resultColor.a = 1.0;
    
	gl_FragColor = texture(u_MainTexture, v_Uv) * resultColor;
    
}