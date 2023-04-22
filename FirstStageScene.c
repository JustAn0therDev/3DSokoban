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
		printf("Unable to allocate memory for scene.\n");
		exit(1);
	}

	scene->player = InitializePlayer();
	scene->camera = GetCamera();

	scene->interaction_cube = (Cube){
		(Vector3) {
			3.0f, 0.0f, 0.0f
		},
		2.0f,
		2.0f,
		2.0f,
		RED
	};

	scene->plate = (Cube){ (Vector3) { 0.0f, 0.0f, -4.0f }, 2, 0, 2, RED };
	scene->plate_next_stage = (Cube){ (Vector3) { 0.0f, -1.0f, 0.0f }, 2, 0, 2, (Color) { 0, 255, 0, 0 } };
	scene->can_draw_next_stage_plate = 0;
	scene->finished_stage = 0;
	scene->stageboard = GetStageboard();

	return scene;
}

void UpdateFirstStageScene(FirstStageScene* scene) {
	UpdatePlayer(scene->player);
	UpdateSokobanCamera(scene->camera, scene->player);

	if (collision_AABB(scene->player->collision_cube, scene->interaction_cube)) {
		scene->interaction_cube.pos =
			Vector3Add(scene->interaction_cube.pos, scene->player->last_movement);
	}

	if (collision_AABB(scene->interaction_cube, scene->plate)) {
		scene->plate.color = GREEN;
		scene->interaction_cube.color = GREEN;
		scene->can_draw_next_stage_plate = 1;
	}
	else {
		scene->plate.color = RED;
		scene->interaction_cube.color = RED;
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
		(Vector3){0.0f, 0.0f, 0.0f},
		0,
		scene->stageboard->scale,
		WHITE);

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
		scene->plate_next_stage.color.a = Lerp(scene->plate_next_stage.color.a, 255, 0.1f);
		DrawCube(
			scene->plate_next_stage.pos,
			scene->plate_next_stage.width,
			scene->plate_next_stage.height,
			scene->plate_next_stage.length,
			scene->plate_next_stage.color);
	}
	else {
		scene->plate_next_stage.color.a = 0;
	}

	EndMode3D();

	if (scene->player->pos.x == scene->plate_next_stage.pos.x &&
		scene->player->pos.z == scene->plate_next_stage.pos.z &&
		scene->can_draw_next_stage_plate) {
		DrawText(
			"NICE CAULK!!1",
			(WIDTH / 2) - 150,
			HEIGHT / 2,
			48,
			GREEN);
		scene->finished_stage = 1;
	}

	EndDrawing();
}

void FreeFirstStageScene(FirstStageScene* scene) {
	FreePlayer(scene->player);
	FreeStageboard(scene->stageboard);
	free(scene->camera);
}