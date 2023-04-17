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

int main(void) {
	InitWindow(WIDTH, HEIGHT, "3D Sokoban");
	
	SetTargetFPS(60);

	Cube player = { (Vector3) { 0.0f, 0.0f, 0.0f }, 2.0f, 2.0f, 2.0f, BLUE, (CubeFaces) { 0.0f,0.0f, 0.0f, 0.0f, 0.0f, 0.0f } };
	Cube interaction_cube = { (Vector3) { 0.0f, 0.0f, -5.0f }, 2.0f, 2.0f, 2.0f, RED, (CubeFaces) { 0.0f,0.0f, 0.0f, 0.0f, 0.0f, 0.0f } };
	Plate plate = { (Vector3) { 0.0f, -1.0f, -10.0f }, 2, 0, 2, RED };
	Plate plate_next_stage = { (Vector3) { 0.0f, -1.0f, 0.0f }, 2, 0, 2, SKYBLUE };

	Camera camera = { 0 };
	camera.position = (Vector3){ 0.0f, 10.0f, 10.0f };
	camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
	camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
	camera.fovy = 70.0f;
	camera.projection = CAMERA_PERSPECTIVE;

	Vector3 movement = { 0 };

	int can_draw_next_stage_plate = 0;

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
			movement.z = -1;
		} else if (IsKeyPressed(KEY_LEFT)) {
			player.pos.x--;
			movement.x = -1;
		} else if (IsKeyPressed(KEY_RIGHT)) {
			player.pos.x++;
			movement.x = 1;
		} else if (IsKeyPressed(KEY_DOWN)) {
			player.pos.z++;
			movement.z = 1;
		}

		// Collision check
		player.cube_faces.top = player.pos.y + player.height / 2;
		player.cube_faces.bottom = player.pos.y - player.height / 2;
		player.cube_faces.front = player.pos.z + player.length / 2;
		player.cube_faces.back = player.pos.z - player.length / 2;
		player.cube_faces.left = player.pos.x - player.width / 2;
		player.cube_faces.right = player.pos.x + player.width / 2;

		interaction_cube.cube_faces.top = interaction_cube.pos.y + interaction_cube.height / 2;
		interaction_cube.cube_faces.bottom = interaction_cube.pos.y - interaction_cube.height / 2;
		interaction_cube.cube_faces.front = interaction_cube.pos.z + interaction_cube.length / 2;
		interaction_cube.cube_faces.back = interaction_cube.pos.z - interaction_cube.length / 2;
		interaction_cube.cube_faces.left = interaction_cube.pos.x - interaction_cube.width / 2;
		interaction_cube.cube_faces.right = interaction_cube.pos.x + interaction_cube.width / 2;

		if (collision_AABB(player, interaction_cube)) {
			interaction_cube.pos.x += movement.x;
			interaction_cube.pos.y += movement.y;
			interaction_cube.pos.z += movement.z;
		}

		if (interaction_cube.pos.x == plate.pos.x && interaction_cube.pos.z == plate.pos.z) {
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

		ClearBackground(WHITE);

		BeginMode3D(camera);

		DrawCube(player.pos, player.width, player.height, player.length, player.color);
		DrawCube(interaction_cube.pos, interaction_cube.width, interaction_cube.height, interaction_cube.length, interaction_cube.color);
		DrawCube(plate.pos, plate.width, plate.height, plate.length, plate.color);

		DrawCubeWires(player.pos, player.width, player.height, player.length, player.color);
		DrawCubeWires(interaction_cube.pos, interaction_cube.width, interaction_cube.height, interaction_cube.length, interaction_cube.color);

		DrawGrid(100, 5.0f);

		if (can_draw_next_stage_plate) {
			DrawCube(plate_next_stage.pos, plate_next_stage.width, plate_next_stage.height, plate_next_stage.length, plate_next_stage.color);;
		}

		EndMode3D();
		
		if (player.pos.x == plate_next_stage.pos.x && player.pos.z == plate_next_stage.pos.z && can_draw_next_stage_plate) {
			DrawText("NICE CAULK!!1", (WIDTH / 2) - 150, HEIGHT / 2, 48, GREEN);
		}

		EndDrawing();
	}

	return 0;
}