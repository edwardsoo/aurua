/*
 * Terrain.h
 *
 *  Created on: Mar 31, 2013
 *      Author: Billy
 */

#ifndef TERRAIN_H_
#define TERRAIN_H_

#include <GL/gl.h>
#include "Vec3.h"

namespace Terrain
{
	enum Map
	{
		MAP_STANDARD,
		MAP_DRAGONBALL,
		MAP_COSINE,
		MAP_BLAND
	};

	typedef struct
	{
		long x;
		long z;
	} coords;

	extern Map map;

	extern int res;

	extern GLfloat ctrlpoints[4][4][3];

	extern bool is_request_print;

	void init_terrain();
	GLfloat* generate_normals(int res);
	GLfloat* generate_terrain(int res);
	GLint* generate_tex_coords(int res);
	void draw_terrain();

	Vec3 get_normal(double x, double z);
	coords get_terrain_coords(double x, double z);

	//float get_height(float x, float z);
	double get_height(double x, double z);

	int* wind_lines(int totalX, int totalY);
	int* wind(int totalX, int totalY);

	Vec3 normal(Vec3& vert_normal, Vec3& vert_right, Vec3& vert_up);

}
#endif /* TERRAIN_H_ */
