#include "Material.h"

#include "GraphicsState.h"
#include "graphics/Cubemap.h"

#include "GL.h"

namespace ftec {

	void Material2D::prepare() const
	{
		Shader &shader = *m_Shader;

		shader.use();

		{
			int matrixModelLocation = shader.getUniformLocation("u_MatrixModel");
			int matrixViewLocation = shader.getUniformLocation("u_MatrixView");
			int matrixProjectionLocation = shader.getUniformLocation("u_MatrixProjection");

			shader.setUniform(matrixModelLocation, GraphicsState::matrixModel);
			shader.setUniform(matrixViewLocation, GraphicsState::matrixView);
			shader.setUniform(matrixProjectionLocation, GraphicsState::matrixProjection);
		}

		{
			//TODO This does not have to change every frame :)
			if (m_TextureMap) {
				glActiveTexture(GL_TEXTURE0);
				m_TextureMap->bind();
				int l = shader.getUniformLocation("u_Textures[0]");
				shader.setUniform(l, 0);
			}
		}
			
	}

	void PBRMaterial::prepare() const
	{
		Shader &shader = *m_Shader;

		shader.use();

		{
			int matrixModelLocation = shader.getUniformLocation("u_MatrixModel");
			int matrixViewLocation = shader.getUniformLocation("u_MatrixView");
			int matrixProjectionLocation = shader.getUniformLocation("u_MatrixProjection");

			shader.setUniform(matrixModelLocation, GraphicsState::matrixModel);
			shader.setUniform(matrixViewLocation, GraphicsState::matrixView);
			shader.setUniform(matrixProjectionLocation, GraphicsState::matrixProjection);
		}

		{
			//TODO This does not have to change every frame :)
			if (m_TextureMap) {
				glActiveTexture(GL_TEXTURE0);
				m_TextureMap->bind();
				int l = shader.getUniformLocation("u_Textures[0]");
				shader.setUniform(l, 0);
			}
			if (m_NormalMap) {
				glActiveTexture(GL_TEXTURE1);
				m_NormalMap->bind();
				int l = shader.getUniformLocation("u_Textures[1]");
				shader.setUniform(l, 1);
			}
			if (m_MetallicMap) {
				glActiveTexture(GL_TEXTURE2);
				m_MetallicMap->bind();
				int l = shader.getUniformLocation("u_Textures[2]");
				shader.setUniform(l, 2);
			}
			if (m_RoughnessMap) {
				glActiveTexture(GL_TEXTURE3);
				m_RoughnessMap->bind();
				int l = shader.getUniformLocation("u_Textures[3]");
				shader.setUniform(l, 3);
			}
		}

		{
			int materialAlbedoLocation = shader.getUniformLocation("u_Material.albedo");
			int materialSpecularLocation = shader.getUniformLocation("u_Material.specular");
			int materialTilingLocation = shader.getUniformLocation("u_Material.tiling");
			int materialRoughnessLocation = shader.getUniformLocation("u_Material.roughness");
			int materialMetallicnessLocation = shader.getUniformLocation("u_Material.metallicness");

			shader.setUniform(materialAlbedoLocation, m_Albedo);
			shader.setUniform(materialSpecularLocation, m_Specular);
			shader.setUniform(materialTilingLocation, m_Tiling);
			shader.setUniform(materialRoughnessLocation, m_Roughness);
			shader.setUniform(materialMetallicnessLocation, m_Metallicness);
		}

		{
			int skyboxLocation = shader.getUniformLocation("u_Skybox");
			if (skyboxLocation > -1) {
				glActiveTexture(GL_TEXTURE0 + GraphicsState::MAX_TEXTURES);
				GraphicsState::m_Skybox->bind();
				shader.setUniform(skyboxLocation, GraphicsState::MAX_TEXTURES);
			}
			glActiveTexture(GL_TEXTURE0);
		}

		{
			int lightEnabledLocation = shader.getUniformLocation("u_Light.enabled");
			int lightDiRectangleionLocation = shader.getUniformLocation("u_Light.direction");
			int lightIntensityLocation = shader.getUniformLocation("u_Light.intensity");
			int lightColorLocation = shader.getUniformLocation("u_Light.color");

			shader.setUniform(lightEnabledLocation, GraphicsState::m_Lights[0].enabled);
			shader.setUniform(lightDiRectangleionLocation, GraphicsState::m_Lights[0].light.m_DiRectangleion);
			shader.setUniform(lightIntensityLocation, GraphicsState::m_Lights[0].light.m_Intensity);
			shader.setUniform(lightColorLocation, Vector3f(
				GraphicsState::m_Lights[0].light.m_Color.x / 255.f,
				GraphicsState::m_Lights[0].light.m_Color.y / 255.f,
				GraphicsState::m_Lights[0].light.m_Color.z / 255.f
			));
		}

		int eyePositionLocation = shader.getUniformLocation("u_EyePosition");
		shader.setUniform(eyePositionLocation, GraphicsState::eyePosition);
	}
}
