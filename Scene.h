#pragma once
#include "Player.h"
#include "Stageboard.h"
#include "Camera.h"

typedef struct scene {
	Player* player;
	Camera* camera;
	Stageboard* stageboard;
} Scene;

void FreeScene(Scene* scene);