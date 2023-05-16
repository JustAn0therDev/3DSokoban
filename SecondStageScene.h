#pragma once
#include "Player.h"
#include "GameGeometry.h"
#include "Camera.h"
#include "Stageboard.h"
#include "CustomShader.h"

typedef struct second_stage_scene {
	Player* player;
	Camera* camera;
	Stageboard* stageboard;
	CustomShader* custom_shader;
	Cube interaction_cubes[2];
	Cube plates[2];
	Cube next_stage_plate;
	int can_draw_next_stage_plate;
	int finished_stage;
	int plates_amount;
} SecondStageScene;

SecondStageScene* CreateSecondStageScene();
void UpdateSecondStageScene(SecondStageScene* scene);
SecondStageScene* ResetSecondStageScene(SecondStageScene* scene);
