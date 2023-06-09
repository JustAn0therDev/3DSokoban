#pragma once
#include "Player.h"
#include "GameGeometry.h"
#include "Camera.h"
#include "Stageboard.h"
#include "Ui.h"
#include "CustomShader.h"
#include <raylib.h>

typedef struct first_stage_scene {
	Player* player;
	Camera* camera;
	Stageboard* stageboard;
	CustomShader* custom_shader;
	Cube interaction_cube;
	Cube plate;
	Cube next_stage_plate;
	int can_draw_next_stage_plate;
	int finished_stage;
	double creation_time;
	int played_puzzle_solved_audio;
	Sound puzzle_solved_audio;
} FirstStageScene;

FirstStageScene* CreateFirstStageScene();
void UpdateFirstStageScene(FirstStageScene* scene, Ui* ui);
FirstStageScene* ResetFirstStageScene(FirstStageScene* scene);
