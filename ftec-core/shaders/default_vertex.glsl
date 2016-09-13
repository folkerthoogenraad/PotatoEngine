
uniform mat4 u_MatrixModel;
uniform mat4 u_MatrixView;
uniform mat4 u_MatrixProjection;

attribute vec3 position;
attribute vec3 normal;
attribute vec2 uv;

varying vec2 v_Uv;

varying vec4 v_WorldPosition;
varying vec4 v_WorldNormal;

varying vec4 v_Color;
varying float v_Lightness;

void main()
{

	vec4 worldNormal = u_MatrixModel * vec4(normal, 0.0);

	vec4 lightDir = normalize(vec4(-1.0, -1.0, -1.0, 0.0));

	float lightness = dot(-lightDir, worldNormal);

	if(lightness < 0.1){
		lightness = 0.1;
	}
	
	v_WorldPosition = u_MatrixModel * vec4(position, 1.0);
	v_WorldNormal = worldNormal;
	v_Uv = uv;
	v_Lightness = lightness;
	
	v_Color =  vec4(1.0,1.0,1.0,1.0);
	v_Color.a = 1.0;
    gl_Position = u_MatrixProjection * u_MatrixView * u_MatrixModel * vec4(position, 1.0);
}