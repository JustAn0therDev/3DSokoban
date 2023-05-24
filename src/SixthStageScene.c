#include "header_files/SixthStageScene.h"
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

SixthStageScene* CreateSixthStageScene() {
	SixthStageScene* scene = malloc(sizeof(SixthStageScene));

	if (scene == 0) {
		puts("Unable to allocate memory for scene object.");
		exit(1);
	}

	scene->player = CreatePlayer();
	scene->camera = CreateCamera();

	scene->unstable_cube = (Cube){
		(Vector3) {
			3.0f, 0.0f, 0.0f
		},
		2.0f,
		2.0f,
		2.0f,
		BLACK
	};

	scene->interaction_cube = (Cube){
		(Vector3) {
			6.0f, 0.0f, 0.0f
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
	scene->removed_interaction_cube = 0;
	scene->custom_shader = CreateCustomShader();

	scene->player->model.materials[0].shader = scene->custom_shader->shader;
	scene->stageboard->model.materials[0].shader = scene->custom_shader->shader;

	return scene;
}

void UpdateSixthStageScene(SixthStageScene* scene) {
	UpdatePlayer(scene->player);
	CustomUpdateCamera(scene->camera, scene->player->pos);

	if (collision_AABB(&scene->player->collision_cube, &scene->unstable_cube)) {
		scene->unstable_cube.pos =
			Vector3Add(scene->unstable_cube.pos, scene->player->last_movement);
	}

	if (scene->removed_interaction_cube == 0 && collision_AABB(&scene->player->collision_cube, &scene->interaction_cube)) {
		scene->interaction_cube.pos =
			Vector3Add(scene->interaction_cube.pos, scene->player->last_movement);
	}

	if (plate_collision(&scene->unstable_cube, &scene->plate) && scene->removed_interaction_cube) {
		scene->plate.color = GREEN;
		scene->can_draw_next_stage_plate = 1;
	}
	else {
		scene->plate.color = RED;
		scene->can_draw_next_stage_plate = 0;
	}

	if (collision_AABB(&scene->interaction_cube, &scene->unstable_cube)) {
		scene->interaction_cube.color.a = 0;
		scene->removed_interaction_cube = 1;
	}

	// Drawing
	ClearBackground(SKYBLUE);

	BeginMode3D(*scene->camera);

	SetShaderValue(scene->custom_shader->shader, scene->custom_shader->shader.locs[SHADER_LOC_VECTOR_VIEW], scene->camera, SHADER_UNIFORM_VEC3);
	UpdateLightValues(&scene->custom_shader->shader, &scene->custom_shader->light);

	// Unstable cubes "eats" (or removes) other cubes and their colors vary a lot.
	unsigned char r = rand() % UCHAR_MAX;
	unsigned char g = rand() % UCHAR_MAX;
	unsigned char b = rand() % UCHAR_MAX;

	DrawCube(
		scene->unstable_cube.pos,
		scene->unstable_cube.width,
		scene->unstable_cube.height,
		scene->unstable_cube.length,
		(Color) {
		r, g, b, UCHAR_MAX
	});

	if (!scene->removed_interaction_cube) {
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
	}

	DrawCube(
		scene->plate.pos,
		scene->plate.width,
		scene->plate.height,
		scene->plate.length,
		(Color) { r, g, b, UCHAR_MAX });

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

SixthStageScene* ResetSixthStageScene(SixthStageScene* scene) {
	FreeScene((Scene**)&scene);
	return CreateSixthStageScene(scene);
}
