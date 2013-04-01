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

#include "Game.h"
#include "stdlib.h"

const float X_CP = -1.5;
const float X_CP_2 = -.5;

const float Z_CP_1 = 3;
const float Z_CP_2 = 2;
const float Z_CP_3 = 3;
const float Z_CP_4 = 00;
const float Z_CP_5 = 1;

GLfloat* terrain;
GLshort* indices;

GLfloat ctrlpoints[4][4][3] = {
	{
			{-X_CP, -X_CP, Z_CP_1},
			{-X_CP_2, -X_CP, Z_CP_2},
			{X_CP_2, -X_CP, -Z_CP_5},
			{X_CP, -X_CP, Z_CP_2}
	},

	{
			{-X_CP, -X_CP_2, Z_CP_5},
			{-X_CP_2, -X_CP_2, Z_CP_3},
			{X_CP_2, -X_CP_2, Z_CP_4},
			{X_CP, -X_CP_2, -Z_CP_5}
	},

	{
			{-X_CP, X_CP_2, Z_CP_1},
			{-X_CP_2, X_CP_2, Z_CP_4},
			{X_CP_2, X_CP_2, Z_CP_3},
			{X_CP, X_CP_2, Z_CP_1}
	},

	{
			{-X_CP, X_CP, -Z_CP_2},
			{-X_CP_2, X_CP, -Z_CP_2},
			{X_CP_2, X_CP, Z_CP_4},
			{X_CP, X_CP, -Z_CP_5}
	}
};

void init()
{
	generate_terrain();
	indices = windLines(100, 100);
}

void draw_terrain()
{
	/*glColor3f(1.0, 1.0, 1.0);

	glPushMatrix();
	glRotatef(90.0, 1.0, 0, 0);
	glScalef(40, 40, 40);
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
	glPopMatrix();*/
	glColor3f(.7,.8,.3);
	float limit = 3;
	glPushMatrix();
		/*glTranslatef(5, 0, -10);
		glBegin(GL_POLYGON);
			/*glVertex3f(0,0,0);
			glVertex3f(2,0,0);
			glVertex3f(2,0,2);
			glVertex3f(0,0,2);*/
			/*glVertex3f(-limit, 0, -limit);

			glVertex3f(limit,0,-limit);
			glVertex3f(limit,0,limit);
			glVertex3f(-limit,0,limit);
			glVertex3f(-limit, 7, 0);
		glEnd();*/
		glVertexPointer(3, GL_FLOAT, 0, terrain);
		glDrawElements(GL_LINES, , GL_UNSIGNED_SHORT, )
	glPopMatrix();
}

void generate_terrain()
{
	terrain = new float[30000];

	int x, y, z;
	int currIndex;

	float xStart = -AREA_LIMIT;
	float xEnd = AREA_LIMIT;
	float xStep = (xEnd - xStart) / 100;

	float yStart = -AREA_LIMIT;
	float yEnd = AREA_LIMIT;
	float yStep = (yEnd - yStart) / 100;

	for (x = 0; x < 100; x++)
	{
		for (y = 0; y < 100; y++)
		{
			currIndex = x * y;
			terrain[currIndex + 0] = xStart + xStep * x;
			terrain[currIndex + 1] = rand();
			terrain[currIndex + 2] = yStart + yStep * y;
		}
	}
}

short* windLines(int totalX, int totalY)
{
	int horizLines = (totalX - 1) * 2 * totalY;
	int vertLines = (totalY - 1) * 2 * totalX;
	short* indices = new short[horizLines + vertLines];
	int y, x;
	short vertex; short id = 0;
	for (y = 0; y < totalY; y++) {
		for (x = 0; x < totalX; x++) {
			if (x < totalX - 1) {
				vertex = (short) (x + y * totalX * 2 - y * 2);
				indices[vertex + x] = id;
				indices[vertex + x + 1] = (short) (id + 1);
			}
			id++;
		}
	}

	//wind vertically
	id = 0;
	for (x = 0; x < totalX; x++) {
		id = (short) x;
		for (y = 0; y < totalY; y++) {
			if (y < totalY - 1) {
				vertex = (short) (y + x * totalY * 2 - x * 2);
				indices[horizLines + vertex + y] = id;
				indices[horizLines + vertex + y + 1] = (short) (id + totalX);
			}
			id+=totalX;
		}

	}
	return indices;
}
