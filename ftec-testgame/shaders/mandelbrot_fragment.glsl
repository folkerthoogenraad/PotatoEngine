#version 150

uniform sampler2D u_Textures[8];

in vec2 v_Uv;
in vec4 v_Color;

out vec4 FragColor;

#define ITERATIONS 1000

float map(float v, float inmin, float inmax, float outmin, float outmax)
{
	return ((v - inmin) / (inmax - inmin)) * (outmax - outmin) + outmin;
}

void main()
{

	float a = map(v_Uv.x, 0, 1, -2, 2);
	float b = map(v_Uv.y, 0, 1, -2, 2);
	
	float ca = a;
	float cb = b;

	float n = 0;

	for(;n < ITERATIONS; n++){
		float aa = a * a - b * b;
		float bb = 2 * a * b;

		if(aa + bb > 16){
			break;
		}

		a = aa + ca;
		b = bb + cb;
	}

	float v = sqrt(map(
			n, 
			0, ITERATIONS,
			0, 1
		));
	

	FragColor = vec4(0.0,v,0.0,1.0);

	if(n == ITERATIONS){
		FragColor = vec4(0.0, 0.0, 0.0, 1.0);
	}
	
}