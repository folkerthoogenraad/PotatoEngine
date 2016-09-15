attribute vec3 position;
attribute vec2 uv;

varying vec2 v_Uv;

void main()
{
	v_Uv = uv;
    gl_Position = vec4(position, 1.0);
}