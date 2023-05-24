#pragma once
#include <raylib.h>

typedef struct {
	int type;
	int enabled;
	Vector3 position;
	Vector3 target;
	Color color;
	float attenuation;

	// Shader locations
	int enabledLoc;
	int typeLoc;
	int positionLoc;
	int targetLoc;
	int colorLoc;
	int attenuationLoc;
} Light;

typedef struct custom_shader {
	Light light;
	Shader shader;
} CustomShader;

// Light type
typedef enum {
	LIGHT_DIRECTIONAL = 0,
	LIGHT_POINT
} LightType;

void UpdateLightValues(Shader* shader, Light* light);
Light CreateLight(int type, Vector3 position, Vector3 target, Color color, Shader shader);
CustomShader* CreateCustomShader();
void FreeCustomShader(CustomShader* custom_shader);
