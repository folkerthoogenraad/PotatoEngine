#include "Time.h"

#include <math.h>

#include <chrono>
#include <thread>

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

	void Time::sleep(float seconds)
	{
		if (seconds <= 0)
			return;

		std::this_thread::sleep_for(std::chrono::milliseconds(
			(long long)(seconds * 1000.0)
		));
	}
}