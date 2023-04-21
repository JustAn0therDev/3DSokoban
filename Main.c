#include <stdio.h>
#include <raylib.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "GameMath.h"
#include "GameObjects.h"
#include "Physics.h"

#define WIDTH 1280
#define HEIGHT 720
#define MOVEMENT_SPEED 1

int main(void) {
	InitWindow(WIDTH, HEIGHT, "3D Sokoban");
	
	SetTargetFPS(60);

	Cube player = {
		(Vector3) {
			0.0f, 0.0f, 0.0f
		},
		2.0f,
		2.0f,
		2.0f,
		WHITE,
		(CubeFaces) {
		0.0f,0.0f, 0.0f, 0.0f, 0.0f, 0.0f
		},
		(Vector3) { 
			0.1f, 0.1f, 0.1f 
		},
		0.0f
	};

	Cube interaction_cube = { 
		(Vector3) { 
			3.0f, 0.0f, 0.0f 
		},
		2.0f, 
		2.0f, 
		2.0f, 
		RED, 
		(CubeFaces) {
			0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f
		},
		0.0f
	};

	Cube board = {
		(Vector3) {
			-1.0f, -2.0f, 0.0f
		},
		2.0f,
		2.0f,
		2.0f,
		WHITE,
		(CubeFaces) {
		0.0f,0.0f, 0.0f, 0.0f, 0.0f, 0.0f
		},
		(Vector3) {
			1.0f, 1.0f, 1.0f
		},
		0.0f
	};
	
	Plate plate = { (Vector3) { 0.0f, -1.0f, -5.0f }, 2, 0, 2, RED };
	Plate plate_next_stage = { (Vector3) { 0.0f, -1.0f, 0.0f }, 2, 0, 2, PINK };

	Camera camera = { 0 };
	camera.position = (Vector3){ 0.0f, 10.0f, 10.0f };
	camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
	camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
	camera.fovy = 80.0f;
	camera.projection = CAMERA_PERSPECTIVE;

	Vector3 movement = { 0 };

	int can_draw_next_stage_plate = 0;

	player.model = LoadModel("Assets/Models/Knight.obj");
	board.model = LoadModel("Assets/Models/Board.obj");

	board.model.materials[0].maps[MATERIAL_MAP_ALBEDO].texture = LoadTexture("Assets/Textures/Chess_Board.png");
	
	Vector3 default_rotation_axis = (Vector3){ 0.0f, 1.0f, 0.0f };

	while (!WindowShouldClose()) {
		movement.x = 0;
		movement.y = 0;
		movement.z = 0;

		camera.target.x = lerp(camera.target.x, player.pos.x / 2, 0.5f);
		camera.target.y = lerp(camera.target.y, player.pos.y / 2, 0.5f);
		camera.target.z = lerp(camera.target.z, player.pos.z / 2, 0.5f);

		// Movement
		if (IsKeyPressed(KEY_UP)) {
			player.pos.z--;
			movement.z = -MOVEMENT_SPEED;
			player.rotation_angle = -90.0f;
		} else if (IsKeyPressed(KEY_LEFT)) {
			player.pos.x--;
			movement.x = -MOVEMENT_SPEED;
			player.rotation_angle = 0.0f;
		} else if (IsKeyPressed(KEY_RIGHT)) {
			player.pos.x++;
			movement.x = MOVEMENT_SPEED;
			player.rotation_angle = 180.0f;
		} else if (IsKeyPressed(KEY_DOWN)) {
			player.pos.z++;
			movement.z = MOVEMENT_SPEED;
			player.rotation_angle = 90.0f;
		}

		if (collision_AABB(player, interaction_cube)) {
			interaction_cube.pos.x += movement.x;
			interaction_cube.pos.y += movement.y;
			interaction_cube.pos.z += movement.z;
		}

		if (interaction_cube.pos.z == plate.pos.z && interaction_cube.pos.x == plate.pos.x) {
			plate.color = GREEN;
			interaction_cube.color = GREEN;
			can_draw_next_stage_plate = 1;
		}
		else {
			plate.color = RED;
			interaction_cube.color = RED;
			can_draw_next_stage_plate = 0;
		}

		// Drawing
		BeginDrawing();

		ClearBackground(DARKGRAY);

		BeginMode3D(camera);

		DrawCube(interaction_cube.pos, interaction_cube.width, interaction_cube.height, interaction_cube.length, interaction_cube.color);
		DrawCube(plate.pos, plate.width, plate.height, plate.length, plate.color);

		DrawModelEx(player.model, player.pos, default_rotation_axis, player.rotation_angle, (Vector3) { 0.1f, 0.1f, 0.1f }, WHITE);
		DrawModelEx(board.model, board.pos, default_rotation_axis, board.rotation_angle, (Vector3) { 0.15f, 0.1f, 0.15f }, board.color);

		DrawCubeWires(player.pos, player.width, player.height, player.length, BLACK);

		DrawCubeWires(interaction_cube.pos, interaction_cube.width, interaction_cube.height, interaction_cube.length, interaction_cube.color);

		if (can_draw_next_stage_plate) {
			DrawCube(plate_next_stage.pos, plate_next_stage.width, plate_next_stage.height, plate_next_stage.length, plate_next_stage.color);
		}

		EndMode3D();
		
		if (player.pos.x == plate_next_stage.pos.x && player.pos.z == plate_next_stage.pos.z && can_draw_next_stage_plate) {
			DrawText("NICE CAULK!!1", (WIDTH / 2) - 150, HEIGHT / 2, 48, BLACK);
		}

		EndDrawing();
	}

	UnloadModel(player.model);
	
	UnloadTexture(board.model.materials[0].maps[MATERIAL_MAP_ALBEDO].texture);
	UnloadModel(board.model);

	return 0;
}