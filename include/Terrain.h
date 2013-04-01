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

	extern GLfloat ctrlpoints[4][4][3];

	void init_terrain();
	GLfloat* generate_normals(int res);
	GLfloat* generate_terrain(int res);
	void draw_terrain();

	int* wind_lines(int totalX, int totalY);
	int* wind(int totalX, int totalY);

	Vec3 normal(Vec3& vert_normal, Vec3& vert_right, Vec3& vert_up);

}
#endif /* TERRAIN_H_ */
