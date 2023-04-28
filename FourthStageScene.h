#pragma once
#include "Player.h"
#include "GameGeometry.h"
#include "Camera.h"
#include "Stageboard.h"

typedef struct fourth_stage_scene {
	Player* player;
	Cube interaction_cube;
	Cube stackable_cubes[2];
	Stageboard* stageboard;
	Camera* camera;
	Cube heavy_plate;
	Cube normal_plate;
	Cube next_stage_plate;
	int can_draw_next_stage_plate;
	int finished_stage;
	int stacked_cubes;
} FourthStageScene;

FourthStageScene* CreateFourthStageScene();
void UpdateFourthStageScene(FourthStageScene* scene);
FourthStageScene* ResetFourthStageScene(FourthStageScene* scene);
void FreeFourthStageScene(FourthStageScene* scene);