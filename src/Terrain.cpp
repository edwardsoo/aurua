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
#include "time.h"

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
	GLint* indices;
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
		generate_terrain(5);
		indices = wind(5, 5);
		srand(time(NULL));
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
		glColor3f(.94,.89,.69);
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
			glDrawElements(GL_TRIANGLE_STRIP, num_indices, GL_UNSIGNED_INT, indices);
		glPopMatrix();
	}

	void generate_terrain(int res)
	{
		terrain = new float[3 * res * res];

		int x, y, z;
		int currIndex = 0;

		float xStart = -AREA_LIMIT;
		float xEnd = AREA_LIMIT;
		float xStep = (xEnd - xStart) / res;

		float yStart = -AREA_LIMIT;
		float yEnd = AREA_LIMIT;
		float yStep = (yEnd - yStart) / res;

		int max_height;
		bool is_edge_y;
		bool is_edge_x;

		int lower_edge = res * 0.3;
		int upper_edge = res * 0.7;

		for (y = 0; y < res; y++)
		{
			is_edge_y = (y < lower_edge || y > upper_edge);
			for (x = 0; x < res; x++)
			{
				is_edge_x = (x < lower_edge || x > upper_edge);

				if (is_edge_x && is_edge_y)
				{
					max_height = 60;
				}
				else if (is_edge_x || is_edge_y)
				{
					max_height = 30;
				}
				else
				{
					max_height = 5;
				}
				terrain[currIndex + 0] = xStart + xStep * x;
				terrain[currIndex + 1] = rand() % max_height;
				terrain[currIndex + 2] = yStart + yStep * y;
				currIndex += 3;
			}
		}
	}

	/**
	 * Wind lines for wireframe terrain.
	 * This function simply connects neighboring vertices,
	 * first going in the horizontal direction, then vertical.
	 */
	int* windLines(int totalX, int totalY)
	{
		int horizLines = (totalX - 1) * 2 * totalY;
		int vertLines = (totalY - 1) * 2 * totalX;
		num_indices = horizLines + vertLines;
		int* indices = new int[num_indices];
		int y, x;
		int vertex; int id = 0;

		//Horizontal winding
		int vertex_id = 0;
		for (y = 0; y < totalY; y++) {
			for (x = 0; x < totalX - 1; x++) {
				indices[id] = vertex_id;
				indices[id + 1] = vertex_id + 1;
				id += 2;
				vertex_id++;
			}
			vertex_id++;
		}

		int second_vertex;
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

	int* wind(int totalX, int totalY) {
		// How many times to do the horizontal winding procedure
		int all = totalX * (totalY - 1);
		int addNum = 2 * totalX - 3;
		int loopNum = 1 + (addNum - 1) / 2;
		int adds = (totalY - 2) * addNum;
		num_indices = 2 * all + adds;
		int* indices = new int[num_indices];
		int index; int row = 0; int add = 0; int y; int loopIndex; int pos;
		int vertex; int col;
		for (int x = 0; x < all * 2; x++) {
			col = (x - row * totalX * 2) / 2;
			if (col % totalX == 0 && x / 2 >= totalX) {
				//new row
				row = x / 2 / totalX;
				loopIndex = row * totalX * 2 + add;
				for (y = 0; y < loopNum; y++) {
					if (y == 0) {
						indices[loopIndex + y] = indices[loopIndex - 1];
					} else {
						indices[loopIndex + 2 * y - 1] = indices[loopIndex - 1 - 2 * y];
						indices[loopIndex + 2 * y] = indices[loopIndex - 1 - 2 * y];
					}
				}
				add = row * (2 * totalX - 3);
				col = 0;
			}
			index = x + add;
			vertex = col + row * totalX;
			indices[index] = vertex;
			indices[index + 1] = vertex + totalX;
			x++;
		}
		return indices;
	}

}
