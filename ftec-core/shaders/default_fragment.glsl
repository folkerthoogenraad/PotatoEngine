#version 150

struct Light{
	vec4 direction;
	bool enabled;
};

struct Data {
	vec2 uv;
	vec3 position;
	vec3 normal;
	vec3 tangent;
};

uniform sampler2D u_Textures[8];
uniform samplerCube u_Skybox;

uniform Light u_Light;
uniform vec3 u_EyePosition;

in Data v;

out vec4 FragColor;

float calculateLighting(vec3 normal);

void main()
{
	vec3 eyeDirection = normalize(v.position - u_EyePosition);

	vec3 normal = normalize(v.normal);
	vec3 tangent = normalize(v.tangent);
	vec3 bitangent = cross(normal, tangent);

	vec3 normalmapSample = texture(u_Textures[1], v.uv).xyz * 2.0 - 1.0;

	mat3 tangentMatrix = mat3(
		tangent.x, tangent.y, tangent.z,
		bitangent.x, bitangent.y, bitangent.z,
		normal.x, normal.y, normal.z
	);
	/*mat3 tangentMatrix = mat3(
		tangent.x, bitangent.x, normal.x,
		tangent.y, bitangent.y, normal.y,
		tangent.z, bitangent.z, normal.z
	);*/
	/*mat3 tangentMatrix = mat3(
		1,0,0,
		0,0,1,
		0,1,0
	);*/

	normal = tangentMatrix * normalmapSample;


	vec3 boxReflection = reflect(eyeDirection, normal);
    boxReflection = vec3(boxReflection.x, -boxReflection.yz);
	
	float rim = dot(-eyeDirection, normal);

	vec4 skyboxSample = texture(u_Skybox, boxReflection);
	vec4 textureSample = texture(u_Textures[0], v.uv);

	vec4 lightingColor = vec4(1.0, 1.0, 1.0, 1.0) * calculateLighting(normal);
	lightingColor.a = 1.0;

	FragColor = textureSample * lightingColor + skyboxSample *  (1.0 - max(rim, 0.0)) * 0.4 + skyboxSample * lightingColor * 0.1;

	vec3 lightingDir = normalize(vec3(1.0, -1.0, -1.0));
	vec3 reflectVector = reflect(-lightingDir, normal);

	float cosAngle = max(0.0, dot(reflectVector, eyeDirection));

	FragColor += pow(cosAngle, 20.0) * 0.1;
	FragColor.a = 1.0;
}


float calculateLighting(vec3 normal)
{
	float lightness = 1.0;

	if(u_Light.enabled){
		lightness = dot(-normalize(vec3(1.0, -1.0, -1.0)), normal);

		if(lightness < 0.2){
			lightness = 0.2;
		}
	}

	return lightness;
}