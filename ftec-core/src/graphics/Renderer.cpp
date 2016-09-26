#include "Renderer.h"

#include "engine/Time.h"
#include "logger/log.h"
#include "scene/Scene.h"
#include "engine/Engine.h"

namespace ftec {

	/*void Renderer::drawDirect(const VBORenderable& renderable, const Material & material, const Camera &camera, const mat4& modelMatrix)
	{
		//TODO dont figure this shit out at run time

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
		}

		glBindBuffer(GL_ARRAY_BUFFER, renderable.m_Vbo);
		//Vertices
		glEnableVertexAttribArray(SHADER_ATTRIBUTE_POSITION);
		glVertexAttribPointer(SHADER_ATTRIBUTE_POSITION, 3, GL_FLOAT, false, sizeof(VBORenderable::VBORVertex), 0);
		//Normals
		glEnableVertexAttribArray(SHADER_ATTRIBUTE_NORMAL);
		glVertexAttribPointer(SHADER_ATTRIBUTE_NORMAL, 3, GL_FLOAT, false, sizeof(VBORenderable::VBORVertex), (void*) sizeof(vec3f));
		//UVs
		glEnableVertexAttribArray(SHADER_ATTRIBUTE_UV);
		glVertexAttribPointer(SHADER_ATTRIBUTE_UV, 2, GL_FLOAT, false, sizeof(VBORenderable::VBORVertex), (void*) (sizeof(vec3f) + sizeof(vec3f)));

		glDrawArrays(GL_TRIANGLES, renderable.firstIndex, renderable.lastIndex);

		glDisableVertexAttribArray(SHADER_ATTRIBUTE_POSITION);
		glDisableVertexAttribArray(SHADER_ATTRIBUTE_NORMAL);
		glDisableVertexAttribArray(SHADER_ATTRIBUTE_UV);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		if (material.m_Shader && material.m_Texture) {
			material.m_Shader->reset();
			material.m_Texture->unbind();
		}
	}*/
	
	void Renderer::drawDirect(const Mesh & mesh, const Material & material, const Light &light, const Camera & camera, const mat4 & modelMatrix)
	{
		drawDirect(mesh, material, light, camera.getProjectionMatrix(), camera.getViewMatrix(), modelMatrix);
	}

	void Renderer::drawDirect(const Mesh & mesh, const Material & material, const Light &light, const mat4 & projectionMatrix, const mat4 & viewMatrix, const mat4 & modelMatrix)
	{
		//TODO dont figure this shit out at run time

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
		glEnableVertexAttribArray(SHADER_ATTRIBUTE_POSITION);
		glVertexAttribPointer(SHADER_ATTRIBUTE_POSITION, 3, GL_FLOAT, false, 0, 0);
		//Normals
		glBindBuffer(GL_ARRAY_BUFFER, mesh.m_NormalsVBO);
		glEnableVertexAttribArray(SHADER_ATTRIBUTE_NORMAL);
		glVertexAttribPointer(SHADER_ATTRIBUTE_NORMAL, 3, GL_FLOAT, false, 0, 0);
		//UVs
		glBindBuffer(GL_ARRAY_BUFFER, mesh.m_UvsVBO);
		glEnableVertexAttribArray(SHADER_ATTRIBUTE_UV);
		glVertexAttribPointer(SHADER_ATTRIBUTE_UV, 2, GL_FLOAT, false, 0, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.m_IndicesVBO);

		glDrawElements(
			GL_TRIANGLES,
			(GLsizei)mesh.m_Triangles.size(),
			GL_UNSIGNED_INT,
			(void*)0
		);

		glDisableVertexAttribArray(SHADER_ATTRIBUTE_POSITION);
		glDisableVertexAttribArray(SHADER_ATTRIBUTE_NORMAL);
		glDisableVertexAttribArray(SHADER_ATTRIBUTE_UV);

		if (material.m_Shader && material.m_Texture) {
			material.m_Shader->reset();
			material.m_Texture->unbind();
		}
	}

