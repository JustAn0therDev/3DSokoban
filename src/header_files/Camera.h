#pragma once
#include <raylib.h>
#include "Player.h"

Camera* CreateCamera();
void CustomUpdateCamera(Camera* camera, Vector3 target);