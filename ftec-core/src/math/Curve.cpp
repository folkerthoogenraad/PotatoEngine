#include "Curve.h"

#include "helpers.h"

namespace ftec {
	float ftec::curves::CubicBezier::interpolate(float x) const
	{
		const vec2f p0 = vec2f(0, 0);
		const vec2f p3 = vec2f(1, 1);

		//TODO optimize
		
		vec2f result = tween(//blue
			tween(//red
				tween(//black
					p0,
					p1,
					x
				),
				tween(//black
					p1,
					p2,
					x
				),
				x
			),
			tween(//red
				tween(//black
					p1,
					p2,
					x
				),
				tween(//black
					p2,
					p3,
					x
				),
				x
			),
			x
		);

		return result.y;
	}
}
