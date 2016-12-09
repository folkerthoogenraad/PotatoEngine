#include "Curve.h"

#include "math.h"

namespace ftec {
	float ftec::curves::CubicBezier::interpolate(float x) const
	{
		const Vector2f p0 = Vector2f(0, 0);
		const Vector2f p3 = Vector2f(1, 1);

		//TODO optimize
		
		Vector2f result = tween(//blue
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
