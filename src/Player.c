#include "header_files/Player.h"
#include "header_files/GameGeometry.h"
#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>

Player* CreatePlayer() {
	Player* player = malloc(sizeof(Player));

	if (player == 0) {
		puts("Unable to allocate memory for player.");
		exit(1);
	}

	player->pos = (Vector3){ 0 };
	player->scale = (Vector3){ 0.15f, 0.15f, 0.15f };
    player->rotation_angle = 0.0f;
	player->rotation_axis = (Vector3){ 0.0f, 1.0f, 0.0f };
	player->movement_speed = 1;
	player->model = LoadModel("Assets/Models/Robot.obj");
	player->texture_ptr = 0;
	player->last_movement = (Vector3){ 0 };
	player->last_movement_time = 1;

	player->model.materials[0].maps[MATERIAL_MAP_ALBEDO].texture = 
		LoadTexture("Assets/Textures/stacked-stones.png");

    player->texture_ptr = &player->model.materials[0].maps[MATERIAL_MAP_ALBEDO].texture;

	player->collision_cube = (Cube){
		player->pos,
		2.0f,
		2.0f,
		2.0f,
		WHITE
	};

	return player;
}

void UpdatePlayer(Player* player, int can_move) {
	player->last_movement = (Vector3){ 0 };

	if (can_move) {
		if (GetTime() - player->last_movement_time > 0.15f) {
			// Movement
			if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
				player->pos.z--;
				player->last_movement.z = -player->movement_speed;
				player->rotation_angle = 90.0f;
			}
			else if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
				player->pos.x--;
				player->last_movement.x = -player->movement_speed;
				player->rotation_angle = 180.0f;
			}
			else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
				player->pos.x++;
				player->last_movement.x = player->movement_speed;
				player->rotation_angle = 0.0f;
			}
			else if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
				player->pos.z++;
				player->last_movement.z = player->movement_speed;
				player->rotation_angle = 270.0f;
			}

			if (player->last_movement.z != 0 || player->last_movement.x != 0) {
				player->last_movement_time = GetTime();
			}
		}
	}

	player->collision_cube.pos = player->pos;
}

void FreePlayer(Player* player) {
	if (player == 0) {
		return;
	}

    UnloadTexture(*player->texture_ptr);
	UnloadModel(player->model);

	free(player);
}
