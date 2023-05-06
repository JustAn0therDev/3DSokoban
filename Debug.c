#include "Debug.h"
#include <raylib.h>

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

	return -1;
}