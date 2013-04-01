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

namespace Terrain
{

	const float X_CP = -1.5;
	const float X_CP_2 = -.5;

	const float Z_CP_1 = 3;
	const float Z_CP_2 = 2;
	const float Z_CP_3 = 3;
	const float Z_CP_4 = 00;
	const float Z_CP_5 = 1;

	GLfloat* terrain;
	GLshort* indices;
	int num_indices;

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

	void init_terrain()
	{
		generate_terrain();
		indices = windLines(100, 100);
		printf(" ");
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
			glEnableClientState( GL_VERTEX_ARRAY );	 // Enable Vertex Arrays
			glVertexPointer(3, GL_FLOAT, 0, terrain);
			glDrawElements(GL_LINES, num_indices, GL_UNSIGNED_SHORT, indices);
		glPopMatrix();
	}

	void generate_terrain()
	{
		terrain = new float[30000];

		int x, y, z;
		int currIndex = 0;

		float xStart = -AREA_LIMIT;
		float xEnd = AREA_LIMIT;
		float xStep = (xEnd - xStart) / 100;

		float yStart = -AREA_LIMIT;
		float yEnd = AREA_LIMIT;
		float yStep = (yEnd - yStart) / 100;

		for (y = 0; y < 100; y++)
		{
			//currIndex = 100 * y;
			for (x = 0; x < 100; x++)
			{
				terrain[currIndex + 0] = xStart + xStep * x;
				terrain[currIndex + 1] = rand() % 5;
				terrain[currIndex + 2] = yStart + yStep * y;
				currIndex += 3;
			}
		}
	}

	/**
	 * This function simply connects neighboring vertices,
	 * first going in the horizontal direction, then vertical.
	 */
	short* windLines(int totalX, int totalY)
	{
		int horizLines = (totalX - 1) * 2 * totalY;
		int vertLines = (totalY - 1) * 2 * totalX;
		num_indices = horizLines + vertLines;
		short* indices = new short[num_indices];
		int y, x;
		short vertex; int id = 0;

		//Horizontal winding
		short vertex_id = 0;
		for (y = 0; y < totalY; y++) {
			for (x = 0; x < totalX - 1; x++) {
				indices[id] = vertex_id;
				indices[id + 1] = (short) (vertex_id + 1);
				id += 2;
				vertex_id++;
			}
			vertex_id++;
		}

		short second_vertex;
		//Wind vertically
		for (x = 0; x < totalX; x++) {
			vertex_id = x;
			for (y = 0; y < totalY - 1; y++) {
				indices[id] = vertex_id;
				second_vertex = vertex_id + totalX;
				indices[id + 1] = second_vertex;
				vertex_id = second_vertex;
				id += 2;
			}
		}

		return indices;
	}

}
