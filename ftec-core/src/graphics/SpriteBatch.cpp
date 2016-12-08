#include "SpriteBatch.h"
#include "Renderer.h"
#include "logger/log.h"

#include "GraphicsState.h"

namespace ftec {

	inline GLenum glPrimitive(const Primitive &p)
	{
		switch (p)
		{
		case Primitive::LINES:
			return GL_LINES;
		case Primitive::QUADS:
			return GL_QUADS;
		case Primitive::POINTS:
			return GL_POINTS;
		default:
			return GL_TRIANGLES;
		}
	}

	SpriteBatch::SpriteBatch() : m_Drawing(false), m_VBOSize(0)
	{
		glGenBuffers(1, &m_VerticesVBO);
		glGenBuffers(1, &m_ColorsVBO);
		glGenBuffers(1, &m_UvsVBO);
	}

	SpriteBatch::~SpriteBatch()
	{
		glDeleteBuffers(1, &m_VerticesVBO);
		glDeleteBuffers(1, &m_ColorsVBO);
		glDeleteBuffers(1, &m_UvsVBO);
	}

	void SpriteBatch::begin(Primitive primitive)
	{
		if (m_Drawing) {
			LOG_ERROR("Can't begin drawing when drawing");
			return;
		}
		m_Drawing = true;

		this->m_Primitive = primitive;

		m_Size = 0;
		m_Vertices.clear();
		m_Uvs.clear();
		m_Colors.clear();
	}

	void SpriteBatch::end()
	{
		if (!m_Drawing) {
			LOG_ERROR("Can't stop drawing when not drawing");
			return;
		}
		m_Drawing = false;

		//We don't have to draw if we don't have to draw <3
		if (m_Vertices.size() <= 0)
			return;

		bool resize = m_Vertices.size() > m_VBOSize;

		//TODO the actual drawing
		//TODO assert that the actual sizes are the same

		GraphicsState::prepare();

		//Drawing code here

		//Vertices
		glBindBuffer(GL_ARRAY_BUFFER, m_VerticesVBO);

		if (resize) {
			glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(vec3f), (void*)&m_Vertices[0], GL_DYNAMIC_DRAW);
		}
		else {
			glBufferSubData(GL_ARRAY_BUFFER, 0, m_Vertices.size() * sizeof(vec3f), (void*)&m_Vertices[0]);
		}
		glEnableVertexAttribArray(SHADER_ATTRIBUTE_POSITION);
		glVertexAttribPointer(SHADER_ATTRIBUTE_POSITION, 3, GL_FLOAT, false, 0, 0);

		//UVs
		glBindBuffer(GL_ARRAY_BUFFER, m_UvsVBO);
		if (resize) {
			glBufferData(GL_ARRAY_BUFFER, m_Uvs.size() * sizeof(vec2f), (void*)&m_Uvs[0], GL_DYNAMIC_DRAW);
		}
		else {
			glBufferSubData(GL_ARRAY_BUFFER, 0, m_Uvs.size() * sizeof(vec2f), (void*)&m_Uvs[0]);
		}
		glEnableVertexAttribArray(SHADER_ATTRIBUTE_UV);
		glVertexAttribPointer(SHADER_ATTRIBUTE_UV, 2, GL_FLOAT, false, 0, 0);

		//Colors
		glBindBuffer(GL_ARRAY_BUFFER, m_ColorsVBO);
		if (resize) {
			glBufferData(GL_ARRAY_BUFFER, m_Colors.size() * sizeof(color32), (void*)&m_Colors[0], GL_DYNAMIC_DRAW);
		}
		else {
			glBufferSubData(GL_ARRAY_BUFFER, 0, m_Colors.size() * sizeof(color32), (void*)&m_Colors[0]);
		}
		glEnableVertexAttribArray(SHADER_ATTRIBUTE_COLOR);
		glVertexAttribPointer(SHADER_ATTRIBUTE_COLOR, 4, GL_UNSIGNED_BYTE, true, 0, 0);
		
		glDrawArrays(
			glPrimitive(m_Primitive),
			0,
			(GLsizei) m_Vertices.size()
			);

		glDisableVertexAttribArray(SHADER_ATTRIBUTE_POSITION);
		glDisableVertexAttribArray(SHADER_ATTRIBUTE_UV);
		glDisableVertexAttribArray(SHADER_ATTRIBUTE_COLOR);
	}

	void SpriteBatch::depth(float d)
	{
		m_Depth = d;
	}

	void SpriteBatch::vertex(const vec3f & position)
	{
		m_Vertices.push_back(position);
		m_Uvs.push_back(m_Uv);
		m_Colors.push_back(m_Color);
		m_Size++;
	}

	void SpriteBatch::vertex(const vec2f & position)
	{
		vertex(vec3f(position.x, position.y, m_Depth));
	}

	void SpriteBatch::color(const color32 & color)
	{
		m_Color = color;
	}

	void SpriteBatch::uv(const vec2f & uv)
	{
		m_Uv = uv;
	}
}