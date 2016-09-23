#include "Graphics2D.h"
#include "Renderer.h"

namespace ftec {
	void Graphics2D::clip(const rect2i &rectangle)
	{
		this->m_ClippingRectangle = rectangle;

		//TODO Flushing
		Renderer::clip(rectangle);
	}

	void Graphics2D::clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}
