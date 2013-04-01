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
	GLfloat* normals;
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
		int res = 50;
		terrain = generate_terrain(res);
		indices = wind(res, res);
		normals = generate_normals(res);
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
			glEnableClientState( GL_NORMAL_ARRAY );
			glVertexPointer(3, GL_FLOAT, 0, terrain);
			glNormalPointer(GL_FLOAT, 0, normals);
			glDrawElements(GL_TRIANGLE_STRIP, num_indices, GL_UNSIGNED_INT, indices);
		glPopMatrix();
	}

	GLfloat* generate_terrain(int res)
	{
		GLfloat* vertices = new float[3 * res * res];

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
				vertices[currIndex + 0] = xStart + xStep * x;
				vertices[currIndex + 1] = rand() % max_height;
				vertices[currIndex + 2] = yStart + yStep * y;

				currIndex += 3;
			}
		}

		return vertices;
	}

	GLfloat* generate_normals(int res)
	{
		GLfloat* normals = new float[3 * res * res];
		int x, y, z;
		int currIndex = 0;

		Vec3 current;
		Vec3 right;
		Vec3 up;
		Vec3 n;

		int upIndex = 0;

		for (y = 0; y < res - 1; y++)
		{
			for (x = 0; x < res - 1; x++)
			{
				current = Vec3(terrain[currIndex],
						terrain[currIndex + 1],
						terrain[currIndex + 2]);

				right = Vec3(terrain[currIndex + 3],
							terrain[currIndex + 4],
							terrain[currIndex + 5]);

				upIndex = currIndex + res * 3;
				up = Vec3(terrain[upIndex],
							terrain[upIndex + 1],
							terrain[upIndex + 2]);

				n = normal(current, right, up);

				normals[currIndex] = n[0];
				normals[currIndex + 1] = n[1];
				normals[currIndex + 2] = n[2];
				currIndex += 3;
			}

			//What do do at the edge? Leave them undefined for now
			normals[currIndex] = 0;
			normals[currIndex + 1] = 0;
			normals[currIndex + 2] = 0;
			currIndex += 3;
		}

		for (x = 0; x < res; x++)
		{
			//What do do at the edge? Leave them undefined for now
			normals[currIndex] = 0;
			normals[currIndex + 1] = 0;
			normals[currIndex + 2] = 0;
			currIndex += 3;
		}

		return normals;
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
		// How many times to wind vertically
		int wind_vert = totalX * (totalY - 1);

		// How many indices for one connection
		int indices_wind = 2 * totalX;

		// How many degenerates are added per row (2(x-2) + 1)
		int degen_row = indices_wind - 3;
		// How many degenerates in total
		int degen_total = (totalY - 2) * degen_row;

		// How many iterations are required for a degenerate row
		int degen_loops = totalX - 1;

		num_indices = 2 * wind_vert + degen_total;

		int* indices = new int[num_indices];
		int wind_index;

		int row = 0, col = 0;

		// What to add to the index because of the degenerates
		int degen_add = 0;
		int degen_lv; //Loop variable for degenerates
		int degen_lv2; //2x loop variable

		// Which vertex index the degenerate is using
		int degen_connect;

		// Which index in the winding array we are dealing with right now
		int degen_index;

		// The index of the vertex in the vertex array
		int vertex;

		for (int x = 0; x < wind_vert; x++) {
			col = x - row * totalX;

			if (col % totalX == 0 && x >= totalX) {
				//new row
				row = x / totalX;

				// The index of the first degenerate for this row
				degen_index = row * indices_wind + degen_add;
				for (degen_lv = 0; degen_lv < degen_loops; degen_lv++) {
					if (degen_lv == 0)
					{
						//This is the first degenerate. It is simply the last vertex
						indices[degen_index + degen_lv] = indices[degen_index - 1];
					} else {
						degen_lv2 = 2 * degen_lv;

						//Connect to the top vertices for this row (excluding first column)
						degen_connect = indices[degen_index - 1 - 2 * degen_lv];
						indices[degen_index + degen_lv2 - 1] = degen_connect;
						indices[degen_index + degen_lv2] = degen_connect;
					}
				}

				degen_add = row * degen_row; //How many degenerate indices in total
				col = 0;
			}

			//What index are we going to use for the winding
			wind_index = x * 2 + degen_add;
			vertex = col + row * totalX;

			//Winding from bottom row to top row
			indices[wind_index] = vertex;
			indices[wind_index + 1] = vertex + totalX;
		}
		return indices;
	}

	Vec3 normal(Vec3& vert_normal, Vec3& vert_right, Vec3& vert_up) {
		Vec3 vn1 = vert_right - vert_normal;
		Vec3 vn2 = vert_up - vert_normal;

		Vec3 norm = vn1.cross(vn2);
		norm.normalize();
		return norm;
	}

}
