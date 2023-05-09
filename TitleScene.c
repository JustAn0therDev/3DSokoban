#include "TitleScene.h"
#include "Player.h"
#include "Stageboard.h"
#include "Macros.h"
#include "Camera.h"
#include <stdlib.h>
#include <stdio.h>

TitleScene* CreateTitleScene()
{
	TitleScene* titlescene = malloc(sizeof(TitleScene));

	if (titlescene == 0) {
		printf("Couldn't allocate memory for title screen.\n");
		exit(1);
	}

	titlescene->player = CreatePlayer();
	titlescene->camera = CreateCamera();
	titlescene->stageboard = CreateStageboard();

	titlescene->camera->position = (Vector3){ 10.0f, 10.0f, 10.0f };
	titlescene->camera->target = titlescene->player->pos;

	SetCameraMode(*titlescene->camera, CAMERA_ORBITAL);

	// focus on the player
	titlescene->camera->target = titlescene->player->pos;

	return titlescene;
}

void FreeTitleScene(TitleScene* titlescene)
{
	FreePlayer(titlescene->player);
	free(titlescene);
}

void UpdateTitleScene(TitleScene* titlescene)
{
	UpdateCamera(titlescene->camera);

	// The main character model has to be fixed in a position.
	// The player cannot control it. 

	// Drawing
	ClearBackground(SKYBLUE);

	BeginMode3D(*titlescene->camera);

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

	DrawText("SOKOBAN", (WIDTH / 2) - 180, HEIGHT / 8, 72, BROWN);

	DrawText("PRESS ENTER TO BEGIN", (WIDTH / 2) - 300, HEIGHT - 100, 48, BLACK);
}
