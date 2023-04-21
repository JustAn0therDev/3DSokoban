#include "Physics.h"
#include "GameObjects.h"

int collision_AABB(Cube cube1, Cube cube2) {
	cube1.cube_faces.top = cube1.pos.y + cube1.height / 2;
	cube1.cube_faces.bottom = cube1.pos.y - cube1.height / 2;
	cube1.cube_faces.front = cube1.pos.z + cube1.length / 2;
	cube1.cube_faces.back = cube1.pos.z - cube1.length / 2;
	cube1.cube_faces.left = cube1.pos.x - cube1.width / 2;
	cube1.cube_faces.right = cube1.pos.x + cube1.width / 2;

	cube2.cube_faces.top = cube2.pos.y + cube2.height / 2;
	cube2.cube_faces.bottom = cube2.pos.y - cube2.height / 2;
	cube2.cube_faces.front = cube2.pos.z + cube2.length / 2;
	cube2.cube_faces.back = cube2.pos.z - cube2.length / 2;
	cube2.cube_faces.left = cube2.pos.x - cube2.width / 2;
	cube2.cube_faces.right = cube2.pos.x + cube2.width / 2;

	int x_collision = cube1.cube_faces.right > cube2.cube_faces.left && cube1.cube_faces.left < cube2.cube_faces.right;
	int y_collision = cube1.cube_faces.top > cube2.cube_faces.bottom && cube1.cube_faces.bottom < cube2.cube_faces.top;
	int z_collision = cube1.cube_faces.front > cube2.cube_faces.back && cube1.cube_faces.back < cube2.cube_faces.front;

	return x_collision & y_collision & z_collision;
}