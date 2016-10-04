#include "GraphicsState.h"

#include <string>
#include <sstream>

#include "Shader.h"
#include "Cubemap.h"
#include "Texture.h"
#include "logger/log.h"

namespace ftec {

	bool GraphicsState::m_LightEnabled = false;
	bool GraphicsState::m_TextureEnabled = true;
	std::shared_ptr<Cubemap> GraphicsState::m_Skybox = nullptr;

	mat4 GraphicsState::matrixModel;
	mat4 GraphicsState::matrixView;
	mat4 GraphicsState::matrixProjection;
	vec3f GraphicsState::eyePosition;

	Material GraphicsState::m_Material(nullptr, nullptr);
	//TextureSlot GraphicsState::m_Textures[MAX_TEXTURES];
	LightSlot GraphicsState::m_Lights[MAX_LIGHTS];

	void GraphicsState::prepare()
	{
		if (!m_Material.m_Shader) {
			LOG("Graphics state shader is null");
			return;
		}

		Shader &shader = *m_Material.m_Shader;

		shader.use();

		int matrixModelLocation = shader.getUniformLocation("u_MatrixModel");
		int matrixViewLocation = shader.getUniformLocation("u_MatrixView");
		int matrixProjectionLocation = shader.getUniformLocation("u_MatrixProjection");

		shader.setUniform(matrixModelLocation, matrixModel);
		shader.setUniform(matrixViewLocation, matrixView);
		shader.setUniform(matrixProjectionLocation, matrixProjection);

		if (m_TextureEnabled) {
			//This does not have to change every frame :)
			if (m_Material.m_TextureMap) {
				glActiveTexture(GL_TEXTURE0);
				m_Material.m_TextureMap->bind();
				int l = shader.getUniformLocation("u_Textures[0]");
				shader.setUniform(l, 0);
			}
			if (m_Material.m_NormalMap) {
				glActiveTexture(GL_TEXTURE1);
				m_Material.m_NormalMap->bind();
				int l = shader.getUniformLocation("u_Textures[1]");
				shader.setUniform(l, 1);
			}
		}

		int materialAlbedoLocation = shader.getUniformLocation("u_Material.albedo");
		int materialSpecularLocation = shader.getUniformLocation("u_Material.specular");
		int materialTilingLocation = shader.getUniformLocation("u_Material.tiling");
		int materialBumpinessLocation = shader.getUniformLocation("u_Material.bumpiness");
		int materialRoughnessLocation = shader.getUniformLocation("u_Material.roughness");
		int materialMetallicnessLocation = shader.getUniformLocation("u_Material.metallicness");

		shader.setUniform(materialAlbedoLocation, m_Material.m_Albedo);
		shader.setUniform(materialSpecularLocation, m_Material.m_Specular);
		shader.setUniform(materialTilingLocation, m_Material.m_Tiling);
		shader.setUniform(materialBumpinessLocation, m_Material.m_Bumpiness);
		shader.setUniform(materialRoughnessLocation, m_Material.m_Roughness);
		shader.setUniform(materialMetallicnessLocation, m_Material.m_Metallicness);

		int skyboxLocation = shader.getUniformLocation("u_Skybox");
		if (skyboxLocation > -1) {
			glActiveTexture(GL_TEXTURE0 + MAX_TEXTURES);
			m_Skybox->bind();
			shader.setUniform(skyboxLocation, MAX_TEXTURES);
		}
		glActiveTexture(GL_TEXTURE0);

		if (m_LightEnabled) {
			int lightEnabledLocation = shader.getUniformLocation("u_Light.enabled");
			int lightDirectionLocation = shader.getUniformLocation("u_Light.direction");
			int lightIntensityLocation = shader.getUniformLocation("u_Light.intensity");
			int lightColorLocation = shader.getUniformLocation("u_Light.color");

			shader.setUniform(lightEnabledLocation, m_Lights[0].enabled);
			shader.setUniform(lightDirectionLocation, m_Lights[0].light.m_Direction);
			shader.setUniform(lightIntensityLocation, m_Lights[0].light.m_Intensity);
			shader.setUniform(lightColorLocation, vec3f(
				m_Lights[0].light.m_Color.x / 255.f,
				m_Lights[0].light.m_Color.y / 255.f,
				m_Lights[0].light.m_Color.z / 255.f
			));
		}

		int eyePositionLocation = shader.getUniformLocation("u_EyePosition");
		shader.setUniform(eyePositionLocation, eyePosition);
	}

}