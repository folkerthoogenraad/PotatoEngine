#include "Renderer.h"

#include "engine/Time.h"
#include "logger/log.h"

namespace ftec {

	void Renderer::draw(const VBORenderable& renderable, const Material & material, const Camera &camera, const mat4& modelMatrix)
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
	
	void Renderer::draw(const Mesh & mesh, const Material & material, const Camera & camera, const mat4 & modelMatrix)
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

			//Temp
			int intensityLocation = shader.getUniformLocation("u_Intensity");
			shader.setUniform(intensityLocation, Time::sinTime / 2.0f + 1);

			int lightPositionLocation = shader.getUniformLocation("u_LightPosition");
			shader.setUniform(lightPositionLocation, vec3(Time::cosTime * 8, 2.0, Time::sin2Time * 8));

			positionIndex = shader.getAttributeLocation("position");
			normalIndex = shader.getAttributeLocation("normal");
			uvIndex = shader.getAttributeLocation("uv");
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
}
