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

	Image image = LoadImage("Assets/Images/SinCity.png");
	Texture texture = LoadTextureFromImage(image);

	int break_game_loop = 0;

	while (!WindowShouldClose()) {
		switch (chosen_scene)
		{
		case 0:
			BeginDrawing();
			
			DrawTexture(texture, WIDTH / 4, HEIGHT / 4, WHITE);
			
			EndDrawing();

			if (IsKeyPressed(KEY_ENTER)) {
				chosen_scene = 1;
			}
			break;
		case 1:
			UpdateFirstStageScene(first_stage_scene);

			if (first_stage_scene->finished_stage) {
				FreeFirstStageScene(first_stage_scene);
				chosen_scene = -1;
				break_game_loop = 1;
			}
		default:
			break;
		}

		if (break_game_loop) {
			break;
		}
	}

	return 0;
}