#pragma once
#include <math.h>

namespace ftec {
	class Time {
	public:
		static float deltaTime;
		static float runTime;

		static float sinTime;
		static float cosTime;

		static float sin2Time;
		static float cos2Time;

		static inline void calculateSinCosTime() {
			sinTime = sinf(runTime);
			cosTime = cosf(runTime);
			sin2Time = sinf(runTime*2);
			cos2Time = cosf(runTime*2);
		}
	};
}