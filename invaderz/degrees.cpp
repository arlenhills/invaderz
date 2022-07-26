#include "degrees.hpp"

float limitDeg(float angle)
{
	//Thank you, Stackoverflow!
	return static_cast<float>(fmod(360 + fmod(angle, 360), 360));
}
