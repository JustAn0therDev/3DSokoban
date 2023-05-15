#pragma once
#include "Player.h"
#include "Stageboard.h"
#include "Ui.h"

typedef struct TitleScene {
	Player* player;
	Stageboard* stageboard;
	Camera* camera;
	float rotation_speed;
} TitleScene;

TitleScene* CreateTitleScene();
void FreeTitleScene(TitleScene* titlescene);
void UpdateTitleScene(TitleScene* titlescene, Ui* ui);