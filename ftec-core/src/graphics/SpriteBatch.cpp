#include "SpriteBatch.h"
#include "Renderer.h"
#include "logger/log.h"

namespace ftec {
	SpriteBatch::SpriteBatch()
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

	void SpriteBatch::begin(Primitive primitive, const Material & material)
	{
		if (m_Drawing) {
			LOG_ERROR("Can't begin drawing when drawing");
			return;
		}
		m_Drawing = true;

		this->m_Primitive = primitive;
		this->m_Material = material;

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
		
		//TODO the actual drawing
		//TODO assert that the actual sizes are the same

		if (m_Material.m_Shader && m_Material.m_Texture) {
			Shader &shader = *m_Material.m_Shader;
			Texture &texture = *m_Material.m_Texture;

			shader.use();
			texture.bind();

			//Do stuff 
		}

		//Drawing code here

		//Vertices
		glBindBuffer(GL_ARRAY_BUFFER, m_VerticesVBO);
		glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(vec3f), (void*)&m_Vertices[0], GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(SHADER_ATTRIBUTE_POSITION);
		glVertexAttribPointer(SHADER_ATTRIBUTE_POSITION, 3, GL_FLOAT, false, 0, 0);

		//UVs
		glBindBuffer(GL_ARRAY_BUFFER, m_UvsVBO);
		glBufferData(GL_ARRAY_BUFFER, m_Uvs.size() * sizeof(vec2f), (void*)&m_Uvs[0], GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(SHADER_ATTRIBUTE_UV);
		glVertexAttribPointer(SHADER_ATTRIBUTE_UV, 2, GL_FLOAT, false, 0, 0);

		//Colors
		glBindBuffer(GL_ARRAY_BUFFER, m_ColorsVBO);
		glBufferData(GL_ARRAY_BUFFER, m_Colors.size() * sizeof(color32), (void*) &m_Colors[0], GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(SHADER_ATTRIBUTE_COLOR);
		glVertexAttribPointer(SHADER_ATTRIBUTE_NORMAL, 4, GL_UNSIGNED_BYTE, true, 0, 0);
		
		glDrawArrays(
			GL_TRIANGLES, //TODO primitive mode
			0,
			m_Vertices.size()
			);

		glDisableVertexAttribArray(SHADER_ATTRIBUTE_POSITION);
		glDisableVertexAttribArray(SHADER_ATTRIBUTE_UV);
		glDisableVertexAttribArray(SHADER_ATTRIBUTE_COLOR);

		if (m_Material.m_Shader && m_Material.m_Texture) {
			m_Material.m_Shader->reset();
			m_Material.m_Texture->unbind();
		}
	}

	void SpriteBatch::vertex(const vec3f & position)
	{
		m_Vertices.push_back(position);
		m_Uvs.push_back(m_Uv);
		m_Colors.push_back(m_Color);
		m_Size++;
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