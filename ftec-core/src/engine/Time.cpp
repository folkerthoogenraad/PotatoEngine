#include "Time.h"

#include <math.h>

#include <chrono>
#include <thread>

namespace ftec {

	static double getSystemTime()
	{
		auto now = std::chrono::system_clock::now();
		auto duration = now.time_since_epoch();
		auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();

		return ((double)microseconds / 1000000.0);
	}

	Time::Time()
	{
		m_CurrentTime = getSystemTime();
		m_StartTime = m_CurrentTime;
	}

	void Time::calculateSinCosTime()
	{
		sinTime = sinf(runTime);
		cosTime = cosf(runTime);
		sin2Time = sinf(runTime * 2);
		cos2Time = cosf(runTime * 2);
	}

	void Time::update()
	{
		// TODO check for correctness and everything
		double time = getSystemTime();
		deltaTime = (float)(time - m_CurrentTime);
		
		m_CurrentTime = time;
		
		runTime = (float)(m_CurrentTime - m_StartTime);

		calculateSinCosTime();
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