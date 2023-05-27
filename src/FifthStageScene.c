#include "header_files/FifthStageScene.h"
#include "header_files/Player.h"
#include "header_files/Camera.h"
#include "header_files/GameGeometry.h"
#include "header_files/Macros.h"
#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>
#include <stdio.h>
#include "header_files/Stageboard.h"
#include "header_files/CustomShader.h"
#include "header_files/Physics.h"
#include "header_files/Scene.h"

FifthStageScene* CreateFifthStageScene() {
	FifthStageScene* scene = malloc(sizeof(FifthStageScene));

	if (scene == 0) {
		puts("Unable to allocate memory for scene object.");
		exit(1);
	}

	scene->player = CreatePlayer(1);
	scene->camera = CreateCamera();

	scene->immovable_cube = (Cube){
		(Vector3) {
			0.0f, 0.0f, -3.0f
		},
		2.0f,
		2.0f,
		2.0f,
		BLACK,
		0
	};

	scene->mirrored_cubes[0] = (Cube){
		(Vector3) {
			6.0f, 0.0f, 0.0f
		},
		2.0f,
		2.0f,
		2.0f,
		WHITE,
		0
	};

	scene->mirrored_cubes[1] = (Cube){
		(Vector3) {
			-9.0f, 0.0f, 0.0f
		},
		2.0f,
		2.0f,
		2.0f,
		TRANSPARENT_WHITE,
		0
	};

	scene->mirrored_cubes_amount = 2;

	scene->plates[0] = (Cube){(Vector3) { -3.0f, -1.0f, -6.0f }, 3, 0, 3, DARKPURPLE, 0};
	scene->plates[1] = (Cube){(Vector3) { 3.0f, -1.0f, -6.0f }, 3, 0, 3, DARKPURPLE, 0};

	scene->next_stage_plate = (Cube){ (Vector3) { 0.0f, -1.0f, 0.0f }, 2, 0, 2, (Color) { 0, 255, 0, 0 } };
	scene->can_draw_next_stage_plate = 0;
	scene->finished_stage = 0;
	scene->activated_all_plates = 0;
	scene->stageboard = CreateStageboard();
	scene->custom_shader = CreateCustomShader();

	scene->player->model.materials[0].shader = scene->custom_shader->shader;
	scene->stageboard->model.materials[0].shader = scene->custom_shader->shader;

	return scene;
}

void UpdateFifthStageScene(FifthStageScene* scene) {
	UpdatePlayer(scene->player, 1);
	CustomUpdateCamera(scene->camera, scene->player->pos);

	int object_can_move[2] = { 1, 1 };

	for (int i = 0; i < scene->mirrored_cubes_amount; i++) {
		Cube current_cube = scene->mirrored_cubes[i];
		current_cube.pos = Vector3Add(current_cube.pos, scene->player->last_movement);

		if (collision_AABB(&current_cube, &scene->immovable_cube)) {
			object_can_move[i] = 0;
		}
	}

	// Player cannot move if in contact with immovable cube,
	// so we retrace the player's last step
	if (collision_AABB(&scene->player->collision_cube, &scene->immovable_cube)) {
		scene->player->pos = Vector3Subtract(scene->player->pos, scene->player->last_movement);
	}

	if (collision_AABB(&scene->player->collision_cube, &scene->mirrored_cubes[0])) {
		if (object_can_move[0]) {
			scene->mirrored_cubes[0].pos = Vector3Add(
				scene->mirrored_cubes[0].pos,
				scene->player->last_movement);
		}
		else {
			scene->player->pos = Vector3Subtract(scene->player->pos, scene->player->last_movement);
		}

		if (object_can_move[1]) {
			scene->mirrored_cubes[1].pos = Vector3Add(
				scene->mirrored_cubes[1].pos,
				scene->player->last_movement);
		}
	}

	int activated_all_plates = 1;

	// Checking plate collisions
	if (plate_collision(&scene->plates[0], &scene->mirrored_cubes[0]) || 
		plate_collision(&scene->plates[0], &scene->mirrored_cubes[1])) {
		scene->plates[0].color = GREEN;
	}
	else {
		scene->plates[0].color = DARKPURPLE;
		activated_all_plates = 0;
	}

	if (plate_collision(&scene->plates[1], &scene->mirrored_cubes[0]) ||
		plate_collision(&scene->plates[1], &scene->mirrored_cubes[1])) {
		scene->plates[1].color = GREEN;
	}
	else {
		scene->plates[1].color = DARKPURPLE;
		activated_all_plates = 0;
	}

	if (activated_all_plates) {
		scene->can_draw_next_stage_plate = 1;
	}
	else {
		scene->can_draw_next_stage_plate = 0;
	}

	// Drawing
	ClearBackground(SKYBLUE);

	BeginMode3D(*scene->camera);

	SetShaderValue(scene->custom_shader->shader, scene->custom_shader->shader.locs[SHADER_LOC_VECTOR_VIEW], scene->camera, SHADER_UNIFORM_VEC3);
	UpdateLightValues(&scene->custom_shader->shader, &scene->custom_shader->light);

	for (int i = 0; i < scene->mirrored_cubes_amount; i++) {
		DrawCube(
			scene->mirrored_cubes[i].pos,
			scene->mirrored_cubes[i].width,
			scene->mirrored_cubes[i].height,
			scene->mirrored_cubes[i].length,
			scene->mirrored_cubes[i].color);

		DrawCubeWires(
			scene->mirrored_cubes[i].pos,
			scene->mirrored_cubes[i].width,
			scene->mirrored_cubes[i].height,
			scene->mirrored_cubes[i].length,
			scene->mirrored_cubes[i].color);

		DrawCube(
			scene->plates[i].pos,
			scene->plates[i].width,
			scene->plates[i].height,
			scene->plates[i].length,
			scene->plates[i].color);
	}

	DrawCube(
		scene->immovable_cube.pos,
		scene->immovable_cube.width,
		scene->immovable_cube.height,
		scene->immovable_cube.length,
		scene->immovable_cube.color);

	DrawCubeWires(
		scene->immovable_cube.pos,
		scene->immovable_cube.width,
		scene->immovable_cube.height,
		scene->immovable_cube.length,
		scene->immovable_cube.color);

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

	if (scene->can_draw_next_stage_plate) {
		scene->next_stage_plate.color.a =
			(int)floor(Lerp(scene->next_stage_plate.color.a, 255, 0.1f));
	}
	else {
		scene->next_stage_plate.color.a =
			(int)floor(Lerp(scene->next_stage_plate.color.a, 0, 0.1f));
	}

	DrawCube(
		scene->next_stage_plate.pos,
		scene->next_stage_plate.width,
		scene->next_stage_plate.height,
		scene->next_stage_plate.length,
		scene->next_stage_plate.color);

	EndMode3D();

	if (scene->player->pos.x == scene->next_stage_plate.pos.x &&
		scene->player->pos.z == scene->next_stage_plate.pos.z &&
		scene->can_draw_next_stage_plate) {
		scene->finished_stage = 1;
	}
}

FifthStageScene* ResetFifthStageScene(FifthStageScene* scene) {
	FreeScene((Scene**)&scene);
	return CreateFifthStageScene(scene);
}
