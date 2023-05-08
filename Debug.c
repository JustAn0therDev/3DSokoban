#include "Debug.h"
#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>

int GetChosenSceneByNumberKey() {
	if (IsKeyReleased(KEY_ZERO)) {
		return 0;
	}
	
	if (IsKeyReleased(KEY_ONE)) {
		return 1;
	}

	if (IsKeyReleased(KEY_TWO)) {
		return 2;
	}

	if (IsKeyReleased(KEY_THREE)) {
		return 3;
	}

	if (IsKeyReleased(KEY_FOUR)) {
		return 4;
	}

	if (IsKeyReleased(KEY_FIVE)) {
		return 5;
	}

	if (IsKeyReleased(KEY_SIX)) {
		return 6;
	}

	if (IsKeyReleased(KEY_SEVEN)) {
		return 7;
	}

	return -1;
}

void ShowInformation(Debug* debug) {
	if (IsKeyReleased(KEY_KP_5)) {
		if (debug->show_information == 0) {
			debug->show_information = 1;
		} else {
			debug->show_information = 0;
		}
	}
}

void DrawGameInformation(Debug* debug) {
	if (debug->show_information) {
		char fps_buffer[10] = { 0 };
		_itoa_s(GetFPS(), fps_buffer, 10, 10);
		
		char final_fps_buffer[50] = { 0 };
		sprintf_s(final_fps_buffer, 50, "FPS: %s", fps_buffer);
		
		char current_scene_buffer[10] = { 0 };
		_itoa_s(debug->current_scene, current_scene_buffer, 10, 10);
		char final_scene_buffer[50] = { 0 };

		sprintf_s(final_scene_buffer, 50, "Stage: %s", current_scene_buffer);

		DrawText(final_fps_buffer, 0, 0, 24, BLACK);
		DrawText(final_scene_buffer, 0, 20, 24, BLACK);
	}
}