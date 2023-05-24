#pragma once
#include <raylib.h>

typedef struct cube {
	Vector3 pos;
	float width;
	float height;
	float length;
	Color color;
	int activated;
} Cube;
