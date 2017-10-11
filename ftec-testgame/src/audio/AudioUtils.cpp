#include "AudioUtils.h"

#include "math\math.h"

double ftec::toGain(double db)
{
	return pow(10.0, db * 0.05);
}

double ftec::audioSine(double input)
{
	return sin(input * PI * 2);
}

double ftec::audioSawtooth(double input)
{
	double v = fmod(input, 1);
	return lerp(-1.0, 1.0, v);
}

double ftec::audioTriangle(double input)
{
	double v = fmod(input, 1);

	if (v < 0.5)
		return lerp(-1.0, 1.0, v * 2.0);
	else
		return lerp(1.0, -1.0, (v - 0.5) * 2.0);
}

double ftec::audioSquare(double input)
{
	double v = fmod(input, 1);
	return v > 0.5 ? 1 : -1;
}

double ftec::remap(double startMin, double startMax, double min, double max, double value)
{
	return lerp(min, max, invLerp(startMin, startMax, value));
}