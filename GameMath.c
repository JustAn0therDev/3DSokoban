#include "GameMath.h"

float lerp(float v0, float v1, float t) {
	return (1 - t) * v0 + t * v1;
}

float clamp(float v, float min, float max) {
	if (v < min) {
		return min;
	}

	if (v > max) {
		return max;
	}

	return v;
}