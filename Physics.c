#include "Physics.h"
#include "GameObjects.h"

int collision_AABB(Cube cube1, Cube cube2) {
	int x_collision = cube1.cube_faces.right >= cube2.cube_faces.left && cube1.cube_faces.left <= cube2.cube_faces.right;
	int y_collision = cube1.cube_faces.top >= cube2.cube_faces.bottom && cube1.cube_faces.bottom <= cube2.cube_faces.top;
	int z_collision = cube1.cube_faces.front >= cube2.cube_faces.back && cube1.cube_faces.back <= cube2.cube_faces.front;

	return x_collision & y_collision & z_collision;
}