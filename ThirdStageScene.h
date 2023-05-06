#pragma once
#include "Player.h"
#include "GameGeometry.h"
#include "Camera.h"
#include "Stageboard.h"

typedef struct third_stage_scene {
	Player* player;
	Camera* camera;
	Stageboard* stageboard;
	Cube stackable_cubes[2];
	Cube heavy_plate;
	Cube next_stage_plate;
	int can_draw_next_stage_plate;
	int finished_stage;
	int stacked_cubes;
} ThirdStageScene;

ThirdStageScene* CreateThirdStageScene();
void UpdateThirdStageScene(ThirdStageScene* scene);
ThirdStageScene* ResetThirdStageScene(ThirdStageScene* scene);
