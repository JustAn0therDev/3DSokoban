#include "header_files/EighthStageScene.h"
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
#include "header_files/Ui.h"

EighthStageScene* CreateEighthStageScene() {
	EighthStageScene* scene = malloc(sizeof(EighthStageScene));

	if (scene == 0) {
		puts("Unable to allocate memory for scene object.");
		exit(1);
	}

	scene->player = CreatePlayer(1);
	scene->player_two = CreatePlayer(2);
	scene->player_two->pos = (Vector3){ 0.0f, 0.0f, 6.0f };
	scene->camera = CreateCamera();

	scene->cube_player_one = (Cube){ (Vector3) { -6.0f, 0.0f, 0.0f }, 2, 2, 2, BLACK, 0 };
	scene->cube_player_two = (Cube){ (Vector3) { 6.0f, 0.0f, 0.0f }, 2, 2, 2, WHITE, 0 };

	scene->plates[0] = (Cube){ (Vector3) { -3.0f, -1.0f, -6.0f }, 3, 0, 3, BLACK, 0 };
	scene->plates[1] = (Cube){ (Vector3) { 3.0f, -1.0f, -6.0f }, 3, 0, 3, WHITE, 0 };

	scene->next_stage_plate = (Cube){ (Vector3) { 0.0f, -1.0f, 0.0f }, 2, 0, 2, (Color) { 0, 255, 0, 0 } };
	scene->can_draw_next_stage_plate = 0;
	scene->finished_stage = 0;
	scene->stageboard = CreateStageboard();
	scene->custom_shader = CreateCustomShader();

	scene->player->model.materials[0].shader = scene->custom_shader->shader;
	scene->stageboard->model.materials[0].shader = scene->custom_shader->shader;

	scene->player_one_toggle = 1;
	scene->player_two_toggle = 0;

	scene->creation_time = (int)GetTime();
    scene->selection_position = (Vector3){ 0.0f, 0.0f, 0.0f };

	return scene;
}

