#pragma once
#include <math.h>

namespace ftec {
	class Time {
	public:
		static float deltaTime;
		static float runTime;

		static float sinTime;
		static float cosTime;

		static inline void calculateSinCosTime() {
			sinTime = sin(runTime);
			cosTime = cos(runTime);
		}
	};
}