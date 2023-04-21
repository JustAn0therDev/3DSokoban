#include "Camera.h"
#include <stdlib.h>
#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include "Player.h"

Camera* GetCamera() {
	Camera* camera = malloc(sizeof(Camera));

	if (camera == 0) {
		printf("Couldn't allocate memory for camera object.\n");
		exit(1);
	}

	camera->position = (Vector3){ 0.0f, 0.0f, 0.0f };
	camera->target = (Vector3){ 0.0f, 0.0f, 0.0f };
	camera->up = (Vector3){ 0.0f, 1.0f, 0.0f };
	camera->fovy = 80.0f;
	camera->projection = CAMERA_PERSPECTIVE;

	return camera;
}

void UpdateSokobanCamera(Camera* camera, Player* player) {
	if (camera->position.z != 10.0f &&
		camera->position.y != 10.0f) {
		camera->position.z = Lerp(
			camera->position.z, 
			10.0f, 
			0.1f);

		camera->position.y = Lerp(
			camera->position.y,
			10.0f,
			0.1f);

		return;
	}
	
	camera->target.x = Lerp(camera->target.x, player->pos.x / 2, 0.5f);
	camera->target.y = Lerp(camera->target.y, player->pos.y / 2, 0.5f);
	camera->target.z = Lerp(camera->target.z, player->pos.z / 2, 0.5f);
}