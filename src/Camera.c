#include "header_files/Camera.h"
#include <stdlib.h>
#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include "header_files/Player.h"
#include "header_files/Macros.h"

Camera* CreateCamera() {
	Camera* camera = malloc(sizeof(Camera));

	if (camera == 0) {
		puts("Couldn't allocate memory for camera object.");
		exit(1);
	}

	camera->position = (Vector3){ 0.0f, 0.0f, 0.0f };
	camera->target = (Vector3){ 0.0f, 0.0f, 0.0f };
	camera->up = (Vector3){ 0.0f, 1.0f, 0.0f };
	camera->fovy = 80.0f;
	camera->projection = CAMERA_PERSPECTIVE;

	return camera;
}

void CustomUpdateCamera(Camera* camera, Vector3 pos) {
	float delta_time = GetFrameTime();
	
	camera->position.z = Lerp(
		camera->position.z, 
		10.0f, 
		CAMERA_SPEED * delta_time);

	camera->position.y = Lerp(
		camera->position.y,
		10.0f,
		CAMERA_SPEED * delta_time);
	
	camera->position.x = Lerp(camera->position.x, pos.x / 2, CAMERA_SPEED * delta_time);
	camera->target.x = Lerp(camera->target.x, pos.x / 2, CAMERA_SPEED * delta_time);
	camera->target.y = Lerp(camera->target.y, pos.y / 2, CAMERA_SPEED * delta_time);
	
	camera->target.z = Lerp(camera->target.z, pos.z / 2, CAMERA_SPEED * delta_time);
}
