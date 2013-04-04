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
#include "textures.h"
#include "PerlinNoise.h"
#include "math.h"
#include "GameParameters.h"

namespace Terrain
{
	GLfloat* terrain;
	GLfloat* normals;
	GLint* indices;
	GLint* indices_solid;
	GLint* texture_indices;
	int num_indices;

	bool is_request_print = false;

	/**
	 * Resolution of terrain.
	 * res * res = total number of squares
	 */
	int res = 100;

	double diff;
	double diff_recp;

	Map map = MAP_STANDARD;

	const float CORNER_HEIGHT = 30;
	const float EDGE_HEIGHT = 10;
	const float NORMAL_HEIGHT = 5;

	const coords INVALID_COORD = { -1, -1 };

	void init_terrain()
	{
		diff = 2 * GameParameters::area_limit / res;
		diff_recp = 1 / (diff * diff);

		PerlinNoise::generate_p();
		terrain = generate_terrain(res);
		indices = wind_lines(res, res);
		indices_solid = wind(res, res);

		normals = generate_normals(res);
		texture_indices = generate_tex_coords(res);
		//get_height(750, 100);

		srand(time(NULL));
		printf(" ");
	}

	void draw_terrain()
	{
		glColor3f(.94,.89,.69);
		float limit = 3;
		glPushMatrix();

			glEnableClientState( GL_VERTEX_ARRAY );	 // Enable Vertex Arrays

			glVertexPointer(3, GL_FLOAT, 0, terrain);
			if (is_wireframe)
			{
				glDrawElements(GL_LINES, num_indices, GL_UNSIGNED_INT, indices);
			}
			else
			{
				glEnable(GL_TEXTURE_2D);
				glEnableClientState( GL_NORMAL_ARRAY );
				glEnableClientState( GL_TEXTURE_COORD_ARRAY );
				glNormalPointer(GL_FLOAT, 0, normals);
				glBindTexture(GL_TEXTURE_2D, Textures::textures[Textures::SAND]);
				glTexCoordPointer(2, GL_INT, 0, texture_indices);
				glDrawElements(GL_TRIANGLE_STRIP, num_indices, GL_UNSIGNED_INT, indices_solid);
				glDisable(GL_TEXTURE_2D);
			}

		glPopMatrix();
	}

	GLfloat* generate_terrain(int res)
	{
		GLfloat* vertices = new float[3 * res * res];

		int x, z;
		int currIndex = 0;

		float xStart = -GameParameters::area_limit;
		float xEnd = GameParameters::area_limit;
		float xStep = (xEnd - xStart) / res;

		float yStart = -GameParameters::area_limit;
		float yEnd = GameParameters::area_limit;
		float yStep = (yEnd - yStart) / res;

		int max_height;
		bool is_edge_y;
		bool is_edge_x;

		int lower_edge = res * 0.3;
		int upper_edge = res * 0.7;

		double temp;
		double tempY;
		double tempRes;
		double tempResY;

		float y;

		for (z = 0; z < res; z++)
		{
			is_edge_y = (z < lower_edge || z > upper_edge);
			for (x = 0; x < res; x++)
			{
				is_edge_x = (x < lower_edge || x > upper_edge);

				if (is_edge_x && is_edge_y)
				{
					// make terrain much higher at corners
					max_height = CORNER_HEIGHT;
				}
				else if (is_edge_x || is_edge_y)
				{
					// make terrain higher at edges
					max_height = EDGE_HEIGHT;
				}
				else
				{
					max_height = NORMAL_HEIGHT;
				}
				vertices[currIndex + 0] = xStart + xStep * x;

				temp = (double) 2 * x - res;
				tempY = (double) 2 * z - res;
				tempRes = temp / res * M_PI;
				tempResY = tempY / res * M_PI;

				switch (map)
				{
				case MAP_STANDARD:
					y = rand() % max_height;
					break;
				case MAP_DRAGONBALL:
					y = fabs(PerlinNoise::noise(tempRes, tempResY, tempRes - tempResY)) * max_height * 100;
					break;
				case MAP_COSINE:
					y = abs(sin(tempRes) * cos(tempResY) * (rand() % 10) - ( 40 * cos(tempRes * tempRes - (rand() % 2) * tempResY * tempResY)));
					break;
			case MAP_BLAND:
					y = (x + z) * max_height;
					break;
				}

				vertices[currIndex + 1] = y;
				vertices[currIndex + 2] = yStart + yStep * z;
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
		GLfloat n1, n2, n3;

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

				n1 = n[0];
				n2 = n[1];
				n3 = n[2];
				normals[currIndex] = n1;
				normals[currIndex + 1] = n2;
				normals[currIndex + 2] = n3;
				currIndex += 3;
			}

			//What do do at the edge? Leave them undefined for now
			normals[currIndex] = n1;
			normals[currIndex + 1] = n2;
			normals[currIndex + 2] = n3;
			currIndex += 3;
		}

		//top edge
		for (x = 0; x < res; x++)
		{
			//What do do at the edge? Leave them undefined for now

			//Actually down index
			upIndex = currIndex - res * 3;
			n1 = normals[upIndex];
			n2 = normals[upIndex + 1];
			n3 = normals[upIndex + 2];

			normals[currIndex] = n1;
			normals[currIndex + 1] = n2;
			normals[currIndex + 2] = n3;
			currIndex += 3;
		}

		return normals;
	}

