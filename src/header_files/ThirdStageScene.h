#pragma once
#include "Player.h"
#include "GameGeometry.h"
#include "Camera.h"
#include "Stageboard.h"
#include "CustomShader.h"

typedef struct third_stage_scene {
	Player* player;
	Camera* camera;
	Stageboard* stageboard;
	CustomShader* custom_shader;
	Cube stackable_cubes[2];
	Cube heavy_plate;
	Cube next_stage_plate;
	int can_draw_next_stage_plate;
	int finished_stage;
	int stacked_cubes;
	int played_puzzle_solved_audio;
	Sound puzzle_solved_audio;
} ThirdStageScene;

ThirdStageScene* CreateThirdStageScene();
void UpdateThirdStageScene(ThirdStageScene* scene);
ThirdStageScene* ResetThirdStageScene(ThirdStageScene* scene);
