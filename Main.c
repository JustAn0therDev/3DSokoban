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

	FirstStageScene* first_stage_scene = CreateScene();

	while (!WindowShouldClose()) {
		UpdateScene(first_stage_scene);
	}

	FreeScene(first_stage_scene);

	return 0;
}