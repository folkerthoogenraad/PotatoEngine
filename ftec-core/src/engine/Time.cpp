#include "Time.h"

#include <math.h>

#include <chrono>
#include <thread>

namespace ftec {

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