#pragma once

namespace ftec {
	class Time {
	public:
		float deltaTime;
		float runTime;

		float sinTime;
		float cosTime;

		float sin2Time;
		float cos2Time;

		void calculateSinCosTime();

		static void sleep(float seconds);
	};
}