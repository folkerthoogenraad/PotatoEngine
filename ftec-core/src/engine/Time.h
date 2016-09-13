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
			sinTime = sin(runTime);
			cosTime = cos(runTime);
			sin2Time = sin(runTime*2);
			cos2Time = cos(runTime*2);
		}
	};
}