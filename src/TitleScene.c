#include "header_files/TitleScene.h"
#include "header_files/Player.h"
#include "header_files/Stageboard.h"
#include "header_files/Macros.h"
#include "header_files/Camera.h"
#include "header_files/CustomShader.h"
#include <stdlib.h>
#include <stdio.h>

TitleScene* CreateTitleScene()
{
	TitleScene* titlescene = malloc(sizeof(TitleScene));

	if (titlescene == 0) {
		puts("Couldn't allocate memory for title screen.");
		exit(1);
	}

	titlescene->player = CreatePlayer(1);
	titlescene->camera = CreateCamera();
	titlescene->stageboard = CreateStageboard();

	titlescene->camera->position = (Vector3){ 10.0f, 10.0f, 10.0f };
	titlescene->camera->target = titlescene->player->pos;

	SetCameraMode(*titlescene->camera, CAMERA_ORBITAL);

	// focus on the player
	titlescene->camera->target = titlescene->player->pos;
	titlescene->custom_shader = CreateCustomShader();
	titlescene->player->model.materials[0].shader = titlescene->custom_shader->shader;
	titlescene->stageboard->model.materials[0].shader = titlescene->custom_shader->shader;

	return titlescene;
}

void FreeTitleScene(TitleScene* titlescene)
{
	FreeCustomShader(titlescene->custom_shader);
	FreePlayer(titlescene->player);
	FreeStageboard(titlescene->stageboard);
	free(titlescene);
}

void UpdateTitleScene(TitleScene* titlescene, Ui* ui)
{
	UpdateCamera(titlescene->camera);

	// The main character model has to be fixed in a position.
	// The player cannot control it. 

	// Drawing
	ClearBackground(SKYBLUE);

	BeginMode3D(*titlescene->camera);

	SetShaderValue(titlescene->custom_shader->shader, titlescene->custom_shader->shader.locs[SHADER_LOC_VECTOR_VIEW], titlescene->camera, SHADER_UNIFORM_VEC3);
	UpdateLightValues(&titlescene->custom_shader->shader, &titlescene->custom_shader->light);

	DrawModelEx(
		titlescene->player->model, 
		titlescene->player->pos, 
		titlescene->player->rotation_axis, 
		titlescene->player->rotation_angle, 
		titlescene->player->scale, 
		WHITE);

	DrawModelEx(
		titlescene->stageboard->model, 
		titlescene->stageboard->pos, 
		titlescene->stageboard->rotation_axis, 
		titlescene->stageboard->rotation_angle, 
		titlescene->stageboard->scale, 
		DARKGRAY);

	EndMode3D();

	UiDrawText(ui, "SOKOBAN", (Vector2) { WIDTH / 2, HEIGHT / 8 }, BROWN);

	UiDrawText(ui, "PRESS ENTER TO BEGIN", (Vector2) { WIDTH / 2, HEIGHT - 100 }, BLACK);
}
