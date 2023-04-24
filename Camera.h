#pragma once
#include <raylib.h>
#include "Player.h"

Camera* CreateCamera();
void CustomUpdateCamera(Camera* camera, Player* player);