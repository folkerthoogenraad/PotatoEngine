#version 150

struct DirectionalLight{
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

struct SurfaceInput{
	vec3 albedo;
	vec3 specular;
	vec2 tiling;

	float bumpiness;
	float roughness;
	float metallicness;
};

struct SurfaceOutput{
	vec3 albedo;
	vec3 specular;
	vec3 normal;

	float roughness;
	float metallicness;
};

uniform sampler2D u_Textures[8];
uniform samplerCube u_Skybox;
uniform vec3 u_EyePosition;

uniform SurfaceInput u_Material;

uniform DirectionalLight u_Light;

in Data v;

out vec4 FragColor;

void surfaceOutput(in SurfaceOutput surface);
mat3 tangentMatrix(in vec3 normal);

void main()
{
	vec3 normal;

	if(u_Material.bumpiness > 0.0 && length(v.position - u_EyePosition) < 64.0f){
		vec3 normalmapSample = texture(u_Textures[1], v.uv * u_Material.tiling * 4.0).xyz * 2.0 - 1.0;
		normal = normalize(v.normal);
		normal = normalize(mix(tangentMatrix(normal) * normalmapSample, normal, 1.0 - u_Material.bumpiness));
	}
	else{
		normal = normalize(v.normal);
	}

	SurfaceOutput surface;
	surface.albedo = texture(u_Textures[0], v.uv * u_Material.tiling).rgb * u_Material.albedo;
	surface.specular = u_Material.specular;
	surface.normal = normal;

	surface.roughness = u_Material.roughness;
	surface.metallicness = u_Material.metallicness;

	surfaceOutput(surface);
}

void surfaceOutput(in SurfaceOutput surface)
{
	vec3 diffuseColor = vec3(1.0, 1.0, 1.0);
	vec3 specularColor = vec3(0.0, 0.0, 0.0);
	vec3 glossColor = vec3(0.0, 0.0, 0.0);
	
	vec3 eyeDir = v.position - u_EyePosition;
	float eyeDistance = length(eyeDir);
	
	vec3 eyeDirection = eyeDir / eyeDistance;

	if(u_Light.enabled){
		diffuseColor = u_Light.color * dot(-u_Light.direction, surface.normal) * u_Light.intensity;
		diffuseColor = max(vec3(0.2, 0.2, 0.2), diffuseColor);

		if(surface.roughness > 0.0){
			vec3 reflectVector = reflect(-u_Light.direction, surface.normal);

			float cosAngle = max(0.0, dot(reflectVector, eyeDirection));

			specularColor = u_Light.color * surface.specular * pow(cosAngle, 1.0 / (surface.roughness / 8.0)) * (1.0 - surface.roughness);
		}
	}

	if(surface.metallicness > 0.0){
		vec3 boxReflection = reflect(eyeDirection, surface.normal);
		boxReflection = vec3(boxReflection.x, -boxReflection.yz);

		glossColor = textureLod(u_Skybox, boxReflection, surface.roughness * 8.0).rgb * surface.metallicness;
	}

	vec3 color = diffuseColor * surface.albedo + specularColor + glossColor * surface.albedo * diffuseColor;

	FragColor = vec4(color, 1.0);
}

mat3 tangentMatrix(in vec3 normal)
{
	vec3 tangent = normalize(v.tangent);
	vec3 bitangent = cross(normal, tangent);

	return mat3(
		tangent.x, tangent.y, tangent.z,
		bitangent.x, bitangent.y, bitangent.z,
		normal.x, normal.y, normal.z
	);
}