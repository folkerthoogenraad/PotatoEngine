#pragma once

namespace ftec {
	class IIRFilter {
	public:
		enum FilterType {
			LowPass,
			HighPass,
			BandPass,
			Notch,
			Peak,
			LowShelf,
			HighShelf
		};
	private:
		double a0 = 1;
		double a1 = 0;
		double a2 = 0;
		double b1 = 0;
		double b2 = 0;
		double z1 = 0;
		double z2 = 0;

	public:
		void setFilter(FilterType type, double filterCutoff, double Q, double peakGain);

		inline float process(float in) {
			double out = in * a0 + z1;
			z1 = in * a1 + z2 - b1 * out;
			z2 = in * a2 - b2 * out;
			return out;
		}
	};
}