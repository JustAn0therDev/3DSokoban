#pragma once
#include <raylib.h>

typedef struct ui {
	Font font;
	float font_size;
	Color color;
} Ui;

Ui* CreateUi();
void UiDrawText(Ui* ui, const char* text, Vector2 pos, Color color);
void FreeUi(Ui* ui);
