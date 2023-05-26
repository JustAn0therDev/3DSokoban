#pragma once
#include "Player.h"
#include "GameGeometry.h"
#include "Camera.h"
#include "Stageboard.h"
#include "CustomShader.h"
#include "Ui.h"

typedef struct eighth_stage_scene {
	Player* player;
	Camera* camera;
	Stageboard* stageboard;
	CustomShader* custom_shader;
	Player* player_two;
	Cube cube_player_one;
	Cube cube_player_two;
	Cube plates[2];
	Cube next_stage_plate;
	int can_draw_next_stage_plate;
	int finished_stage;
	int player_one_toggle;
	int player_two_toggle;
	int creation_time;
} EighthStageScene;

EighthStageScene* CreateEighthStageScene();
void UpdateEighthStageScene(EighthStageScene* scene, Ui* ui);
EighthStageScene* ResetEighthStageScene(EighthStageScene* scene);
