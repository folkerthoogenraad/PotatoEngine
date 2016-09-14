//This thing is just a poor slave man

uniform sampler2D u_MainTexture;

varying vec4 v_WorldPosition;
varying vec4 v_WorldNormal;

varying vec4 v_Color;
varying vec2 v_Uv;
varying float v_Lightness;

void main()
{
	vec4 resultColor = v_Color * v_Lightness;
	resultColor.a = 1.0;

    gl_FragColor = texture(u_MainTexture, v_Uv) * resultColor;
}