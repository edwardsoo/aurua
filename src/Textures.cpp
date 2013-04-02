#if defined(__APPLE_CC__)
#include<OpenGL/gl.h>
#include<OpenGL/glu.h>
#include<GLUT/glut.h>
#elif defined(WIN32)
#include<windows.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#else
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<stdint.h>
#endif

#include "Textures.h"
#include <stdio.h>
#include <stdlib.h>

namespace Textures
{
	GLuint textures[NUM_TEXTURES];
	/**
	 * From http://en.wikibooks.org/wiki/OpenGL_Programming/Intermediate/Textures
	 */
	GLuint raw_texture_load(GLuint textures[], const char *filename, int width,
			int height, int texture_id)
	{
		unsigned char *data;
		FILE *file;
		GLfloat border_color[] = { 0, 0, 0, 0 };

		// open texture data
		file = fopen(filename, "rb");
		if (file == NULL) {
			fprintf(stderr, "Error: cannot open %s.\n", filename);
			fflush(stderr);
			return 0;
		}

			// allocate buffer
		data = (unsigned char*) malloc(width * height * 4);

		// read texture data
		fread(data, width * height * 4, 1, file);
		fclose(file);

		// allocate a texture name
		glGenTextures(1, &textures[texture_id]);

		// select our current texture
		glBindTexture(GL_TEXTURE_2D, textures[texture_id]);

		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border_color);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
				GL_LINEAR_MIPMAP_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

		// build our texture mipmaps
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE,
				data);

		// free buffer
		free(data);

		return 1;
	}
}