void UpdateEighthStageScene(EighthStageScene* scene, Ui* ui) {
	// Check which character is being controlled
	if (IsKeyPressed(KEY_F)) {
		if (scene->player_one_toggle) {
			scene->player_one_toggle = 0;
			scene->player_two_toggle = 1;
		}
		else {
			scene->player_one_toggle = 1;
			scene->player_two_toggle = 0;
		}
	}

	UpdatePlayer(scene->player, scene->player_one_toggle);
	UpdatePlayer(scene->player_two, scene->player_two_toggle);

	CustomUpdateCamera(scene->camera, scene->player->pos);

    scene->can_draw_next_stage_plate = 1;

	// Collision detection
	if (collision_AABB(&scene->player->collision_cube, &scene->cube_player_one)) {
		scene->cube_player_one.pos = Vector3Add(scene->player->last_movement, scene->cube_player_one.pos);
	}

	if (collision_AABB(&scene->player->collision_cube, &scene->cube_player_two)) {
		scene->player->pos = Vector3Subtract(scene->player->pos, scene->player->last_movement);
	}

	if (collision_AABB(&scene->player_two->collision_cube, &scene->cube_player_two)) {
		scene->cube_player_two.pos = Vector3Add(scene->player_two->last_movement, scene->cube_player_two.pos);
	}

	if (collision_AABB(&scene->player_two->collision_cube, &scene->cube_player_one)) {
		scene->player_two->pos = Vector3Subtract(scene->player_two->pos, scene->player_two->last_movement);
	}

    if (plate_collision(&scene->plates[0], &scene->cube_player_one)) {
        scene->plates[0].color = GREEN;
    } else {
        scene->plates[1].color = BLACK;
        scene->can_draw_next_stage_plate = 0;
    }

    if (plate_collision(&scene->plates[1], &scene->cube_player_two)) {
        scene->plates[1].color = GREEN;
    } else {
        scene->plates[1].color = WHITE;
        scene->can_draw_next_stage_plate = 0;
    }

	// Drawing
	ClearBackground(SKYBLUE);

	BeginMode3D(*scene->camera);

	SetShaderValue(scene->custom_shader->shader, scene->custom_shader->shader.locs[SHADER_LOC_VECTOR_VIEW], scene->camera, SHADER_UNIFORM_VEC3);
	UpdateLightValues(&scene->custom_shader->shader, &scene->custom_shader->light);

	DrawCube(
		scene->cube_player_one.pos,
		scene->cube_player_one.width,
		scene->cube_player_one.height,
		scene->cube_player_one.length,
		scene->cube_player_one.color);

	DrawCube(
		scene->cube_player_two.pos,
		scene->cube_player_two.width,
		scene->cube_player_two.height,
		scene->cube_player_two.length,
		scene->cube_player_two.color);

	DrawCube(
		scene->plates[0].pos,
		scene->plates[0].width,
		scene->plates[0].height,
		scene->plates[0].length,
		scene->plates[0].color);

	DrawCube(
		scene->plates[1].pos,
		scene->plates[1].width,
		scene->plates[1].height,
		scene->plates[1].length,
		scene->plates[1].color);

	DrawModelEx(
		scene->player->model,
		scene->player->pos,
		scene->player->rotation_axis,
		scene->player->rotation_angle,
		scene->player->scale,
		WHITE);

	DrawModelEx(
		scene->player_two->model,
		scene->player_two->pos,
		scene->player_two->rotation_axis,
		scene->player_two->rotation_angle,
		scene->player_two->scale,
		WHITE);

    if (scene->player_one_toggle) {
        scene->selection_position.x = Lerp(scene->selection_position.x, scene->player->pos.x, 0.1f);
        scene->selection_position.y = Lerp(scene->selection_position.y, scene->player->pos.y, 0.1f);
        scene->selection_position.z = Lerp(scene->selection_position.z, scene->player->pos.z, 0.1f);

        DrawCubeWires(
            scene->selection_position,
            scene->player->collision_cube.width,
            scene->player->collision_cube.height,
            scene->player->collision_cube.length,
            BLACK);
    } else {
        scene->selection_position.x = Lerp(scene->selection_position.x, scene->player_two->pos.x, 0.1f);
        scene->selection_position.y = Lerp(scene->selection_position.y, scene->player_two->pos.y, 0.1f);
        scene->selection_position.z = Lerp(scene->selection_position.z, scene->player_two->pos.z, 0.1f);

        DrawCubeWires(
            scene->selection_position,
            scene->player_two->collision_cube.width,
            scene->player_two->collision_cube.height,
            scene->player_two->collision_cube.length,
            BLACK);
    }

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

	if (!scene->can_draw_next_stage_plate) {
		if (GetTime() - scene->creation_time < 4.0f) {
			ui->color.a = (int)floor(Lerp(ui->color.a, 255, 0.1f));
		}
		else {
			ui->color.a = (int)floor(Lerp(ui->color.a, 0, 0.1f));
		}

		UiDrawText(ui, "PRESS F TO SWITCH CHARACTERS", (Vector2) { WIDTH / 2, HEIGHT / 8 }, ui->color);
	} else {
        ui->color.a = (int)floor(Lerp(ui->color.a, 255, 0.1f));

        // TODO: this message should be more clear about which one of the characters is the first.
		UiDrawText(ui, "MOVE THE FIRST CHARACTER TO THE LIT SQUARE", (Vector2) { WIDTH / 2, HEIGHT / 8 }, ui->color);
    }

	if (scene->player->pos.x == scene->next_stage_plate.pos.x &&
		scene->player->pos.z == scene->next_stage_plate.pos.z &&
		scene->can_draw_next_stage_plate) {
		scene->finished_stage = 1;
	}
}

EighthStageScene* ResetEighthStageScene(EighthStageScene* scene) {
	FreePlayer(scene->player_two);
	FreeScene((Scene**)&scene);
	return CreateEighthStageScene(scene);
}
