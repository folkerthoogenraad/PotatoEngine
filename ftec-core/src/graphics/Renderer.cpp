#include "Renderer.h"

#include "GL.h"						//For all OpenGL code

#include "math/Vector3.h"
#include "math/Rectangle.h"

#include "engine/Engine.h"			//Shouldn't be needed.
#include "graphics/Window.h"		//Shouldn't be needed.

#include "Mesh.h"					//For mesh rendering

#include "GraphicsState.h"			//For state objects

namespace ftec {

	void setupMesh(const Mesh & mesh)
	{
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
	}

	void Renderer::drawDirect(const Mesh & mesh)
	{
		GraphicsState::prepare();

		setupMesh(mesh);

		glDrawElements(
			GL_TRIANGLES,
			(GLsizei)mesh.m_Triangles.size(),
			GL_UNSIGNED_INT,
			(void*)0
		);

		//glDisableVertexAttribArray(SHADER_ATTRIBUTE_POSITION);
		//glDisableVertexAttribArray(SHADER_ATTRIBUTE_NORMAL);
		//glDisableVertexAttribArray(SHADER_ATTRIBUTE_UV);
	}

	void Renderer::drawDirect(const Mesh & mesh, const InstanceList &instances)
	{
		GraphicsState::prepare();

		setupMesh(mesh);

		glEnableVertexAttribArray(SHADER_ATTRIBUTE_INSTANCE_POSITION);
		glBindBuffer(GL_ARRAY_BUFFER, instances.m_Vbo);
		glVertexAttribPointer(SHADER_ATTRIBUTE_INSTANCE_POSITION, 3, GL_FLOAT, false, 0, 0);
		glVertexAttribDivisor(SHADER_ATTRIBUTE_INSTANCE_POSITION, 1);

		glDrawElementsInstanced(
			GL_TRIANGLES,
			(GLsizei)mesh.m_Triangles.size(),
			GL_UNSIGNED_INT,
			(void*)0,
			(GLsizei) instances.m_Positions.size()
		);

		glDisableVertexAttribArray(SHADER_ATTRIBUTE_INSTANCE_POSITION);

		//glDisableVertexAttribArray(SHADER_ATTRIBUTE_POSITION);
		//glDisableVertexAttribArray(SHADER_ATTRIBUTE_NORMAL);
		//glDisableVertexAttribArray(SHADER_ATTRIBUTE_UV);
	}

	void Renderer::clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Renderer::clip(const Rectanglei &rectangle)
	{
		//TODO this is stupid, pls fix folkert.

		//Both viewport and clip have 0,0 in the bottom left
		glScissor(rectangle.x(), (int)Engine::getWindow().getHeight() - rectangle.y() - rectangle.height(), rectangle.width(), rectangle.height());
	}
	
	void Renderer::viewport(const Rectanglei &rectangle)
	{
		//Both viewport and clip have 0,0 in the bottom left
		glViewport(rectangle.x(), (int)Engine::getWindow().getHeight() - rectangle.y() - rectangle.height(), rectangle.width(), rectangle.height());
	}

	void Renderer::renderport(const Rectanglei &rectangle)
	{
		viewport(rectangle);
		clip(rectangle);
	}

	InstanceList::InstanceList()
	{
		glGenBuffers(1, &m_Vbo);
	}

	InstanceList::~InstanceList()
	{
		glDeleteBuffers(1, &m_Vbo);
	}

	void InstanceList::upload()
	{
		if (m_Positions.size() < 1)
			return;

		glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);

		glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3f) * m_Positions.size(), &m_Positions[0], GL_STATIC_DRAW); //Maybe dynamic, because instancing?

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

}
