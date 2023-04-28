#include "ThirdStageScene.h"
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

ThirdStageScene* CreateThirdStageScene() {
	ThirdStageScene* scene = malloc(sizeof(ThirdStageScene));

	if (scene == 0) {
		printf("Unable to allocate memory for first scene object.\n");
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
		DARKBROWN,
		0
	};

	scene->interaction_cubes[1] = (Cube){
		(Vector3) {
			-6.0f, 0.0f, 0.0f
		},
		2.0f,
		2.0f,
		2.0f,
		DARKBROWN,
		0
	};

	scene->heavy_plate = (Cube){ (Vector3) { 0.0f, -1.0f, -6.0f }, 3, 0, 3, ORANGE, 0 };

	scene->next_stage_plate = (Cube){ (Vector3) { 0.0f, -1.0f, 0.0f }, 2, 0, 2, (Color) { 0, 255, 0, 0 } };
	scene->can_draw_next_stage_plate = 0;
	scene->finished_stage = 0;
	scene->stacked_cubes = 0;
	scene->stageboard = CreateStageboard();

	return scene;
}

void UpdateThirdStageScene(ThirdStageScene* scene) {
	UpdatePlayer(scene->player);
	CustomUpdateCamera(scene->camera, scene->player);

	// Checking interaction cubes.
	if (collision_AABB(scene->player->collision_cube, scene->interaction_cubes[0])) {
		scene->interaction_cubes[0].pos = Vector3Add(
			scene->interaction_cubes[0].pos,
			scene->player->last_movement);

		if (scene->stacked_cubes) {
			scene->interaction_cubes[1].pos = Vector3Add(
				scene->interaction_cubes[1].pos,
				scene->player->last_movement);
		}
	}

	if (collision_AABB(scene->player->collision_cube, scene->interaction_cubes[1])) {
		scene->interaction_cubes[1].pos = Vector3Add(
			scene->interaction_cubes[1].pos,
			scene->player->last_movement);
	}

	if (collision_AABB(scene->interaction_cubes[0], scene->interaction_cubes[1])) {
		scene->stacked_cubes = 1;
		scene->interaction_cubes[1].pos.y += scene->interaction_cubes[1].height;
		scene->interaction_cubes[1].pos.x = scene->interaction_cubes[0].pos.x;
		scene->interaction_cubes[1].pos.z = scene->interaction_cubes[0].pos.z;
	}

	if ((plate_collision(scene->heavy_plate, scene->interaction_cubes[0]) ||
		plate_collision(scene->heavy_plate, scene->interaction_cubes[1])) &&
		scene->stacked_cubes) {
		scene->can_draw_next_stage_plate = 1; 
		scene->heavy_plate.color = GREEN;
	}
	else {
		scene->can_draw_next_stage_plate = 0;
	}

	// Drawing
	BeginDrawing();

	ClearBackground(SKYBLUE);

	BeginMode3D(*scene->camera);

	for (int i = 0; i < 2; i++) {
		DrawCube(
			scene->interaction_cubes[i].pos,
			scene->interaction_cubes[i].width,
			scene->interaction_cubes[i].height,
			scene->interaction_cubes[i].length,
			scene->interaction_cubes[i].color);

		DrawCubeWires(
			scene->interaction_cubes[i].pos,
			scene->interaction_cubes[i].width,
			scene->interaction_cubes[i].height,
			scene->interaction_cubes[i].length,
			scene->interaction_cubes[i].color);
	}

	DrawCube(
		scene->heavy_plate.pos,
		scene->heavy_plate.width,
		scene->heavy_plate.height,
		scene->heavy_plate.length,
		scene->heavy_plate.color);

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

ThirdStageScene* ResetThirdStageScene(ThirdStageScene* scene) {
	FreeThirdStageScene(scene);
	return CreateThirdStageScene(scene);
}

void FreeThirdStageScene(ThirdStageScene* scene) {
	FreePlayer(scene->player);
	FreeStageboard(scene->stageboard);
	free(scene->camera);
}