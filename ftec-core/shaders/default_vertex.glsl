
uniform mat4 u_MatrixModel;
uniform mat4 u_MatrixView;
uniform mat4 u_MatrixProjection;

attribute vec3 position;
attribute vec3 normal;
attribute vec2 uv;

varying vec2 v_Uv;
varying vec4 v_Color;

void main()
{
	v_Uv = uv;

	vec3 worldNormal = u_MatrixModel * vec4(normal, 0.0);

	vec3 lightDir = normalize(vec3(0.0, 0.0, 1.0));

	float lightness = dot(lightDir, worldNormal);

	if(lightness < 0.1){
		lightness = 0.1;
	}
	
	v_Color =  vec4(1.0,1.0,1.0,1.0)  * lightness;
    gl_Position = u_MatrixProjection * u_MatrixView * u_MatrixModel * vec4(position, 1.0);
}