	/**
	 * Generate texture coordinates
	 */
	GLint* generate_tex_coords(int res)
	{
		GLint* tex_ind = new int[2 * res * res];
		int x, y;
		int currIndex = 0;

		for (y = 0; y < res; y++)
		{
			for (x = 0; x < res; x++)
			{
				tex_ind[currIndex] = x;
				tex_ind[currIndex + 1] = y;
				currIndex += 2;
			}
		}

		return tex_ind;
	}

	/**
	 * Wind lines for wireframe terrain.
	 * This function simply connects neighboring vertices,
	 * first going in the horizontal direction, then vertical.
	 */
	int* wind_lines(int totalX, int totalY)
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

	/**
	 * Generate the indices needed for a triangle strip
	 */
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
		norm.positive();
		return norm;
	}

	double get_height(double x, double z)
	{
		coords terrain_coords = get_terrain_coords(x, z);

		if (terrain_coords.x < 0)
		{
			return 0;
		}

		int res_m1 = res - 1;
		if (terrain_coords.x < res_m1 && terrain_coords.z < res_m1)
		{
			int index = (terrain_coords.x + terrain_coords.z * res) * 3;
			double orig_x = terrain[index];
			double orig_y = terrain[index + 1];
			double orig_z = terrain[index + 2];

			double px_x = terrain[index + 3];
			double px_y = terrain[index + 4];

			index = (terrain_coords.x + (terrain_coords.z + 1) * res) * 3;
			double pz_y = terrain[index + 1];
			double pz_z = terrain[index + 2];

			index = ((terrain_coords.x + 1) + (terrain_coords.z + 1) * res) * 3;
			double pxz_y = terrain[index + 1];

			double height = 0;

			if (is_request_print)
			{
				printf("At %f,%f, o: %f x: %f z: %f xz: %f \n", x, z, orig_y, px_y, pz_y, pxz_y);
				fflush(stdout);
				is_request_print = false;
			}

			Vec3 origin = Vec3(orig_x, orig_y, orig_z);
			height = interpolate_bilinear(x, z, origin, px_x, px_y, pz_y, pz_z, pxz_y, diff_recp);

			if (x > px_x || z > pz_z)
			{
				printf("Fail \n");
				fflush(stdout);
			}
			return height;
		}
		return 0;
	}

	coords get_terrain_coords(double x, double z)
	{
		if (fabs(x) > GameParameters::area_limit || fabs(z) > GameParameters::area_limit)
		{
			return INVALID_COORD;
		}

		int area_limit_2 = (2 * GameParameters::area_limit);
		double x_prop = (x + GameParameters::area_limit) / area_limit_2;
		double x_prop_res = x_prop * res;

		coords ret;
		// Which terrain coordinate x?
		ret.x = integer_part(x_prop_res);

		double z_prop = (z + GameParameters::area_limit) / area_limit_2;
		double z_prop_res = z_prop * res;

		ret.z = integer_part(z_prop_res);

		return ret;
	}

	Vec3 get_normal(double x, double z)
	{
		coords terrain_coords = get_terrain_coords(x, z);

		if (terrain_coords.x < 0)
		{
			return Vec3();
		}

		int res_m1 = res - 1;
		if (terrain_coords.x < res_m1 && terrain_coords.z < res_m1)
		{
			int index = (terrain_coords.x + terrain_coords.z * res) * 3;

			float norm_x = normals[index];
			float norm_y = normals[index + 1];
			float norm_z = normals[index + 2];

			return Vec3(norm_x, norm_y, norm_z);
		}
		return Vec3();
	}

}
