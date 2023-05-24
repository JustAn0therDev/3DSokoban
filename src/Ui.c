#include "header_files/Ui.h"
#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

Ui* CreateUi()
{
	Ui* ui = malloc(sizeof(Ui));

	if (ui == 0) {
		puts("Unable to allocate memory for UI object.");
		exit(1);
	}

	ui->font = LoadFont("Assets/Fonts/SocietyMembersRegular-L3vMn.ttf");
	ui->font_size = 48.0f;
	ui->color = BLACK;

	return ui;
}

void UiDrawText(Ui* ui, const char* text, Vector2 pos, Color color) {
	int text_size = (int)strlen(text);

	int half_text_size = (int)ceil(text_size / 2.0f);

	Vector2 final_pos = (Vector2){ pos.x - ((ui->font_size / 2) * half_text_size), pos.y - (ui->font_size / 2)};
	DrawTextEx(ui->font, text, final_pos, (float)ui->font_size, 2, color);
}

void FreeUi(Ui* ui)
{
	UnloadFont(ui->font);
	free(ui);
}
