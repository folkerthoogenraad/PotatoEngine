//This thing is just a poor slave man

uniform sampler2D u_MainTexture;

uniform float u_Intensity;
uniform vec3 u_LightPosition;

varying vec4 v_WorldPosition;
varying vec4 v_WorldNormal;

varying vec4 v_Color;
varying vec2 v_Uv;
varying float v_Lightness;

void main()
{
	float lightness = v_Lightness;

	float radius = 8.0;
	float intensity = u_Intensity + 1.0;

	vec4 lightPosition = vec4(u_LightPosition, 0.0);//vec4(0.0,2.0,0.0,0.0);
	vec4 lightDirection = normalize(lightPosition - v_WorldPosition);
	float distance = distance(lightPosition, v_WorldPosition);

	lightness = (intensity - distance / (radius / intensity));
	
	if(lightness < 0.2)
		lightness = 0.2;

	lightness *= dot(lightDirection, v_WorldNormal);
	
	if(lightness < 0.2)
		lightness = 0.2;

	lightness = max(lightness, v_Lightness);

	
	vec4 resultColor = v_Color * lightness;// * lightness;
	resultColor.a = 1.0;

    gl_FragColor = texture(u_MainTexture, v_Uv) * resultColor;
}