#pragma once
#include <raylib.h>
#include "GameGeometry.h"

typedef struct player {
	Vector3 pos;
	Vector3 scale;
	Model model;
	float rotation_angle;
	Cube collision_cube;
	float movement_speed;
	Vector3 last_movement;
	Texture* texture_ptr;
	Vector3 rotation_axis;
} Player;

Player* InitializePlayer();

void UpdatePlayer(Player* player);

void FreePlayer(Player* player);