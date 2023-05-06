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
#include "Scene.h"
#include "TitleScene.h"
#include "FirstStageScene.h"
#include "SecondStageScene.h"
#include "ThirdStageScene.h"
#include "FourthStageScene.h"
#include "FifthStageScene.h"

#ifdef _DEBUG
	#include "Debug.h"
#endif

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
			if (titlescene == 0) {
				titlescene = CreateTitleScene();
			}

			UpdateTitleScene(titlescene);

			if (IsKeyPressed(KEY_ENTER)) {
				FreeTitleScene(titlescene);
				chosen_scene = 1;
			}
			break;
		case 1:
			if (first_stage_scene == 0) {
				first_stage_scene = CreateFirstStageScene();
			}

			UpdateFirstStageScene(first_stage_scene);

			if (first_stage_scene->finished_stage) {
				FreeScene((Scene*)first_stage_scene);
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
				FreeScene((Scene*)second_stage_scene);
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
				FreeScene((Scene*)third_stage_scene);
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
				FreeScene((Scene*)fourth_stage_scene);
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
				FreeScene((Scene*)fifth_stage_scene);
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

#ifdef _DEBUG
		int new_chosen_scene = GetChosenSceneByNumberKey();

		if (new_chosen_scene > -1) {
			chosen_scene = new_chosen_scene;
		}
		else {
			// No new stages were selected.
			continue;
		}

		if (chosen_scene != 0 && titlescene) {
			FreeTitleScene(titlescene);
			titlescene = 0;
		}
		
		if (chosen_scene != 1 && first_stage_scene) {
			FreeScene((Scene*)first_stage_scene);
			first_stage_scene = 0;
		}

		if (chosen_scene != 2 && second_stage_scene) {
			FreeScene((Scene*)second_stage_scene);
			second_stage_scene = 0;
		}

		if (chosen_scene != 3 && third_stage_scene) {
			FreeScene((Scene*)third_stage_scene);
			third_stage_scene = 0;
		}

		if (chosen_scene != 4 && fourth_stage_scene) {
			FreeScene((Scene*)fourth_stage_scene);
			fourth_stage_scene = 0;
		}

		if (chosen_scene != 5 && fifth_stage_scene) {
			FreeScene((Scene*)fifth_stage_scene);
			fifth_stage_scene = 0;
		}
#endif
	}

	return 0;
}