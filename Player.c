#include "Player.h"
#include "GameGeometry.h"
#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>

Player* CreatePlayer() {
	Player* player = malloc(sizeof(Player));

	if (player == 0) {
		printf("Unable to allocate memory for player.\n");
		exit(1);
	}

	player->pos = (Vector3){ 0 };
	player->scale = (Vector3){ 0.1f, 0.1f, 0.1f };
	player->rotation_axis = (Vector3){ 0.0f, 1.0f, 0.0f };
	player->rotation_angle = 0.0f;
	player->movement_speed = 1;
	player->model = LoadModel("Assets/Models/Knight.obj");
	player->texture_ptr = 0;
	player->last_movement = (Vector3){ 0 };

	player->collision_cube = (Cube){
		player->pos,
		2.0f,
		2.0f,
		2.0f,
		WHITE
	};

	return player;
}

void UpdatePlayer(Player* player) {
	player->last_movement = (Vector3){ 0 };

	// Movement
	if (IsKeyPressed(KEY_UP)) {
		player->pos.z--;
		player->last_movement.z = -player->movement_speed;
		player->rotation_angle = -90.0f;
	}
	else if (IsKeyPressed(KEY_LEFT)) {
		player->pos.x--;
		player->last_movement.x = -player->movement_speed;
		player->rotation_angle = 0.0f;
	}
	else if (IsKeyPressed(KEY_RIGHT)) {
		player->pos.x++;
		player->last_movement.x = player->movement_speed;
		player->rotation_angle = 180.0f;
	}
	else if (IsKeyPressed(KEY_DOWN)) {
		player->pos.z++;
		player->last_movement.z = player->movement_speed;
		player->rotation_angle = 90.0f;
	}

	player->collision_cube.pos = player->pos;
}

void FreePlayer(Player* player) {
	if (player == 0) {
		return;
	}

	UnloadModel(player->model);

	free(player);
}
