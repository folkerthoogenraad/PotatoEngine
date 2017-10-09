#pragma once

namespace ftec {
	double toGain(double db);

	// All these waveforms have a period of 1 (not 2PI!)
	double audioSine(double input);
	double audioSawtooth(double input);
	double audioTriangle(double input);
	double audioSquare(double input);
}