#include "Renderer.h"

#include "engine/Time.h"
#include "logger/log.h"
#include "scene/Scene.h"
#include "engine/Engine.h"
#include "GraphicsState.h"

namespace ftec {

	void Renderer::drawDirect(const Mesh & mesh)
	{
		GraphicsState::prepare();

		//Vertices
		glBindBuffer(GL_ARRAY_BUFFER, mesh.m_VerticesVBO);
		glEnableVertexAttribArray(SHADER_ATTRIBUTE_POSITION);
		glVertexAttribPointer(SHADER_ATTRIBUTE_POSITION, 3, GL_FLOAT, false, 0, 0);
		//Normals
		glBindBuffer(GL_ARRAY_BUFFER, mesh.m_NormalsVBO);
		glEnableVertexAttribArray(SHADER_ATTRIBUTE_NORMAL);
		glVertexAttribPointer(SHADER_ATTRIBUTE_NORMAL, 3, GL_FLOAT, false, 0, 0);

		//Optional tangents
		if (mesh.m_Tangents.size() > 0) {
			//Normals
			glBindBuffer(GL_ARRAY_BUFFER, mesh.m_TangentsVBO);
			glEnableVertexAttribArray(SHADER_ATTRIBUTE_TANGENT);
			glVertexAttribPointer(SHADER_ATTRIBUTE_TANGENT, 3, GL_FLOAT, false, 0, 0);
		}

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
	}

	void Renderer::clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Renderer::clip(const rect2i &rectangle)
	{
		//Both viewport and clip have 0,0 in the bottom left
		glScissor(rectangle.x(), Engine::getWindow().getHeight() - rectangle.y() - rectangle.height(), rectangle.width(), rectangle.height());
	}
	
	void Renderer::viewport(const rect2i &rectangle)
	{
		//Both viewport and clip have 0,0 in the bottom left
		glViewport(rectangle.x(), Engine::getWindow().getHeight() - rectangle.y() - rectangle.height(), rectangle.width(), rectangle.height());
	}

	void Renderer::renderport(const rect2i &rectangle)
	{
		viewport(rectangle);
		clip(rectangle);
	}

}
