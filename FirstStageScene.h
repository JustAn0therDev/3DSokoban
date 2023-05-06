#pragma once
#include "Player.h"
#include "GameGeometry.h"
#include "Camera.h"
#include "Stageboard.h"

typedef struct first_stage_scene {
	Player* player;
	Camera* camera;
	Stageboard* stageboard;
	Cube interaction_cube;
	Cube plate;
	Cube next_stage_plate;
	int can_draw_next_stage_plate;
	int finished_stage;
} FirstStageScene;

FirstStageScene* CreateFirstStageScene();
void UpdateFirstStageScene(FirstStageScene* scene);
FirstStageScene* ResetFirstStageScene(FirstStageScene* scene);
