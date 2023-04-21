#pragma once
#include "Player.h"
#include "GameGeometry.h"
#include "Camera.h"
#include "Stageboard.h"

typedef struct first_stage_scene {
	Player* player;
	Cube interaction_cube;
	Stageboard* stageboard;
	Camera* camera;
	Plate plate;
	Plate plate_next_stage;
	int can_draw_next_stage_plate;
	Vector3 default_rotation_axis; // TODO: I'm not sure what to do with this...
} FirstStageScene;

FirstStageScene* CreateScene();
void UpdateScene(FirstStageScene* scene);
void FreeScene(FirstStageScene* scene);