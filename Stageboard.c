#include "Stageboard.h"
#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>

Stageboard* GetStageboard() {
	Stageboard* stageboard = malloc(sizeof(Stageboard));

	if (stageboard == 0) {
		printf("Unable to allocate memory for stageboard.\n");
		exit(1);
	}

	stageboard->pos = (Vector3){ -1.0f, -2.0f, 0.0f };
	stageboard->height = 2.0f;
	stageboard->width = 2.0f;
	stageboard->length = 2.0f;
	stageboard->model = LoadModel("Assets/Models/Board.obj");
	stageboard->model.materials[0].maps[MATERIAL_MAP_ALBEDO].texture = LoadTexture("Assets/Textures/Chess_Board.png");
	stageboard->texture_ptr = &stageboard->model.materials[0].maps[MATERIAL_MAP_ALBEDO].texture;

	return stageboard;
}

void FreeStageboard(Stageboard* stageboard) {
	if (stageboard == 0) {
		return;
	}

	if (stageboard->texture_ptr != 0) {
		UnloadTexture(*stageboard->texture_ptr);
	}
	
	UnloadModel(stageboard->model);

	free(stageboard);
}