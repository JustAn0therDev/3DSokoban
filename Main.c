#include <stdio.h>
#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Camera.h"
#include "GameGeometry.h"
#include "Player.h"
#include "Physics.h"
#include "FirstStageScene.h"

#define WIDTH 1280
#define HEIGHT 720

int main(void) {
	InitWindow(WIDTH, HEIGHT, "3D Sokoban");
	
	SetTargetFPS(60);

	int chosen_scene = 0;

	FirstStageScene* first_stage_scene = CreateFirstStageScene();

	Image image_sin_city = LoadImage("Assets/Images/SinCity.png");
	Texture texture_sin_city = LoadTextureFromImage(image_sin_city);

	int break_game_loop = 0;

	while (!WindowShouldClose()) {
		switch (chosen_scene)
		{
		case 0:
			BeginDrawing();
			
			DrawTexture(texture_sin_city, WIDTH / 4, HEIGHT / 4, WHITE);
			
			EndDrawing();

			if (IsKeyPressed(KEY_ENTER)) {
				chosen_scene = 1;
			}
			break;
		case 1:
			UpdateFirstStageScene(first_stage_scene);

			if (first_stage_scene->finished_stage) {
				FreeFirstStageScene(first_stage_scene);
				// TODO: Maybe wait a few seconds before moving on?
				chosen_scene = -1;
				break_game_loop = 1;
			}

			if (IsKeyPressed(KEY_R)) {
				FreeFirstStageScene(first_stage_scene);
				first_stage_scene = CreateFirstStageScene();
			}
		default:
			break;
		}

		if (break_game_loop) {
			break;
		}
	}

	UnloadTexture(texture_sin_city);
	UnloadImage(image_sin_city);

	return 0;
}