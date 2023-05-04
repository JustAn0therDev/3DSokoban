#include <stdio.h>
#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Camera.h"
#include "Macros.h"
#include "GameGeometry.h"
#include "Player.h"
#include "Physics.h"
#include "TitleScene.h"
#include "FirstStageScene.h"
#include "SecondStageScene.h"
#include "ThirdStageScene.h"
#include "FourthStageScene.h"
#include "FifthStageScene.h"


int main(void) {
	InitWindow(WIDTH, HEIGHT, "Sokoban");
	
	SetTargetFPS(60);

	int chosen_scene = 0;

	TitleScene* titlescene = CreateTitleScene();
	FirstStageScene* first_stage_scene = 0;
	SecondStageScene* second_stage_scene = 0;
	ThirdStageScene* third_stage_scene = 0;
	FourthStageScene* fourth_stage_scene = 0;
	FifthStageScene* fifth_stage_scene = 0;

	int break_game_loop = 0;

	while (!WindowShouldClose()) {
		switch (chosen_scene)
		{
		case 0:
			UpdateTitleScene(titlescene);

			if (IsKeyPressed(KEY_ENTER)) {
				FreeTitleScene(titlescene);
				chosen_scene = 1; // TODO: choosing the second scene temporarily; this should be set to 1.
			}
			break;
		case 1:
			if (first_stage_scene == 0) {
				first_stage_scene = CreateFirstStageScene();
			}

			UpdateFirstStageScene(first_stage_scene);

			if (first_stage_scene->finished_stage) {
				FreeFirstStageScene(first_stage_scene);
				chosen_scene++;
			}

			if (IsKeyPressed(KEY_R)) {
				first_stage_scene = ResetFirstStageScene(first_stage_scene);
			}
			break;
		case 2:
			if (second_stage_scene == 0) {
				second_stage_scene = CreateSecondStageScene();
			}

			UpdateSecondStageScene(second_stage_scene);

			if (second_stage_scene->finished_stage) {
				FreeSecondStageScene(second_stage_scene);
				chosen_scene++;
			}

			if (IsKeyPressed(KEY_R)) {
				second_stage_scene = ResetSecondStageScene(second_stage_scene);
			}
			break;
		case 3:
			if (third_stage_scene == 0) {
				third_stage_scene = CreateThirdStageScene();
			}

			UpdateThirdStageScene(third_stage_scene);

			if (third_stage_scene->finished_stage) {
				FreeThirdStageScene(third_stage_scene);
				chosen_scene++;
			}

			if (IsKeyPressed(KEY_R)) {
				third_stage_scene = ResetThirdStageScene(third_stage_scene);
			}
			break;
		case 4:
			if (fourth_stage_scene == 0) {
				fourth_stage_scene = CreateFourthStageScene();
			}

			UpdateFourthStageScene(fourth_stage_scene);

			if (fourth_stage_scene->finished_stage) {
				FreeFourthStageScene(fourth_stage_scene);
				chosen_scene++;
			}

			if (IsKeyPressed(KEY_R)) {
				fourth_stage_scene = ResetFourthStageScene(fourth_stage_scene);
			}
			break;
		case 5:
			if (fifth_stage_scene == 0) {
				fifth_stage_scene = CreateFifthStageScene();
			}

			UpdateFifthStageScene(fifth_stage_scene);

			if (fifth_stage_scene->finished_stage) {
				FreeFifthStageScene(fifth_stage_scene);
				chosen_scene = -1;
				break_game_loop = 1;
			}

			if (IsKeyPressed(KEY_R)) {
				fifth_stage_scene = ResetFifthStageScene(fifth_stage_scene);
			}
			break;
		default:
			break;
		}

		if (break_game_loop) {
			break;
		}
	}

	return 0;
}