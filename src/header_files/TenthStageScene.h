#pragma once
#include "Player.h"
#include "GameGeometry.h"
#include "Camera.h"
#include "Stageboard.h"
#include "CustomShader.h"
#include "Ui.h"

typedef struct tenth_stage_scene {
	Player* player;
	Camera* camera;
	Stageboard* stageboard;
	CustomShader* custom_shader;
	Player* player_two;
	Cube cube_player_one;
	Cube cube_player_two;
    Cube mirrored_cube_player_one;
    Cube mirrored_cube_player_two;
	Cube plates_player_one[2];
	Cube plates_player_two[2];
	Cube next_stage_plate;
	int can_draw_next_stage_plate;
	int finished_stage;
	int player_one_toggle;
	int player_two_toggle;
	int creation_time;
    Vector3 selection_position;
} TenthStageScene;

TenthStageScene* CreateTenthStageScene();
void UpdateTenthStageScene(TenthStageScene* scene, Ui* ui);
TenthStageScene* ResetTenthStageScene(TenthStageScene* scene);
