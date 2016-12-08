#include "TestCanvas.h"

#include "math/mat3.h"

#include "graphics/2d/Drawable2D.h"

#include "logger/log.h"

namespace ftec {


	TestCanvas::TestCanvas()
	{

	}

	void TestCanvas::update()
	{

	}

	struct TestDrawing : public Drawable2D
	{
	public:

		void draw(Renderer2D &renderer) override
		{
			Paint paint(renderer, Primitive::QUADS);

			
		}
	};

	void TestCanvas::drawSelf(Graphics2D & graphics)
	{
		Transformation transform(m_Renderer);
		
		TestDrawing test;

		m_Renderer.draw(test);

		transform.translate(10, 10);

		m_Renderer.draw(test);
	}

}