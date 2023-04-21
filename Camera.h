#pragma once
#include <raylib.h>
#include "Player.h"

Camera* GetCamera();
void UpdateSokobanCamera(Camera* camera, Player* player);