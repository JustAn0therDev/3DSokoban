#include "Scene.h"
#include "Player.h"
#include "Stageboard.h"
#include "Camera.h"
#include "CustomShader.h"
#include <stdlib.h>

void FreeScene(Scene** scene) {
	FreePlayer((*scene)->player);
	FreeStageboard((*scene)->stageboard);
	FreeCustomShader((*scene)->custom_shader);
	free((*scene)->camera);
	free(*scene);
	*scene = 0;
}