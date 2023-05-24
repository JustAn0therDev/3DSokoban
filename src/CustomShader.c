#include "header_files/CustomShader.h"
#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <raymath.h>

CustomShader* CreateCustomShader() {
	CustomShader* custom_shader = malloc(sizeof(CustomShader));

	if (custom_shader == 0) {
		puts("Unable to allocate memory for CustomShader object.");
		exit(1);
	}

	// Load basic lighting shader
	custom_shader->shader = LoadShader("Shaders/lighting.vs", "Shaders/lighting.fs");
	// Get some required shader locations

	custom_shader->shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(custom_shader->shader, "viewPos");
	// NOTE: "matModel" location name is automatically assigned on shader loading, 
	// no need to get the location again if using that uniform name
	//shader.locs[SHADER_LOC_MATRIX_MODEL] = GetShaderLocation(shader, "matModel");

	int ambientLoc = GetShaderLocation(custom_shader->shader, "ambient");
	SetShaderValue(custom_shader->shader, ambientLoc, (float[4]) { 0.1f, 0.1f, 0.1f, 1.0f }, SHADER_UNIFORM_VEC4);

	// Create light
	custom_shader->light = CreateLight(LIGHT_POINT, (Vector3) { -2, 60, -60 }, (Vector3) { 0, 50, -50 }, RAYWHITE, custom_shader->shader);

	return custom_shader;
}

void UpdateCustomShader(CustomShader* custom_shader) {
	UpdateLightValues(&custom_shader->shader, &custom_shader->light);
}

// Send light->properties to shader
// NOTE: light->shader locations should be available 
void UpdateLightValues(Shader* shader, Light* light)
{
	DrawSphereEx(light->position, 0.2f, 8, 8, light->color);
	// Send to shader light->enabled state and type
	SetShaderValue(*shader, light->enabledLoc, &light->enabled, SHADER_UNIFORM_INT);
	SetShaderValue(*shader, light->typeLoc, &light->type, SHADER_UNIFORM_INT);

	// Send to shader light->position values
	float position[3] = { light->position.x, light->position.y, light->position.z };
	SetShaderValue(*shader, light->positionLoc, position, SHADER_UNIFORM_VEC3);

	// Send to shader light->target position values
	float target[3] = { light->target.x, light->target.y, light->target.z };
	SetShaderValue(*shader, light->targetLoc, target, SHADER_UNIFORM_VEC3);

	// Send to shader light->color values
	float color[4] = { (float)light->color.r / (float)255, (float)light->color.g / (float)255,
					   (float)light->color.b / (float)255, (float)light->color.a / (float)255 };
	SetShaderValue(*shader, light->colorLoc, color, SHADER_UNIFORM_VEC4);
}

Light CreateLight(int type, Vector3 position, Vector3 target, Color color, Shader shader)
{
	Light light = { 0 };

	light.enabled = 1;
	light.type = type;
	light.position = position;
	light.target = target;
	light.color = color;

	// NOTE: lighting shader naming must be the provided ones
	light.enabledLoc = GetShaderLocation(shader, "light.enabled");
	light.typeLoc = GetShaderLocation(shader, "light.type");
	light.positionLoc = GetShaderLocation(shader, "light.position");
	light.targetLoc = GetShaderLocation(shader, "light.target");
	light.colorLoc = GetShaderLocation(shader, "light.color");

	UpdateLightValues(&shader, &light);

	return light;
}

void FreeCustomShader(CustomShader* custom_shader) {
	UnloadShader(custom_shader->shader);
	free(custom_shader);
}
