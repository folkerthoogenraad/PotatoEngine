#include "Time.h"

#include <math.h>
#include <chrono>

namespace ftec {
	float Time::deltaTime = 0;
	float Time::runTime = 0;

	float Time::sinTime = 0;
	float Time::cosTime = 0;
	float Time::sin2Time = 0;
	float Time::cos2Time = 0;

	void Time::calculateSinCosTime()
	{
		sinTime = sinf(runTime);
		cosTime = cosf(runTime);
		sin2Time = sinf(runTime * 2);
		cos2Time = cosf(runTime * 2);
	}

	double Time::currentTimeMilliseconds()
	{
		auto now = std::chrono::high_resolution_clock::now();
		auto t = now.time_since_epoch();

		return (double)t.count() / (double) 1000000.0;
	}
}