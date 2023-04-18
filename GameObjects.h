#pragma once
#include <raylib.h>

typedef struct {
	float top;
	float bottom;
	float left;
	float right;
	float front;
	float back;
} CubeFaces;

typedef struct {
	Vector3 pos;
	float width;
	float height;
	float length;
	Color color;
	CubeFaces cube_faces;
	Vector3 scale;
	float rotation_angle;
	Model model;
} Cube;

typedef struct {
	Vector3 pos;
	float width;
	float height;
	float length;
	Color color;
} Plate;