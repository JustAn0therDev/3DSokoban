#pragma once

typedef struct debug {
	int show_information;
	int current_scene;
} Debug;

int GetChosenSceneByNumberKey();
void ShowInformation(Debug* debug);
void DrawGameInformation(Debug* debug);