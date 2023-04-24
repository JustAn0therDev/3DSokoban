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
} Stageboard;

Stageboard* CreateStageboard();
void FreeStageboard(Stageboard* stageboard);