#pragma once
#include "Player.h"
#include "GameGeometry.h"
#include "Camera.h"
#include "Stageboard.h"
#include "CustomShader.h"
#include "Ui.h"

typedef struct ninth_stage_scene {
	Player* player;
	Camera* camera;
	Stageboard* stageboard;
	CustomShader* custom_shader;
	Player* player_two;
    Cube fused_cube;
	Cube cube_player_one;
	Cube cube_player_two;
	Cube plate;
	Cube next_stage_plate;
	int can_draw_next_stage_plate;
    int has_fused_cube;
	int finished_stage;
	int player_one_toggle;
	int player_two_toggle;
	int creation_time;
    Vector3 selection_position;
	int played_puzzle_solved_audio;
	Sound puzzle_solved_audio;
} NinthStageScene;

NinthStageScene* CreateNinthStageScene();
void UpdateNinthStageScene(NinthStageScene* scene, Ui* ui);
NinthStageScene* ResetNinthStageScene(NinthStageScene* scene);
