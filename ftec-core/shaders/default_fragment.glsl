#version 150

struct Light{
	vec3 direction;
	vec3 color;
	float intensity;
	bool enabled;
};

struct Data {
	vec2 uv;
	vec3 position;
	vec3 normal;
	vec3 tangent;
};

struct SurfaceOutput{
	vec3 albedo;
	vec3 specular;
	vec3 normal;

	float smoothness;
	float glossiness;
};

uniform sampler2D u_Textures[8];
uniform samplerCube u_Skybox;

uniform Light u_Light;
uniform vec3 u_EyePosition;

in Data v;

out vec4 FragColor;

void output(SurfaceOutput surface);

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

	normal = tangentMatrix * normalmapSample;

	SurfaceOutput surface;
	surface.albedo = texture(u_Textures[0], v.uv).rgb;
	surface.specular = vec3(0.5, 0.2, 0.1);
	surface.normal = normal;

	surface.smoothness = 0.1f;
	surface.glossiness = 0.2f;

	output(surface);
}

void output(SurfaceOutput surface)
{
	vec3 diffuseColor = vec3(1.0, 1.0, 1.0);
	vec3 specularColor = vec3(0.0, 0.0, 0.0);
	vec3 glossColor = vec3(0.0, 0.0, 0.0);
	
	vec3 eyeDirection = normalize(v.position - u_EyePosition);

	if(u_Light.enabled){
		diffuseColor = u_Light.color * dot(-u_Light.direction, surface.normal) * u_Light.intensity;
		diffuseColor = max(vec3(0.0, 0.0, 0.0), diffuseColor);

		if(surface.smoothness != 1.0){
			vec3 reflectVector = reflect(-u_Light.direction, surface.normal);

			float cosAngle = max(0.0, dot(reflectVector, eyeDirection));

			specularColor = u_Light.color * pow(cosAngle, 1.0 / (1.0 - surface.smoothness));
		}
	}

	if(surface.glossiness > 0.0){
		vec3 boxReflection = reflect(eyeDirection, surface.normal);
		boxReflection = vec3(boxReflection.x, -boxReflection.yz);
		float rim = max(0.0, 1.0 - dot(-eyeDirection, surface.normal));

		glossColor = texture(u_Skybox, boxReflection).rgb * rim; //TODO metalicness
	}

	vec3 output = diffuseColor * surface.albedo + specularColor * surface.specular + glossColor * surface.glossiness;

	FragColor = vec4(output, 1.0);
}