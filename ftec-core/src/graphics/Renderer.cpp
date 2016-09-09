#include "Renderer.h"

#include "logger/log.h"

namespace ftec {

	void Renderer::draw(const VBORenderable& renderable, const Material & material, const Camera &camera, const mat4& modelMatrix)
	{
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
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(VBORenderable::VBORVertex), 0);
		//Normals
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(VBORenderable::VBORVertex), (void*) sizeof(vec3));
		//UVs
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(VBORenderable::VBORVertex), (void*) (sizeof(vec3) + sizeof(vec3)));

		glDrawArrays(GL_TRIANGLES, renderable.firstIndex, renderable.lastIndex);

		glDisableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		if (material.m_Shader && material.m_Texture) {
			material.m_Shader->reset();
			material.m_Texture->unbind();
		}
	}
}
