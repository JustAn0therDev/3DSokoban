#include "header_files/Scene.h"
#include "header_files/Player.h"
#include "header_files/Stageboard.h"
#include "header_files/Camera.h"
#include "header_files/CustomShader.h"
#include <stdlib.h>

void FreeScene(Scene** scene) {
	FreePlayer((*scene)->player);
	FreeStageboard((*scene)->stageboard);
	FreeCustomShader((*scene)->custom_shader);
	free((*scene)->camera);
	free(*scene);
	*scene = 0;
}
