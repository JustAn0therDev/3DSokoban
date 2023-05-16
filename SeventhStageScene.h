#pragma once
#include "Player.h"
#include "GameGeometry.h"
#include "Camera.h"
#include "Stageboard.h"
#include "CustomShader.h"

typedef struct seventh_stage_scene {
	Player* player;
	Camera* camera;
	Stageboard* stageboard;
	CustomShader* custom_shader;
	Cube immovable_cube;
	Cube unstable_cubes[7];
	Cube mirrored_cubes[2];
	Cube plates[2];
	Cube next_stage_plate;
	int can_draw_next_stage_plate;
	int finished_stage;
	int removed_mirrored_cubes[2];
	int amount_of_unstable_cubes;
} SeventhStageScene;

SeventhStageScene* CreateSeventhStageScene();
void UpdateSeventhStageScene(SeventhStageScene* scene);
SeventhStageScene* ResetSeventhStageScene(SeventhStageScene* scene);
