#pragma once
#include <raylib.h>

typedef struct stageboard {
	Vector3 pos;
	Vector3 scale;
	Model model;
	Texture* texture_ptr;
	float length;
	float width;
	float height;
	Color color;
	float rotation_angle;
	Vector3 rotation_axis;
} Stageboard;

Stageboard* CreateStageboard();
void FreeStageboard(Stageboard* stageboard);