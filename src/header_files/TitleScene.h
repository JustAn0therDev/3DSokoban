#pragma once
#include "Player.h"
#include "Stageboard.h"
#include "Ui.h"
#include "CustomShader.h"

typedef struct TitleScene {
	Player* player;
	Stageboard* stageboard;
	Camera* camera;
	CustomShader* custom_shader;
	float rotation_speed;
} TitleScene;

TitleScene* CreateTitleScene();
void FreeTitleScene(TitleScene* titlescene);
void UpdateTitleScene(TitleScene* titlescene, Ui* ui);