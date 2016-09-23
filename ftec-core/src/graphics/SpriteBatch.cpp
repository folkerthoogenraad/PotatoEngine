#include "SpriteBatch.h"
#include "Renderer.h"

namespace ftec {
	SpriteBatch::SpriteBatch()
		:m_Vbo(600), m_Index(0), m_Material(Material::empty), m_Camera(60, 4.f/3.f,.1f,1000.f)
	{}

	SpriteBatch::~SpriteBatch()
	{
	}

	void SpriteBatch::begin()
	{
		m_Drawing = true;
	}

	void SpriteBatch::end()
	{
		flush();
		m_Drawing = false;
	}

	void SpriteBatch::flush()
	{
		if (m_Index <= 0)
			return;

		m_Vbo.update(0, m_Index);
		m_Vbo.firstIndex = 0; //Redundant probably, but for safety
		m_Vbo.lastIndex = m_Index;
		m_Index = 0;

		//Its now ready for rendering
		//Renderer::drawDirect(m_Vbo,m_Material,m_Camera);
	}

	void SpriteBatch::vertex(vec3f p)
	{
		m_Vbo.m_Vertices[m_Index].position = p;
		m_Index++;

		if (m_Index >= m_Vbo.m_Vertices.size())
			flush();
	}

	void SpriteBatch::material(const Material &m)
	{
		if (m_Drawing) {
			if (m_Material != m) {
				flush();
			}
			m_Material = m;
		}else{
			m_Material = m;
		}
	}

	void SpriteBatch::camera(const Camera &c)
	{
		if (m_Drawing) {
			if (m_Camera != c) {
				flush();
			}
			m_Camera = c;
		}
		else {
			m_Camera = c;
		}
	}

}