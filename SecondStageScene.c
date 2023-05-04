#include "SecondStageScene.h"
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

SecondStageScene* CreateSecondStageScene() {
	SecondStageScene* scene = malloc(sizeof(SecondStageScene));

	if (scene == 0) {
		printf("Unable to allocate memory for scene object.\n");
		exit(1);
	}

	scene->player = InitializePlayer();
	scene->camera = CreateCamera();

	scene->interaction_cubes[0] = (Cube){
		(Vector3) {
			3.0f, 0.0f, 0.0f
		},
		2.0f,
		2.0f,
		2.0f,
		RED,
		0
	};

	scene->interaction_cubes[1] = (Cube){
		(Vector3) {
			-6.0f, 0.0f, 0.0f
		},
		2.0f,
		2.0f,
		2.0f,
		RED,
		0
	};

	scene->plates_amount = 2;
	scene->plates[0] = (Cube){ (Vector3) { 3.0f, -1.0f, -6.0f }, 3, 0, 3, RED, 0 };
	scene->plates[1] = (Cube){ (Vector3) { -6.0f, -1.0f, -6.0f }, 3, 0, 3, RED, 0 };

	scene->next_stage_plate = (Cube){ (Vector3) { 0.0f, -1.0f, 0.0f }, 2, 0, 2, (Color) { 0, 255, 0, 0 } };
	scene->can_draw_next_stage_plate = 0;
	scene->finished_stage = 0;
	scene->stageboard = CreateStageboard();

	return scene;
}

void UpdateSecondStageScene(SecondStageScene* scene) {
	UpdatePlayer(scene->player);
	CustomUpdateCamera(scene->camera, scene->player);

	if (collision_AABB(&scene->player->collision_cube, &scene->interaction_cubes[0])) {
		scene->interaction_cubes[0].pos = Vector3Add(
			scene->interaction_cubes[0].pos,
			scene->player->last_movement);
	}

	if (collision_AABB(&scene->player->collision_cube, &scene->interaction_cubes[1])) {
		scene->interaction_cubes[1].pos = Vector3Add(
			scene->interaction_cubes[1].pos,
			scene->player->last_movement);
	}

	int all_plates_activated = 1;

	if (plate_collision(&scene->plates[0], &scene->interaction_cubes[0]) || 
		plate_collision(&scene->plates[0], &scene->interaction_cubes[1])) {
		scene->plates[0].color = GREEN;
	}
	else {
		scene->plates[0].color = RED;
		all_plates_activated = 0;
	}

	if (plate_collision(&scene->plates[1], &scene->interaction_cubes[0]) ||
		plate_collision(&scene->plates[1], &scene->interaction_cubes[1])) {
		scene->plates[1].color = GREEN;
	}
	else {
		scene->plates[1].color = RED;
		all_plates_activated = 0;
	}

	if (all_plates_activated) {
		scene->can_draw_next_stage_plate = 1;
	}
	else {
		scene->can_draw_next_stage_plate = 0;
	}

	// Drawing
	BeginDrawing();

	ClearBackground(SKYBLUE);

	BeginMode3D(*scene->camera);

	for (int i = 0; i < scene->plates_amount; i++) {
		DrawCube(
			scene->interaction_cubes[i].pos,
			scene->interaction_cubes[i].width,
			scene->interaction_cubes[i].height,
			scene->interaction_cubes[i].length,
			scene->interaction_cubes[i].color);

		DrawCube(
			scene->plates[i].pos,
			scene->plates[i].width,
			scene->plates[i].height,
			scene->plates[i].length,
			scene->plates[i].color);

		DrawCubeWires(
			scene->interaction_cubes[i].pos,
			scene->interaction_cubes[i].width,
			scene->interaction_cubes[i].height,
			scene->interaction_cubes[i].length,
			scene->interaction_cubes[i].color);
	}

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
		scene->stageboard->rotation_axis,
		scene->stageboard->rotation_angle,
		scene->stageboard->scale,
		scene->stageboard->color);

	DrawCubeWires(
		scene->player->collision_cube.pos,
		scene->player->collision_cube.width,
		scene->player->collision_cube.height,
		scene->player->collision_cube.length,
		BLACK);

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

SecondStageScene* ResetSecondStageScene(SecondStageScene* scene) {
	FreeSecondStageScene(scene);
	return CreateSecondStageScene(scene);
}

void FreeSecondStageScene(SecondStageScene* scene) {
	FreePlayer(scene->player);
	FreeStageboard(scene->stageboard);
	free(scene->camera);
}