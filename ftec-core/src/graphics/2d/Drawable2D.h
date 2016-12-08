#pragma once


namespace ftec {
	
	struct Drawable2D {
	public:
		virtual void draw(Renderer2D &renderer) = 0;
	};

}