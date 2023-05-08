#pragma once
#include "Player.h"
#include "GameGeometry.h"
#include "Camera.h"
#include "Stageboard.h"

typedef struct sixth_stage_scene {
	Player* player;
	Camera* camera;
	Stageboard* stageboard;
	Cube unstable_cube;
	Cube interaction_cube;
	Cube plate;
	Cube next_stage_plate;
	int can_draw_next_stage_plate;
	int finished_stage;
	int removed_interaction_cube;
} SixthStageScene;

SixthStageScene* CreateSixthStageScene();
void UpdateSixthStageScene(SixthStageScene* scene);
SixthStageScene* ResetSixthStageScene(SixthStageScene* scene);
