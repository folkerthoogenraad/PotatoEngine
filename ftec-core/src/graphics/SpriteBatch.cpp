#include "SpriteBatch.h"

#include "GL.h"

#include "Renderer.h"
#include "logger/log.h"

#include "math/Vector3.h"

#include "GraphicsState.h"


namespace ftec {

	// Should be tested what number is good, probably a setting or something
	const int MAX_BATCH_SIZE = 4800;

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
		glGenBuffers(1, &m_VBO);
	}

	SpriteBatch::~SpriteBatch()
	{
		glDeleteBuffers(1, &m_VBO);
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
	}

	void SpriteBatch::flush()
	{
		if (!m_Drawing)
			return;

		end();
		begin(m_Primitive);
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

		//Drawing code here

		// Vertices
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

		// Create or update the data
		if (m_Vertices.size() > m_VBOSize) {
			glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(SpriteBatchVertex), (void*)&m_Vertices[0], GL_DYNAMIC_DRAW);
			m_VBOSize = m_Vertices.size();
		}
		else {
			glBufferSubData(GL_ARRAY_BUFFER, 0, m_Vertices.size() * sizeof(SpriteBatchVertex), (void*)&m_Vertices[0]);
		}

		glEnableVertexAttribArray(SHADER_ATTRIBUTE_POSITION);
		glEnableVertexAttribArray(SHADER_ATTRIBUTE_UV);
		glEnableVertexAttribArray(SHADER_ATTRIBUTE_COLOR);
		glEnableVertexAttribArray(SHADER_ATTRIBUTE_TEXTURE_INDEX);

		const void* positionOffset = (void*) offsetof(SpriteBatchVertex, position);
		const void* uvOffset = (void*) offsetof(SpriteBatchVertex, uv);
		const void* colorOffset = (void*)offsetof(SpriteBatchVertex, color);
		const void* textureOffset = (void*)offsetof(SpriteBatchVertex, texureIndex);


		glVertexAttribPointer(SHADER_ATTRIBUTE_POSITION, 3, GL_FLOAT, false, sizeof(SpriteBatchVertex), positionOffset);
		glVertexAttribPointer(SHADER_ATTRIBUTE_UV, 2, GL_FLOAT, false, sizeof(SpriteBatchVertex), uvOffset);
		glVertexAttribPointer(SHADER_ATTRIBUTE_COLOR, 4, GL_UNSIGNED_BYTE, true, sizeof(SpriteBatchVertex), colorOffset);

		glVertexAttribIPointer(SHADER_ATTRIBUTE_TEXTURE_INDEX, 1, GL_UNSIGNED_BYTE, sizeof(SpriteBatchVertex), textureOffset);

		glDrawArrays(
			glPrimitive(m_Primitive),
			0,
			(GLsizei)m_Vertices.size()
		);

		glDisableVertexAttribArray(SHADER_ATTRIBUTE_POSITION);
		glDisableVertexAttribArray(SHADER_ATTRIBUTE_UV);
		glDisableVertexAttribArray(SHADER_ATTRIBUTE_COLOR);
		glDisableVertexAttribArray(SHADER_ATTRIBUTE_TEXTURE_INDEX);
	}

	void SpriteBatch::depth(float d)
	{
		m_Depth = d;
	}

	void SpriteBatch::vertex(Vector3f position)
	{
		m_BufferVertex.position = std::move(position);
		
		m_Vertices.push_back(m_BufferVertex);
		m_Size++;

		if (m_Size == MAX_BATCH_SIZE)
			m_RequestFlush();
	}

	void SpriteBatch::vertex(Vector2f position)
	{
		vertex(Vector3f(position.x, position.y, m_Depth));
	}

	void SpriteBatch::color(Color32 color)
	{
		m_BufferVertex.color = std::move(color);
	}

	void SpriteBatch::uv(Vector2f uv)
	{
		m_BufferVertex.uv = std::move(uv);
	}

	void SpriteBatch::texureIndex(unsigned char idx)
	{
		m_BufferVertex.texureIndex = idx;
	}

	Primitive SpriteBatch::primitive()
	{
		return m_Primitive;
	}

	void SpriteBatch::setRequestFlush(std::function<void()> func)
	{
		m_RequestFlush = std::move(func);
	}
}