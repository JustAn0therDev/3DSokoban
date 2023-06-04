#include <stdio.h>
#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "header_files/Camera.h"
#include "header_files/Macros.h"
#include "header_files/GameGeometry.h"
#include "header_files/Player.h"
#include "header_files/Physics.h"
#include "header_files/Scene.h"
#include "header_files/TitleScene.h"
#include "header_files/FirstStageScene.h"
#include "header_files/SecondStageScene.h"
#include "header_files/ThirdStageScene.h"
#include "header_files/FourthStageScene.h"
#include "header_files/FifthStageScene.h"
#include "header_files/SixthStageScene.h"
#include "header_files/SeventhStageScene.h"
#include "header_files/EighthStageScene.h"
#include "header_files/NinthStageScene.h"
#include "header_files/TenthStageScene.h"

#ifdef _DEBUG
	#include "header_files/Debug.h"
#endif

int main(void) {
	InitWindow(WIDTH, HEIGHT, "Sokoban");
	
	SetTargetFPS(60);

	int chosen_scene = 0;

#ifdef _DEBUG
	Debug debug = { 0 };
	debug.show_information = 1;
	debug.current_scene = chosen_scene;
#endif

	Ui* ui = CreateUi();

	InitAudioDevice();

	SetMasterVolume(0.2f);

	Sound main_theme_sound = LoadSound("Assets/Audios/Stickerbush Symphony.mp3");

	TitleScene* titlescene = CreateTitleScene();
	FirstStageScene* first_stage_scene = 0;
	SecondStageScene* second_stage_scene = 0;
	ThirdStageScene* third_stage_scene = 0;
	FourthStageScene* fourth_stage_scene = 0;
	FifthStageScene* fifth_stage_scene = 0;
	SixthStageScene* sixth_stage_scene = 0;
	SeventhStageScene* seventh_stage_scene = 0;
	EighthStageScene* eighth_stage_scene = 0;
	NinthStageScene* ninth_stage_scene = 0;
	TenthStageScene* tenth_stage_scene = 0;

	int break_game_loop = 0;

	while (!WindowShouldClose()) {
		BeginDrawing();

		switch (chosen_scene)
		{
		case 0:
			if (titlescene == 0) {
				titlescene = CreateTitleScene();
			}

			UpdateTitleScene(titlescene, ui);

			if (IsKeyPressed(KEY_ENTER)) {
				FreeTitleScene(titlescene);
				PlaySound(main_theme_sound);
				titlescene = 0;
				chosen_scene = 1;
			}
			break;
		case 1:
			if (first_stage_scene == 0) {
				first_stage_scene = CreateFirstStageScene();
			}

			UpdateFirstStageScene(first_stage_scene, ui);

			if (first_stage_scene->finished_stage) {
				FreeScene((Scene**)&first_stage_scene);
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
				FreeScene((Scene**)&second_stage_scene);
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
				FreeScene((Scene**)&third_stage_scene);
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
				FreeScene((Scene**)&fourth_stage_scene);
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
				FreeScene((Scene**)&fifth_stage_scene);
				chosen_scene++;
			}

			if (IsKeyPressed(KEY_R)) {
				fifth_stage_scene = ResetFifthStageScene(fifth_stage_scene);
			}
			break;
		case 6:
			if (sixth_stage_scene == 0) {
				sixth_stage_scene = CreateSixthStageScene();
			}

			UpdateSixthStageScene(sixth_stage_scene, &main_theme_sound);

			if (sixth_stage_scene->finished_stage) {
				FreeScene((Scene**)&sixth_stage_scene);
				chosen_scene++;
			}

			if (IsKeyPressed(KEY_R)) {
				sixth_stage_scene = ResetSixthStageScene(sixth_stage_scene);
			}
			break;
		case 7:
			if (seventh_stage_scene == 0) {
				seventh_stage_scene = CreateSeventhStageScene();
			}

			UpdateSeventhStageScene(seventh_stage_scene);

			if (seventh_stage_scene->finished_stage) {
				FreeScene((Scene**)&seventh_stage_scene);
				chosen_scene++;
			}

			if (IsKeyPressed(KEY_R)) {
				seventh_stage_scene = ResetSeventhStageScene(seventh_stage_scene);
			}
			break;
		case 8:
			if (eighth_stage_scene == 0) {
				eighth_stage_scene = CreateEighthStageScene();
			}

			UpdateEighthStageScene(eighth_stage_scene, ui);

			if (eighth_stage_scene->finished_stage) {
				FreeScene((Scene**)&eighth_stage_scene);
				chosen_scene++;
			}

			if (IsKeyPressed(KEY_R)) {
				eighth_stage_scene = ResetEighthStageScene(eighth_stage_scene);
			}
			break;
		case 9:
			if (ninth_stage_scene == 0) {
				ninth_stage_scene = CreateNinthStageScene();
			}

			UpdateNinthStageScene(ninth_stage_scene, ui);

			if (ninth_stage_scene->finished_stage) {
				FreeScene((Scene**)&ninth_stage_scene);
				chosen_scene++;
			}

			if (IsKeyPressed(KEY_R)) {
				ninth_stage_scene = ResetNinthStageScene(ninth_stage_scene);
			}
			break;
        case 10:
			if (tenth_stage_scene == 0) {
				tenth_stage_scene = CreateTenthStageScene();
			}

			UpdateTenthStageScene(tenth_stage_scene, ui);

			if (tenth_stage_scene->finished_stage) {
				FreeScene((Scene**)&tenth_stage_scene);
				chosen_scene = -1;
				break_game_loop = 1;
			}

			if (IsKeyPressed(KEY_R)) {
				tenth_stage_scene = ResetTenthStageScene(tenth_stage_scene);
			}
			break;
		default:
			break;
		}

#ifdef _DEBUG
		ShowInformation(&debug);
		DrawGameInformation(&debug);
		EndDrawing();

		int new_chosen_scene = GetChosenSceneByNumberKey();

		debug.current_scene = chosen_scene;

		if (new_chosen_scene > -1) {
			chosen_scene = new_chosen_scene;
		}
		else if (break_game_loop) {
			break;
		}
		else {
			// No new stages were selected.
			continue;
		}

		if (chosen_scene != 0 && titlescene != 0) {
			FreeTitleScene(titlescene);
			titlescene = 0;
		}
		
		if (chosen_scene != 1 && first_stage_scene != 0) {
			FreeScene((Scene**)&first_stage_scene);
		}

		if (chosen_scene != 2 && second_stage_scene != 0) {
			FreeScene((Scene**)&second_stage_scene);
		}

		if (chosen_scene != 3 && third_stage_scene != 0) {
			FreeScene((Scene**)&third_stage_scene);
		}

		if (chosen_scene != 4 && fourth_stage_scene != 0) {
			FreeScene((Scene**)&fourth_stage_scene);
		}

		if (chosen_scene != 5 && fifth_stage_scene != 0) {
			FreeScene((Scene**)&fifth_stage_scene);
		}

		if (chosen_scene != 6 && sixth_stage_scene != 0) {
			FreeScene((Scene**)&sixth_stage_scene);
		}

		if (chosen_scene != 7 && seventh_stage_scene != 0) {
			FreeScene((Scene**)&seventh_stage_scene);
		}

		if (chosen_scene != 8 && eighth_stage_scene != 0) {
			FreeScene((Scene**)&eighth_stage_scene);
		}

		if (chosen_scene != 9 && ninth_stage_scene != 0) {
			FreeScene((Scene**)&ninth_stage_scene);
		}

		if (chosen_scene != 10 && tenth_stage_scene != 0) {
			FreeScene((Scene**)&tenth_stage_scene);
		}
#else
		if (break_game_loop) {
			break;
		}

		EndDrawing();
#endif
	}

	FreeUi(ui);
	UnloadSound(main_theme_sound);
	CloseAudioDevice();

	return 0;
}
