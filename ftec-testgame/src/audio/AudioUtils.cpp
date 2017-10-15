#include "AudioUtils.h"

#include "math/math.h"
#include "logger/log.h"

#include <algorithm>

namespace ftec{

	double toGain(double db)
	{
		return pow(10.0, db * 0.05);
	}

	double toDB(double gain)
	{
		return 20 * log10(gain);
	}

	double toBarSeconds(double bpm, double beatsPerBar)
	{
		double secondsPerBeat = 60 / bpm;
		return secondsPerBeat * beatsPerBar;
	}

	double semitonesMultiplier(double semitones)
	{
		return pow(2, semitones / 12.0);
	}

	double intervalMultiplier(double from, double to)
	{
		return to / from;
	}

	double audioSine(double input)
	{
		return sin(input * PI * 2);
	}

	double audioSawtooth(double input)
	{
		double v = fmod(input, 1);
		return lerp(-1.0, 1.0, v);
	}

	double audioTriangle(double input)
	{
		double v = fmod(input, 1);

		if (v < 0.5)
			return lerp(-1.0, 1.0, v * 2.0);
		else
			return lerp(1.0, -1.0, (v - 0.5) * 2.0);
	}

	double audioSquare(double input)
	{
		double v = fmod(input, 1);
		return v > 0.5 ? 1 : -1;
	}

	double remap(double startMin, double startMax, double min, double max, double value)
	{
		return lerp(min, max, invLerp(startMin, startMax, value));
	}

	// I am no wizard, stolen from
	// https://www.nayuki.io/page/free-small-fft-in-multiple-languages

	static size_t reverseBits(size_t x, int n) {
		size_t result = 0;
		for (int i = 0; i < n; i++, x >>= 1)
			result = (result << 1) | (x & 1U);
		return result;
	}

	static void transform(std::vector<std::complex<double>> &vec);

	void inverseTransform(std::vector<std::complex<double>> &vec) {
		using namespace std;

		std::transform(vec.cbegin(), vec.cend(), vec.begin(),
			static_cast<complex<double>(*)(const complex<double> &)>(std::conj));
		
		transform(vec);

		std::transform(vec.cbegin(), vec.cend(), vec.begin(),
			static_cast<complex<double>(*)(const complex<double> &)>(std::conj));
	}

	static void transform(std::vector<std::complex<double>> &vec) {
		using namespace std;

		// (TODO optimize this, usually its 1024 samples long anyway, so this can be removed comletelyye)

		// Length variables
		size_t n = vec.size();
		int levels = 0;  // Compute levels = floor(log2(n))
		for (size_t temp = n; temp > 1U; temp >>= 1)
			levels++;
		if (static_cast<size_t>(1U) << levels != n)
			throw "Length is not a power of 2";

		// Trignometric table 
		vector<complex<double> > expTable(n / 2);
		for (size_t i = 0; i < n / 2; i++)
			expTable[i] = std::exp(complex<double>(0, -2 * PI * i / n));

		// Bit-reversed addressing permutation
		for (size_t i = 0; i < n; i++) {
			size_t j = reverseBits(i, levels);
			if (j > i)
				std::swap(vec[i], vec[j]);
		}

		// Cooley-Tukey decimation-in-time radix-2 FFT
		for (size_t size = 2; size <= n; size *= 2) {
			size_t halfsize = size / 2;
			size_t tablestep = n / size;
			for (size_t i = 0; i < n; i += size) {
				for (size_t j = i, k = 0; j < i + halfsize; j++, k += tablestep) {
					complex<double> temp = vec[j + halfsize] * expTable[k];
					vec[j + halfsize] = vec[j] - temp;
					vec[j] += temp;
				}
			}
			if (size == n)  // Prevent overflow in 'size *= 2'
				break;
		}
	}

	static void convolve(
		const std::vector<std::complex<double> > &xvec,
		const std::vector<std::complex<double> > &yvec,
		std::vector<std::complex<double> > &outvec) {
		using namespace std;

		size_t n = xvec.size();
		if (n != yvec.size() || n != outvec.size())
			throw "Mismatched lengths";
		vector<complex<double> > xv(xvec);
		vector<complex<double> > yv(yvec);

		transform(xv);
		transform(yv);
		for (size_t i = 0; i < n; i++) {
			xv[i] *= yv[i];
		}
		inverseTransform(xv);
		for (size_t i = 0; i < n; i++)  // Scaling (because this FFT implementation omits it)
			outvec[i] = xv[i] / static_cast<double>(n);
	}

	double sinc(double x)
	{
		if (x == 0)
			return 1;
		return sin(PI * x) / (PI * x);
	}

	void convolute(std::vector<std::complex<double>>& a, std::vector<std::complex<double>>& b, std::vector<std::complex<double>>& out)
	{
		convolve(a, b, out);
	}

	void ftec::fft(std::vector<std::complex<double>>& samples)
	{
		transform(samples);
	}

	void ftec::ifft(std::vector<std::complex<double>>& frequencies)
	{
		inverseTransform(frequencies);
	}
}