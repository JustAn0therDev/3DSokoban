#include "FirstStageScene.h"
#include "Player.h"
#include "Camera.h"
#include "GameGeometry.h"
#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>
#include <stdio.h>
#include "Macros.h"
#include "Stageboard.h"
#include "Physics.h"

FirstStageScene* CreateFirstStageScene() {
	FirstStageScene* scene = malloc(sizeof(FirstStageScene));

	if (scene == 0) {
		printf("Unable to allocate memory for scene object.\n");
		exit(1);
	}

	scene->player = InitializePlayer();
	scene->camera = CreateCamera();

	scene->interaction_cube = (Cube){
		(Vector3) {
			3.0f, 0.0f, 0.0f
		},
		2.0f,
		2.0f,
		2.0f,
		RED
	};

	scene->plate = (Cube){ (Vector3) { 0.0f, -1.0f, -4.0f }, 3, 0, 3, RED };
	scene->next_stage_plate = (Cube){ (Vector3) { 0.0f, -1.0f, 0.0f }, 2, 0, 2, (Color) { 0, 255, 0, 0 } };
	scene->can_draw_next_stage_plate = 0;
	scene->finished_stage = 0;
	scene->stageboard = CreateStageboard();

	return scene;
}

void UpdateFirstStageScene(FirstStageScene* scene) {
	UpdatePlayer(scene->player);
	CustomUpdateCamera(scene->camera, scene->player);

	if (collision_AABB(&scene->player->collision_cube, &scene->interaction_cube)) {
		scene->interaction_cube.pos =
			Vector3Add(scene->interaction_cube.pos, scene->player->last_movement);
	}

	if (plate_collision(&scene->interaction_cube, &scene->plate)) {
		scene->plate.color = GREEN;
		scene->can_draw_next_stage_plate = 1;
	}
	else {
		scene->plate.color = RED;
		scene->can_draw_next_stage_plate = 0;
	}

	// Drawing
	BeginDrawing();

	ClearBackground(SKYBLUE);

	BeginMode3D(*scene->camera);

	DrawCube(
		scene->interaction_cube.pos,
		scene->interaction_cube.width,
		scene->interaction_cube.height,
		scene->interaction_cube.length,
		scene->interaction_cube.color);

	DrawCube(
		scene->plate.pos,
		scene->plate.width,
		scene->plate.height,
		scene->plate.length,
		scene->plate.color);

	DrawModelEx(
		scene->player->model,
		scene->player->pos,
		scene->player->rotation_axis,
		scene->player->rotation_angle,
		scene->player->scale,
		WHITE);

	DrawModelEx(
		scene->stageboard->model,
		scene->stageboard->pos,
		(Vector3){ 0.0f, 0.0f, 0.0f },
		0,
		scene->stageboard->scale,
		scene->stageboard->color);

	DrawCubeWires(
		scene->player->collision_cube.pos,
		scene->player->collision_cube.width,
		scene->player->collision_cube.height,
		scene->player->collision_cube.length,
		BLACK);

	DrawCubeWires(
		scene->interaction_cube.pos,
		scene->interaction_cube.width,
		scene->interaction_cube.height,
		scene->interaction_cube.length,
		scene->interaction_cube.color);

	if (scene->can_draw_next_stage_plate) {
		scene->next_stage_plate.color.a = 
			(int)Lerp(scene->next_stage_plate.color.a, 255, 0.1f);
		
		DrawCube(
			scene->next_stage_plate.pos,
			scene->next_stage_plate.width,
			scene->next_stage_plate.height,
			scene->next_stage_plate.length,
			scene->next_stage_plate.color);
	}
	else {
		scene->next_stage_plate.color.a = 0;
	}

	EndMode3D();

	if (scene->player->pos.x == scene->next_stage_plate.pos.x &&
		scene->player->pos.z == scene->next_stage_plate.pos.z &&
		scene->can_draw_next_stage_plate) {
		scene->finished_stage = 1;
	}

	EndDrawing();
}

FirstStageScene* ResetFirstStageScene(FirstStageScene* scene) {
	FreeFirstStageScene(scene);
	return CreateFirstStageScene(scene);
}

void FreeFirstStageScene(FirstStageScene* scene) {
	FreePlayer(scene->player);
	FreeStageboard(scene->stageboard);
	free(scene->camera);
}