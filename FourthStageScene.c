#include "FourthStageScene.h"
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

FourthStageScene* CreateFourthStageScene() {
	FourthStageScene* scene = malloc(sizeof(FourthStageScene));

	if (scene == 0) {
		printf("Unable to allocate memory for first scene object.\n");
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
		RED,
		0
	};

	scene->stackable_cubes[0] = (Cube){
		(Vector3) {
			6.0f, 0.0f, 0.0f
		},
		2.0f,
		2.0f,
		2.0f,
		DARKBROWN,
		0
		};

	scene->stackable_cubes[1] = (Cube){
		(Vector3) {
			-9.0f, 0.0f, 0.0f
		},
		2.0f,
		2.0f,
		2.0f,
		DARKBROWN,
		0
	};

	scene->heavy_plate = (Cube){ (Vector3) { 0.0f, -1.0f, -6.0f }, 3, 0, 3, ORANGE, 0 };
	scene->normal_plate = (Cube){ (Vector3) { 3.0f, -1.0f, -6.0f }, 3, 0, 3, RED, 0 };

	scene->next_stage_plate = (Cube){ (Vector3) { 0.0f, -1.0f, 0.0f }, 2, 0, 2, (Color) { 0, 255, 0, 0 } };
	scene->can_draw_next_stage_plate = 0;
	scene->finished_stage = 0;
	scene->stacked_cubes = 0;
	scene->stageboard = CreateStageboard();

	return scene;
}

void UpdateFourthStageScene(FourthStageScene* scene) {
	UpdatePlayer(scene->player);
	CustomUpdateCamera(scene->camera, scene->player);

	// Checking stackable cubes.
	if (collision_AABB(scene->player->collision_cube, scene->stackable_cubes[0])) {
		scene->stackable_cubes[0].pos = Vector3Add(
			scene->stackable_cubes[0].pos,
			scene->player->last_movement);

		if (scene->stacked_cubes) {
			scene->stackable_cubes[1].pos = Vector3Add(
				scene->stackable_cubes[1].pos,
				scene->player->last_movement);
		}
	}

	if (collision_AABB(scene->player->collision_cube, scene->stackable_cubes[1])) {
		scene->stackable_cubes[1].pos = Vector3Add(
			scene->stackable_cubes[1].pos,
			scene->player->last_movement);
	}

	if (collision_AABB(scene->stackable_cubes[0], scene->stackable_cubes[1])) {
		scene->stacked_cubes = 1;
		scene->stackable_cubes[1].pos.y += scene->stackable_cubes[1].height;
		scene->stackable_cubes[1].pos.x = scene->stackable_cubes[0].pos.x;
		scene->stackable_cubes[1].pos.z = scene->stackable_cubes[0].pos.z;
	}

	if (((plate_collision(scene->heavy_plate, scene->stackable_cubes[0]) ||
		plate_collision(scene->heavy_plate, scene->stackable_cubes[1])) &&
		scene->stacked_cubes) &&
		plate_collision(scene->normal_plate, scene->interaction_cube)) {
		scene->can_draw_next_stage_plate = 1;
		scene->heavy_plate.color = GREEN;
	}
	else {
		scene->can_draw_next_stage_plate = 0;
	}

	if (plate_collision(scene->normal_plate, scene->interaction_cube)) {
		scene->normal_plate.color = GREEN;
	}
	else {
		scene->normal_plate.color = RED;
	}

	// Checking interactable cubes.
	if (collision_AABB(scene->player->collision_cube, scene->interaction_cube)) {
		scene->interaction_cube.pos = Vector3Add(
			scene->interaction_cube.pos,
			scene->player->last_movement);
	}

	// Drawing
	BeginDrawing();

	ClearBackground(SKYBLUE);

	BeginMode3D(*scene->camera);

	for (int i = 0; i < 2; i++) {
		DrawCube(
			scene->stackable_cubes[i].pos,
			scene->stackable_cubes[i].width,
			scene->stackable_cubes[i].height,
			scene->stackable_cubes[i].length,
			scene->stackable_cubes[i].color);

		DrawCubeWires(
			scene->stackable_cubes[i].pos,
			scene->stackable_cubes[i].width,
			scene->stackable_cubes[i].height,
			scene->stackable_cubes[i].length,
			scene->stackable_cubes[i].color);
	}

	DrawCube(
		scene->interaction_cube.pos,
		scene->interaction_cube.width,
		scene->interaction_cube.height,
		scene->interaction_cube.length,
		scene->interaction_cube.color);

	DrawCubeWires(
		scene->interaction_cube.pos,
		scene->interaction_cube.width,
		scene->interaction_cube.height,
		scene->interaction_cube.length,
		scene->interaction_cube.color);

	DrawCube(
		scene->heavy_plate.pos,
		scene->heavy_plate.width,
		scene->heavy_plate.height,
		scene->heavy_plate.length,
		scene->heavy_plate.color);

	DrawCube(
		scene->normal_plate.pos,
		scene->normal_plate.width,
		scene->normal_plate.height,
		scene->normal_plate.length,
		scene->normal_plate.color);

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
		(Vector3) {
		0.0f, 0.0f, 0.0f
		},
		0,
		scene->stageboard->scale,
		WHITE);

	DrawCubeWires(
		scene->player->collision_cube.pos,
		scene->player->collision_cube.width,
		scene->player->collision_cube.height,
		scene->player->collision_cube.length,
		BLACK);

	if (scene->can_draw_next_stage_plate) {
		scene->next_stage_plate.color.a =
			(int)Lerp(scene->next_stage_plate.color.a, 255, 0.2f);

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

FourthStageScene* ResetFourthStageScene(FourthStageScene* scene) {
	FreeFourthStageScene(scene);
	return CreateFourthStageScene(scene);
}

void FreeFourthStageScene(FourthStageScene* scene) {
	FreePlayer(scene->player);
	FreeStageboard(scene->stageboard);
	free(scene->camera);
}