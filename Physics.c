#include "Physics.h"
#include "GameGeometry.h"

int collision_AABB(Cube* cube1, Cube* cube2) {
	float cube1top = cube1->pos.y + cube1->height / 2;
	float cube1bottom = cube1->pos.y - cube1->height / 2;
	float cube1front = cube1->pos.z + cube1->length / 2;
	float cube1back = cube1->pos.z - cube1->length / 2;
	float cube1left = cube1->pos.x - cube1->width / 2;
	float cube1right = cube1->pos.x + cube1->width / 2;

	float cube2top = cube2->pos.y + cube2->height / 2;
	float cube2bottom = cube2->pos.y - cube2->height / 2;
	float cube2front = cube2->pos.z + cube2->length / 2;
	float cube2back = cube2->pos.z - cube2->length / 2;
	float cube2left = cube2->pos.x - cube2->width / 2;
	float cube2right = cube2->pos.x + cube2->width / 2;

	int x_collision = cube1right > cube2left && cube1left < cube2right;
	int y_collision = cube1top > cube2bottom && cube1bottom < cube2top;
	int z_collision = cube1front > cube2back && cube1back < cube2front;

	return x_collision & y_collision & z_collision;
}

int plate_collision(Cube* cube1, Cube* cube2) {
	float cube1top = cube1->pos.y + cube1->height / 2;
	float cube1bottom = cube1->pos.y - cube1->height / 2;
	float cube1front = cube1->pos.z + cube1->length / 2;
	float cube1back = cube1->pos.z - cube1->length / 2;
	float cube1left = cube1->pos.x - cube1->width / 2;
	float cube1right = cube1->pos.x + cube1->width / 2;

	float cube2top = cube2->pos.y + cube2->height / 2;
	float cube2bottom = cube2->pos.y - cube2->height / 2;
	float cube2front = cube2->pos.z + cube2->length / 2;
	float cube2back = cube2->pos.z - cube2->length / 2;
	float cube2left = cube2->pos.x - cube2->width / 2;
	float cube2right = cube2->pos.x + cube2->width / 2;

	int x_collision = cube1right >= cube2left && cube1left <= cube2right;
	int y_collision = cube1top >= cube2bottom && cube1bottom <= cube2top;
	int z_collision = cube1front >= cube2back && cube1back <= cube2front;

	return x_collision & y_collision & z_collision;
}