#include "header_files/FirstStageScene.h"
#include "header_files/Player.h"
#include "header_files/Camera.h"
#include "header_files/GameGeometry.h"
#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>
#include <stdio.h>
#include "header_files/Macros.h"
#include "header_files/Stageboard.h"
#include "header_files/Physics.h"
#include "header_files/Scene.h"
#include "header_files/CustomShader.h"

FirstStageScene* CreateFirstStageScene() {
	FirstStageScene* scene = malloc(sizeof(FirstStageScene));

	if (scene == 0) {
		puts("Unable to allocate memory for scene object.");
		exit(1);
	}

	scene->player = CreatePlayer(1);
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
	scene->creation_time = GetTime();
	scene->custom_shader = CreateCustomShader();

	scene->player->model.materials[0].shader = scene->custom_shader->shader;
	scene->stageboard->model.materials[0].shader = scene->custom_shader->shader;

	scene->played_puzzle_solved_audio = 0;
	scene->puzzle_solved_audio = LoadSound("Assets/Audios/Puzzle Solved.wav");

	return scene;
}

void UpdateFirstStageScene(FirstStageScene* scene, Ui* ui) {
	UpdatePlayer(scene->player, 1);
	CustomUpdateCamera(scene->camera, scene->player->pos);

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
	ClearBackground(SKYBLUE);

	BeginMode3D(*scene->camera);

	SetShaderValue(scene->custom_shader->shader, scene->custom_shader->shader.locs[SHADER_LOC_VECTOR_VIEW], scene->camera, SHADER_UNIFORM_VEC3);
	UpdateLightValues(&scene->custom_shader->shader, &scene->custom_shader->light);

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
		scene->stageboard->rotation_axis,
		scene->stageboard->rotation_angle,
		scene->stageboard->scale,
		scene->stageboard->color);

	DrawCubeWires(
		scene->interaction_cube.pos,
		scene->interaction_cube.width,
		scene->interaction_cube.height,
		scene->interaction_cube.length,
		scene->interaction_cube.color);

	if (scene->can_draw_next_stage_plate) {
		if (!scene->played_puzzle_solved_audio) {
			scene->played_puzzle_solved_audio = 1;
			PlaySound(scene->puzzle_solved_audio);
		}

		ui->color.a = (int)floor(Lerp(ui->color.a, 255, 0.1f));
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

	if (!scene->can_draw_next_stage_plate) {
		if (GetTime() - scene->creation_time < 4.0f) {
			ui->color.a = (int)floor(Lerp(ui->color.a, 255, 0.1f));
		}
		else {
			ui->color.a = (int)floor(Lerp(ui->color.a, 0, 0.1f));
		}

		UiDrawText(ui, "CONTROLS: ARROWS OR WASD", (Vector2) { WIDTH / 2, HEIGHT / 8 }, ui->color);
		UiDrawText(ui, "PRESS R TO RESTART ANY STAGE", (Vector2) { WIDTH / 2, HEIGHT / 4 }, ui->color);
	} else {
		UiDrawText(ui, "GET TO THE LIT SQUARE.", (Vector2) { WIDTH / 2, HEIGHT / 4 }, ui->color);
	}

	if (scene->player->pos.x == scene->next_stage_plate.pos.x &&
		scene->player->pos.z == scene->next_stage_plate.pos.z &&
		scene->can_draw_next_stage_plate) {
		scene->finished_stage = 1;
	}
}

FirstStageScene* ResetFirstStageScene(FirstStageScene* scene) {
	UnloadSound(scene->puzzle_solved_audio);
	FreeScene((Scene**)&scene);
	return CreateFirstStageScene(scene);
}
