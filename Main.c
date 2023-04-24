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
#include "SecondStageScene.h"

#define WIDTH 1280
#define HEIGHT 720

int main(void) {
	InitWindow(WIDTH, HEIGHT, "3D Sokoban");
	
	SetTargetFPS(60);

	int chosen_scene = 0;

	FirstStageScene* first_stage_scene = 0;
	SecondStageScene* second_stage_scene = 0;

	Image image_sin_city = LoadImage("Assets/Images/SinCity.png");
	Texture texture_sin_city = LoadTextureFromImage(image_sin_city);

	int break_game_loop = 0;

	while (!WindowShouldClose()) {
		switch (chosen_scene)
		{
		case 0:
			BeginDrawing();
			
			DrawTexture(texture_sin_city, WIDTH / 4, HEIGHT / 5, WHITE);
			
			EndDrawing();

			if (IsKeyPressed(KEY_ENTER)) {
				chosen_scene = 1; // TODO: choosing the second scene temporarily; this should be set to 1.
				first_stage_scene = CreateFirstStageScene();
			}
			break;
		case 1:
			UpdateFirstStageScene(first_stage_scene);

			if (first_stage_scene->finished_stage) {
				FreeFirstStageScene(first_stage_scene);
				second_stage_scene = CreateSecondStageScene();
				chosen_scene++;
			}

			if (IsKeyPressed(KEY_R)) {
				first_stage_scene = ResetFirstStageScene(first_stage_scene);
			}
			break;
		case 2:
			UpdateSecondStageScene(second_stage_scene);

			if (second_stage_scene->finished_stage) {
				FreeSecondStageScene(second_stage_scene);
				// TODO: Maybe wait a few seconds before moving on?
				chosen_scene = -1;
				break_game_loop = 1;
			}

			if (IsKeyPressed(KEY_R)) {
				second_stage_scene = ResetSecondStageScene(second_stage_scene);
			}
			break;
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