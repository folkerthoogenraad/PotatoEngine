//This thing is just a poor slave man

uniform sampler2D u_MainTexture;

varying vec4 v_Color;
varying vec4 v_Uv;

void main()
{
    gl_FragColor = texture(u_MainTexture, v_Uv) * v_Color;
}