#include "Filter.h"

#include "ModularSystem.h"
#include "audio/AudioUtils.h"

#include "logger/log.h"
#include "math/math.h"

namespace ftec {
	Filter::Filter()
	{
		m_Buffer.resize(MODULAR_BUFFER_SIZE);
	}
	void Filter::setInput(AudioModuleOutput out)
	{
		m_Input.function = out;
	}

	void Filter::setAmount(double amount)
	{
		m_Amount = amount;
	}

	void Filter::out(std::vector<double>& input, AudioFormat format)
	{
		if (!m_Input.function)
			return;

		size_t n = m_Buffer.size();

		m_Input.execute(format);

		for (int i = 0; i < n; i++) {
			m_Buffer[i] = std::complex<double>(m_Input.buffer[i], 0);
		}

		fft(m_Buffer);

		double freqPerBin = (double)format.getSampleRate() / n;

		for (int i = 1; i < n / 2; i++) {
			double f = 1;

			if (freqPerBin * i > 440)
				f = 0;

			m_Buffer[i] *= f;
			m_Buffer[n - i] *= f;
		}

		ifft(m_Buffer);

		// Need to downscale because the FFT implementation does not do this
		double scale = 1.0 / m_Buffer.size();

		for (int i = 0; i < n; i++) {
			input[i] = m_Buffer[i].real() *scale;
		}
	}
}
