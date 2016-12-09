#pragma once


namespace ftec {

	class Renderer2D;
	
	struct Drawable2D {
	public:
		virtual void draw(Renderer2D &renderer) = 0;
	};

}