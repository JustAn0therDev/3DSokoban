#include "Scene.h"
#include "Player.h"
#include "Stageboard.h"
#include "Camera.h"
#include <stdlib.h>

void FreeScene(Scene** scene) {
	FreePlayer((*scene)->player);
	FreeStageboard((*scene)->stageboard);
	free((*scene)->camera);
	free(*scene);
	*scene = 0;
}