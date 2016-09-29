#pragma once

/*
Potato UI is a user interface system for realtime software. 
Every panel gets an update call every frame and, if needed, every panel
can redraw every frame.

This is not yet implemented, but will be implemented using OpenGL on the
PotatoEngine bases. The PotatoEngine will be fully compatible with the
PotatoUI (obviously).
*/

#include "math/math.h"

namespace potato {
	class PotatoColor {
	public:PotatoColor() = delete; ~PotatoColor() = delete;
	public:
		static ftec::color32 primaryText;
		static ftec::color32 secondaryText;

		static ftec::color32 darkPrimary;
		static ftec::color32 primary;
		static ftec::color32 lightPrimary;

		static ftec::color32 divider;
		static ftec::color32 accent;
		static ftec::color32 iconsText;
	};
}