#pragma once
#include "Player.h"
#include "GameGeometry.h"
#include "Camera.h"
#include "Stageboard.h"

typedef struct fifth_stage_scene {
	Player* player;
	Cube immovable_cube;
	Cube mirrored_cubes[2];
	Stageboard* stageboard;
	Camera* camera;
	Cube plates[2];
	Cube next_stage_plate;
	int can_draw_next_stage_plate;
	int finished_stage;
	int mirrored_cubes_amount;
	int activated_all_plates;
} FifthStageScene;

FifthStageScene* CreateFifthStageScene();
void UpdateFifthStageScene(FifthStageScene* scene);
FifthStageScene* ResetFifthStageScene(FifthStageScene* scene);
void FreeFifthStageScene(FifthStageScene* scene);