#include "TestCanvas.h"

#include "math/Matrix3.h"

#include "graphics/2d/Drawable2D.h"
#include "engine/Time.h"

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

			paint.color(Color32::white());
			paint.depth(0);

			paint.vertex(-1, -1);
			paint.vertex(1, -1);
			paint.vertex(1, 1);
			paint.vertex(-1, 1);
		}
	};

	void TestCanvas::drawSelf(Graphics2D & graphics)
	{
		Transformation transform(m_Renderer);
		transform.scale(0.009f, 0.016f);
		
		TestDrawing test;
		
		for (int y = -20; y < 20; y++) {
			for (int x = -20; x < 20; x++) {
				Transformation transform(m_Renderer);
				
				transform.translate(y * 3 + Time::sinTime, x * 3);
				
				test.draw(m_Renderer);
			}
		}

	}

}