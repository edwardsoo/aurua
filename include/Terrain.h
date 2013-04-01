/*
 * Terrain.h
 *
 *  Created on: Mar 31, 2013
 *      Author: Billy
 */

#ifndef TERRAIN_H_
#define TERRAIN_H_

#include<GL/gl.h>

namespace Terrain
{

	extern GLfloat ctrlpoints[4][4][3];

	void init_terrain();
	void generate_terrain();
	extern void draw_terrain();

	short* windLines(int totalX, int totalY);

}
#endif /* TERRAIN_H_ */
