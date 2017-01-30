#pragma once

namespace ftec {
	class Time {
	public:
		static float deltaTime;
		static float runTime;

		static float sinTime;
		static float cosTime;

		static float sin2Time;
		static float cos2Time;

		static void calculateSinCosTime();

		static double currentTimeMilliseconds();
	};
}