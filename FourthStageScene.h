#pragma once
#include "Player.h"
#include "GameGeometry.h"
#include "Camera.h"
#include "Stageboard.h"

typedef struct fourth_stage_scene {
	Player* player;
	Camera* camera;
	Stageboard* stageboard;
	Cube interaction_cube;
	Cube stackable_cubes[2];
	Cube heavy_plate;
	Cube normal_plate;
	Cube next_stage_plate;
	int can_draw_next_stage_plate;
	int finished_stage;
	int stacked_cubes;
	int activated_heavy_plate;
	int activated_normal_plate;
} FourthStageScene;

FourthStageScene* CreateFourthStageScene();
void UpdateFourthStageScene(FourthStageScene* scene);
FourthStageScene* ResetFourthStageScene(FourthStageScene* scene);
