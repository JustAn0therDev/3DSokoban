#pragma once
#include "Player.h"
#include "GameGeometry.h"
#include "Camera.h"
#include "Stageboard.h"
#include "CustomShader.h"

typedef struct fifth_stage_scene {
	Player* player;
	Camera* camera;
	Stageboard* stageboard;
	CustomShader* custom_shader;
	Cube immovable_cube;
	Cube mirrored_cubes[2];
	Cube plates[2];
	Cube next_stage_plate;
	int can_draw_next_stage_plate;
	int finished_stage;
	int mirrored_cubes_amount;
	int activated_all_plates;
	int played_puzzle_solved_audio;
	Sound puzzle_solved_audio;
} FifthStageScene;

FifthStageScene* CreateFifthStageScene();
void UpdateFifthStageScene(FifthStageScene* scene);
FifthStageScene* ResetFifthStageScene(FifthStageScene* scene);
