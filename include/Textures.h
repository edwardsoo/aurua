/*
 * Textures.h
 *
 *  Created on: Apr 1, 2013
 *      Author: Billy
 */

#ifndef TEXTURES_H_
#define TEXTURES_H_

namespace Textures
{

	// Texture ID
	const int TITLE = 0;
	const int SKY_Q1 = TITLE+1;
	const int SKY_Q2 = SKY_Q1+1;
	const int SKY_Q3 = SKY_Q2+1;
	const int SKY_Q4 = SKY_Q3+1;
	const int SAND = SKY_Q4+1;
	const int NUM_TEXTURES = SAND+1;

	// Display list ID
	const int SKY_LIST = 1;
	// Textures variables
	extern GLuint textures[NUM_TEXTURES];

	GLuint raw_texture_load(GLuint textures[], const char *filename, int width,
			int height, int texture_id);

	void create_textures();
}


#endif /* TEXTURES_H_ */
