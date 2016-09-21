#include "Renderer.h"

#include "engine/Time.h"
#include "logger/log.h"

namespace ftec {

	void Renderer::drawDirect(const VBORenderable& renderable, const Material & material, const Camera &camera, const mat4& modelMatrix)
	{
		//TODO dont figure this shit out at run time

		int positionIndex = 0;
		int normalIndex = 1;
		int uvIndex = 2;

		if (material.m_Shader && material.m_Texture) {
			Shader &shader = *material.m_Shader;
			Texture &texture = *material.m_Texture;

			shader.use();
			texture.bind();

			//TODO fix this stupid thing with requesting location each frame
			int matrixModelLocation = shader.getUniformLocation("u_MatrixModel");
			int matrixViewLocation = shader.getUniformLocation("u_MatrixView");
			int matrixProjectionLocation = shader.getUniformLocation("u_MatrixProjection");

			shader.setUniform(matrixModelLocation, modelMatrix);
			shader.setUniform(matrixViewLocation, camera.getViewMatrix());
			shader.setUniform(matrixProjectionLocation, camera.getProjectionMatrix());
		
			int mainTextureLocation = shader.getUniformLocation("u_MainTexture");

			shader.setUniform(mainTextureLocation, 0);

			positionIndex = shader.getAttributeLocation("position");
			normalIndex = shader.getAttributeLocation("normal");
			uvIndex = shader.getAttributeLocation("uv");
		}

		glBindBuffer(GL_ARRAY_BUFFER, renderable.m_Vbo);
		//Vertices
		glEnableVertexAttribArray(positionIndex);
		glVertexAttribPointer(positionIndex, 3, GL_FLOAT, false, sizeof(VBORenderable::VBORVertex), 0);
		//Normals
		glEnableVertexAttribArray(normalIndex);
		glVertexAttribPointer(normalIndex, 3, GL_FLOAT, false, sizeof(VBORenderable::VBORVertex), (void*) sizeof(vec3));
		//UVs
		glEnableVertexAttribArray(uvIndex);
		glVertexAttribPointer(uvIndex, 2, GL_FLOAT, false, sizeof(VBORenderable::VBORVertex), (void*) (sizeof(vec3) + sizeof(vec3)));

		glDrawArrays(GL_TRIANGLES, renderable.firstIndex, renderable.lastIndex);

		glDisableVertexAttribArray(positionIndex);
		glDisableVertexAttribArray(normalIndex);
		glDisableVertexAttribArray(uvIndex);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		if (material.m_Shader && material.m_Texture) {
			material.m_Shader->reset();
			material.m_Texture->unbind();
		}
	}
	
	void Renderer::drawDirect(const Mesh & mesh, const Material & material, const Light &light, const Camera & camera, const mat4 & modelMatrix)
	{
		drawDirect(mesh, material, light, camera.getProjectionMatrix(), camera.getViewMatrix(), modelMatrix);
	}

	void Renderer::drawDirect(const Mesh & mesh, const Material & material, const Light &light, const mat4 & projectionMatrix, const mat4 & viewMatrix, const mat4 & modelMatrix)
	{
		//TODO dont figure this shit out at run time

		int positionIndex = 0;
		int normalIndex = 1;
		int uvIndex = 2;

		if (material.m_Shader && material.m_Texture) {
			Shader &shader = *material.m_Shader;
			Texture &texture = *material.m_Texture;

			shader.use();
			texture.bind();

			//TODO fix this stupid thing with requesting location each frame
			int matrixModelLocation = shader.getUniformLocation("u_MatrixModel");
			int matrixViewLocation = shader.getUniformLocation("u_MatrixView");
			int matrixProjectionLocation = shader.getUniformLocation("u_MatrixProjection");

			shader.setUniform(matrixModelLocation, modelMatrix);
			shader.setUniform(matrixViewLocation, viewMatrix);
			shader.setUniform(matrixProjectionLocation, projectionMatrix);

			int mainTextureLocation = shader.getUniformLocation("u_MainTexture");

			shader.setUniform(mainTextureLocation, 0);

			positionIndex = shader.getAttributeLocation("position");
			normalIndex = shader.getAttributeLocation("normal");
			uvIndex = shader.getAttributeLocation("uv");

			//TODO multiple lights and stuffs
			int lightEnabledLocation = shader.getUniformLocation("u_Light.enabled");
			int lightDirectionLocation = shader.getUniformLocation("u_Light.direction");
			int lightShadowsEnabledLocation = shader.getUniformLocation("u_Light.shadowsEnabled");

			shader.setUniform(lightEnabledLocation, light.m_Enabled);
			shader.setUniform(lightDirectionLocation, light.m_Direction);
			shader.setUniform(lightShadowsEnabledLocation, light.isShadowsEnabled());
			
			if (light.isShadowsEnabled()) {
				int lightShadowMatrixLocation = shader.getUniformLocation("u_Light.shadowMatrix");
				int lightShadowTexture = shader.getUniformLocation("u_Light.shadowTexture");

				glActiveTexture(GL_TEXTURE1);

				light.getShadowBuffer()->getDepthTexture()->bind();

				shader.setUniform(lightShadowMatrixLocation, light.getShadowMatrix());
				shader.setUniform(lightShadowTexture, 1);

				glActiveTexture(GL_TEXTURE0);
			}
		}

		//Vertices
		glBindBuffer(GL_ARRAY_BUFFER, mesh.m_VerticesVBO);
		glEnableVertexAttribArray(positionIndex);
		glVertexAttribPointer(positionIndex, 3, GL_FLOAT, false, 0, 0);
		//Normals
		glBindBuffer(GL_ARRAY_BUFFER, mesh.m_NormalsVBO);
		glEnableVertexAttribArray(normalIndex);
		glVertexAttribPointer(normalIndex, 3, GL_FLOAT, false, 0, 0);
		//UVs
		glBindBuffer(GL_ARRAY_BUFFER, mesh.m_UvsVBO);
		glEnableVertexAttribArray(uvIndex);
		glVertexAttribPointer(uvIndex, 2, GL_FLOAT, false, 0, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.m_IndicesVBO);

		glDrawElements(
			GL_TRIANGLES,
			mesh.m_Triangles.size(),
			GL_UNSIGNED_INT,
			(void*)0
		);

		glDisableVertexAttribArray(positionIndex);
		glDisableVertexAttribArray(normalIndex);
		glDisableVertexAttribArray(uvIndex);

		if (material.m_Shader && material.m_Texture) {
			material.m_Shader->reset();
			material.m_Texture->unbind();
		}
	}

	void Renderer::clip(int x, int y, int width, int height)
	{
		glScissor(x, y, width, height);
	}

	void Renderer::viewport(int x, int y, int width, int height)
	{
		glViewport(x, y, width, height);
	}

	void Renderer::renderport(int x, int y, int width, int height)
	{
		viewport(x, y, width, height);
		clip(x, y, width, height);
	}

}
