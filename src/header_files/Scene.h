#pragma once
#include "Player.h"
#include "Stageboard.h"
#include "Camera.h"
#include "CustomShader.h"

typedef struct scene {
	Player* player;
	Camera* camera;
	Stageboard* stageboard;
	CustomShader* custom_shader;
} Scene;

void FreeScene(Scene** scene);