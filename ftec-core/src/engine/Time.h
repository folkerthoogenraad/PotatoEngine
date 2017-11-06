#pragma once

namespace ftec {

	/**
	 * Time class for all things with time
	*/
	class Time {
	private:
		double m_CurrentTime;
		double m_StartTime;
	public:
		Time();

		float deltaTime; /**< Delta time since previous update()*/
		float runTime; /**< Runtime since starting up (only updates every update())*/

		float sinTime;
		float cosTime;

		float sin2Time;
		float cos2Time;

		/**
		 * Calculates sinTime, cosTime, sin2Time, cos2Time.
		*/
		void calculateSinCosTime();

		/**
		 * Updates the deltaTime and runTime
		*/
		void update();

		/**
		 * Sleeps for seconds
		*/
		static void sleep(float seconds);
	};
}