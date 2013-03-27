#include "Global.h"
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

// Day of year
float day[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

float progress[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

float DAYS[9] = {100, 200, 365, 400, 500, 600, 700, 800, 900};
bool isTimeProgressing = false;

float getPlanetLocation(int planet) {
	return 2.0f * (planet + 1);
}

float speedFactor[10] = { 1.0f, .8f, .6f, .5f, .4f, .3f, .2f, .1f, .2f, 0.1f };

void updateDay(int planet) {
	float today = ++day[planet];
	if (today > DAYS[planet]) {
		day[planet] = 0;
	}
	progress[planet] = today / DAYS[planet];
}

void toggleTime() {
	isTimeProgressing = !isTimeProgressing;
}

/**
 * From http://en.wikibooks.org/wiki/OpenGL_Programming/Intermediate/Textures
 */
GLuint raw_texture_load(const char *filename, int width, int height)
{
	GLuint texture;
	unsigned char *data;
	FILE *file;

	// open texture data
	file = fopen(filename, "rb");
	if (file == NULL) return 0;

	// allocate buffer
	data = (unsigned char*) malloc(width * height * 4);

	// read texture data
	fread(data, width * height * 4, 1, file);
	fclose(file);

	// allocate a texture name
	glGenTextures(1, &texture);

	// select our current texture
	glBindTexture(GL_TEXTURE_2D, texture);

	// select modulate to mix texture with color for shading
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_DECAL);

	// when texture area is small, bilinear filter the closest mipmap
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	// when texture area is large, bilinear filter the first mipmap
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// texture should tile
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// build our texture mipmaps
	gluBuild2DMipmaps(GL_TEXTURE_2D, 4, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);

	// free buffer
	free(data);

	return texture;
}
