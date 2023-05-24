#include "header_files/ThirdStageScene.h"
#include "header_files/Player.h"
#include "header_files/Camera.h"
#include "header_files/GameGeometry.h"
#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>
#include <stdio.h>
#include "header_files/Macros.h"
#include "header_files/Stageboard.h"
#include "header_files/CustomShader.h"
#include "header_files/Physics.h"
#include "header_files/Scene.h"

ThirdStageScene* CreateThirdStageScene() {
	ThirdStageScene* scene = malloc(sizeof(ThirdStageScene));

	if (scene == 0) {
		puts("Unable to allocate memory for scene object.");
		exit(1);
	}

	scene->player = CreatePlayer();
	scene->camera = CreateCamera();

	scene->stackable_cubes[0] = (Cube){
		(Vector3) {
			3.0f, 0.0f, 0.0f
		},
		2.0f,
		2.0f,
		2.0f,
		DARKBROWN,
		0
	};

	scene->stackable_cubes[1] = (Cube){
		(Vector3) {
			-6.0f, 0.0f, 0.0f
		},
		2.0f,
		2.0f,
		2.0f,
		DARKBROWN,
		0
	};

	scene->heavy_plate = (Cube){ (Vector3) { 0.0f, -1.0f, -6.0f }, 3, 0, 3, DARKBROWN, 0 };

	scene->next_stage_plate = (Cube){ (Vector3) { 0.0f, -1.0f, 0.0f }, 2, 0, 2, (Color) { 0, 255, 0, 0 } };
	scene->can_draw_next_stage_plate = 0;
	scene->finished_stage = 0;
	scene->stacked_cubes = 0;
	scene->stageboard = CreateStageboard();
	scene->custom_shader = CreateCustomShader();

	scene->player->model.materials[0].shader = scene->custom_shader->shader;
	scene->stageboard->model.materials[0].shader = scene->custom_shader->shader;

	return scene;
}

void UpdateThirdStageScene(ThirdStageScene* scene) {
	UpdatePlayer(scene->player);
	CustomUpdateCamera(scene->camera, scene->player->pos);

	// Checking interaction cubes.
	if (collision_AABB(&scene->player->collision_cube, &scene->stackable_cubes[0])) {
		scene->stackable_cubes[0].pos = Vector3Add(
			scene->stackable_cubes[0].pos,
			scene->player->last_movement);

		if (scene->stacked_cubes) {
			scene->stackable_cubes[1].pos = Vector3Add(
				scene->stackable_cubes[1].pos,
				scene->player->last_movement);
		}
	}

	if (collision_AABB(&scene->player->collision_cube, &scene->stackable_cubes[1])) {
		scene->stackable_cubes[1].pos = Vector3Add(
			scene->stackable_cubes[1].pos,
			scene->player->last_movement);
	}

	if (collision_AABB(&scene->stackable_cubes[0], &scene->stackable_cubes[1])) {
		scene->stacked_cubes = 1;
		scene->stackable_cubes[1].pos.y += scene->stackable_cubes[1].height;
		scene->stackable_cubes[1].pos.x = scene->stackable_cubes[0].pos.x;
		scene->stackable_cubes[1].pos.z = scene->stackable_cubes[0].pos.z;
	}

	if ((plate_collision(&scene->heavy_plate, &scene->stackable_cubes[0]) ||
		plate_collision(&scene->heavy_plate, &scene->stackable_cubes[1])) &&
		scene->stacked_cubes) {
		scene->can_draw_next_stage_plate = 1; 
		scene->heavy_plate.color = GREEN;
	}
	else {
		scene->can_draw_next_stage_plate = 0;
	}

	// Drawing
	ClearBackground(SKYBLUE);

	BeginMode3D(*scene->camera);

	SetShaderValue(scene->custom_shader->shader, scene->custom_shader->shader.locs[SHADER_LOC_VECTOR_VIEW], scene->camera, SHADER_UNIFORM_VEC3);
	UpdateLightValues(&scene->custom_shader->shader, &scene->custom_shader->light);

	DrawCube(
		scene->stackable_cubes[0].pos,
		scene->stackable_cubes[0].width,
		scene->stackable_cubes[0].height,
		scene->stackable_cubes[0].length,
		scene->stackable_cubes[0].color);

	DrawCubeWires(
		scene->stackable_cubes[0].pos,
		scene->stackable_cubes[0].width,
		scene->stackable_cubes[0].height,
		scene->stackable_cubes[0].length,
		scene->stackable_cubes[0].color);

	DrawCube(
		scene->stackable_cubes[1].pos,
		scene->stackable_cubes[1].width,
		scene->stackable_cubes[1].height,
		scene->stackable_cubes[1].length,
		scene->stackable_cubes[1].color);

	DrawCubeWires(
		scene->stackable_cubes[1].pos,
		scene->stackable_cubes[1].width,
		scene->stackable_cubes[1].height,
		scene->stackable_cubes[1].length,
		scene->stackable_cubes[1].color);

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

ThirdStageScene* ResetThirdStageScene(ThirdStageScene* scene) {
	FreeScene((Scene**)&scene);
	return CreateThirdStageScene(scene);
}