	void Renderer::drawDirect(const Mesh & mesh, const Material & material, const mat4 & modelMatrix)
	{
		//If there is no scene, we cannot draw.
		if (!Engine::getScene())
			return;

		const Scene &scene = *Engine::getScene();

		//TODO dont figure this shit out at run time

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
			shader.setUniform(matrixViewLocation, scene.m_Camera.getViewMatrix());
			shader.setUniform(matrixProjectionLocation, scene.m_Camera.getProjectionMatrix());

			int mainTextureLocation = shader.getUniformLocation("u_MainTexture");

			shader.setUniform(mainTextureLocation, 0);

			//TODO multiple lights and stuffs
			int lightEnabledLocation = shader.getUniformLocation("u_Light.enabled");
			int lightDirectionLocation = shader.getUniformLocation("u_Light.direction");
			int lightShadowsEnabledLocation = shader.getUniformLocation("u_Light.shadowsEnabled");

			shader.setUniform(lightEnabledLocation, scene.m_Light.m_Enabled);
			shader.setUniform(lightDirectionLocation, scene.m_Light.m_Direction);
			shader.setUniform(lightShadowsEnabledLocation, scene.m_Light.isShadowsEnabled());

			if (scene.m_Light.isShadowsEnabled()) {
				int lightShadowMatrixLocation = shader.getUniformLocation("u_Light.shadowMatrix");
				int lightShadowTexture = shader.getUniformLocation("u_Light.shadowTexture");

				glActiveTexture(GL_TEXTURE1);

				scene.m_Light.getShadowBuffer()->getDepthTexture()->bind();

				shader.setUniform(lightShadowMatrixLocation, scene.m_Light.getShadowMatrix());
				shader.setUniform(lightShadowTexture, 1);

				glActiveTexture(GL_TEXTURE0);
			}
		}

		//Vertices
		glBindBuffer(GL_ARRAY_BUFFER, mesh.m_VerticesVBO);
		glEnableVertexAttribArray(SHADER_ATTRIBUTE_POSITION);
		glVertexAttribPointer(SHADER_ATTRIBUTE_POSITION, 3, GL_FLOAT, false, 0, 0);
		//Normals
		glBindBuffer(GL_ARRAY_BUFFER, mesh.m_NormalsVBO);
		glEnableVertexAttribArray(SHADER_ATTRIBUTE_NORMAL);
		glVertexAttribPointer(SHADER_ATTRIBUTE_NORMAL, 3, GL_FLOAT, false, 0, 0);
		//UVs
		glBindBuffer(GL_ARRAY_BUFFER, mesh.m_UvsVBO);
		glEnableVertexAttribArray(SHADER_ATTRIBUTE_UV);
		glVertexAttribPointer(SHADER_ATTRIBUTE_UV, 2, GL_FLOAT, false, 0, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.m_IndicesVBO);

		glDrawElements(
			GL_TRIANGLES,
			(GLsizei)mesh.m_Triangles.size(),
			GL_UNSIGNED_INT,
			(void*)0
		);

		glDisableVertexAttribArray(SHADER_ATTRIBUTE_POSITION);
		glDisableVertexAttribArray(SHADER_ATTRIBUTE_NORMAL);
		glDisableVertexAttribArray(SHADER_ATTRIBUTE_UV);

		if (material.m_Shader && material.m_Texture) {
			material.m_Shader->reset();
			material.m_Texture->unbind();
		}

	}

	void Renderer::clip(const rect2i &rectangle)
	{
		glScissor(rectangle.x(), rectangle.y(), rectangle.width(), rectangle.height());
	}

	void Renderer::viewport(const rect2i &rectangle)
	{
		glViewport(rectangle.x(), rectangle.y(), rectangle.width(), rectangle.height());
	}

	void Renderer::renderport(const rect2i &rectangle)
	{
		viewport(rectangle);
		clip(rectangle);
	}

}
