#include "SpriteBatch.h"


namespace ftec {
	SpriteBatch::SpriteBatch()
	{
	}

	SpriteBatch::~SpriteBatch()
	{
	}

	void SpriteBatch::begin()
	{
		glBegin(GL_TRIANGLES);
	}

	void SpriteBatch::end()
	{
		glEnd();
	}

	void SpriteBatch::vertex(vec3 p)
	{
		glVertex3f(p.x, p.y, p.z);
	}

}