/*
 * Terrain.cpp
 *
 *  Created on: Mar 31, 2013
 *      Author: Billy
 */

#include "Terrain.h"
#if defined(WIN32)
#include<windows.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#endif

GLfloat ctrlpoints[4][4][3] = {
	{{-1.5, -1.5, 4.0}, {-0.5, -1.5, 2.0},
	{0.5, -1.5, -1.0}, {1.5, -1.5, 2.0}},
	{{-1.5, -0.5, 1.0}, {-0.5, -0.5, 3.0},
	{0.5, -0.5, 0.0}, {1.5, -0.5, -1.0}},
	{{-1.5, 0.5, 4.0}, {-0.5, 0.5, 0.0},
	{0.5, 0.5, 3.0}, {1.5, 0.5, 4.0}},
	{{-1.5, 1.5, -2.0}, {-0.5, 1.5, -2.0},
	{0.5, 1.5, 0.0}, {1.5, 1.5, -1.0}}
};

void draw_terrain()
{
	glColor3f(1.0, 1.0, 1.0);

	glPushMatrix();
	glRotatef(85.0, 1.0, 1.0, 1.0);
	int i, j;
	for (j = 0; j <= 8; j++)
	{
		glBegin (GL_LINE_STRIP);
		for (i = 0; i <= 30; i++)
			glEvalCoord2f((GLfloat) i / 30.0, (GLfloat) j / 8.0);
		glEnd();
		glBegin(GL_LINE_STRIP);
		for (i = 0; i <= 30; i++)
			glEvalCoord2f((GLfloat) j / 8.0, (GLfloat) i / 30.0);
		glEnd();
	}
	glPopMatrix();
}
