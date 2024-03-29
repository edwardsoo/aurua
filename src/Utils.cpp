#include "Utils.h"

#include <stdio.h>
#if defined(WIN32)
#include<windows.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#endif

#include "Game.h"
#include "math.h"
#include "GameParameters.h"

// debug matrix
void print_matrix(double* m) {
	printf("%f %f %f %f\n%f %f %f %f\n %f %f %f %f\n%f %f %f %f\n\n", m[0],
			m[4], m[8], m[12], m[1], m[5], m[9], m[13], m[2], m[6], m[10],
			m[14], m[3], m[7], m[11], m[15]);

}

// debug vector
void print_vector(double* m) {
	printf("%f %f %f %f\n", m[0], m[1], m[2], m[3]);
}

// debug camera
void debug_camera(Camera* cam) {
	printf("view %f %f %f\n", cam->view.x, cam->view.y, cam->view.z);
	printf("up %f %f %f\n", cam->up.x, cam->up.y, cam->up.z);
}

// debug Vec3
void debug_vec3(Vec3 vec) {
	printf("Vec3: x=%f y=%f z=%f\n", vec.x, vec.y, vec.z);
}

// debug Player
void debug_player(Player *player) {
	printf("Player:\n");
	printf("pos: x=%f y=%f z=%f\n", player->pos.x, player->pos.y,
			player->pos.z);
	printf("vel: x=%f y=%f z=%f\n", player->vel.x, player->vel.y,
			player->vel.z);
	printf("acc: x=%f y=%f z=%f\n", player->acc.x, player->acc.y,
			player->acc.z);
	printf("\n");
}

// get system time in ms, only useful for time difference
unsigned long get_system_time() {
	unsigned long time = 0;
#if _WIN32
	time = GetTickCount();
#elif linux
	struct timeval tv;
	gettimeofday(&tv, NULL);
	time = (unsigned long) (tv.tv_sec * 1000.0 + tv.tv_usec / 1000.0);
#endif
	return time;
}

// inversion routine originally from MESA
bool invert_pose(float *m) {
	float inv[16], det;
	int i;

	inv[0] = m[5] * m[10] * m[15] - m[5] * m[11] * m[14] - m[9] * m[6] * m[15]
			+ m[9] * m[7] * m[14] + m[13] * m[6] * m[11] - m[13] * m[7] * m[10];

	inv[4] = -m[4] * m[10] * m[15] + m[4] * m[11] * m[14] + m[8] * m[6] * m[15]
			- m[8] * m[7] * m[14] - m[12] * m[6] * m[11] + m[12] * m[7] * m[10];

	inv[8] = m[4] * m[9] * m[15] - m[4] * m[11] * m[13] - m[8] * m[5] * m[15]
			+ m[8] * m[7] * m[13] + m[12] * m[5] * m[11] - m[12] * m[7] * m[9];

	inv[12] = -m[4] * m[9] * m[14] + m[4] * m[10] * m[13] + m[8] * m[5] * m[14]
			- m[8] * m[6] * m[13] - m[12] * m[5] * m[10] + m[12] * m[6] * m[9];

	inv[1] = -m[1] * m[10] * m[15] + m[1] * m[11] * m[14] + m[9] * m[2] * m[15]
			- m[9] * m[3] * m[14] - m[13] * m[2] * m[11] + m[13] * m[3] * m[10];

	inv[5] = m[0] * m[10] * m[15] - m[0] * m[11] * m[14] - m[8] * m[2] * m[15]
			+ m[8] * m[3] * m[14] + m[12] * m[2] * m[11] - m[12] * m[3] * m[10];

	inv[9] = -m[0] * m[9] * m[15] + m[0] * m[11] * m[13] + m[8] * m[1] * m[15]
			- m[8] * m[3] * m[13] - m[12] * m[1] * m[11] + m[12] * m[3] * m[9];

	inv[13] = m[0] * m[9] * m[14] - m[0] * m[10] * m[13] - m[8] * m[1] * m[14]
			+ m[8] * m[2] * m[13] + m[12] * m[1] * m[10] - m[12] * m[2] * m[9];

	inv[2] = m[1] * m[6] * m[15] - m[1] * m[7] * m[14] - m[5] * m[2] * m[15]
			+ m[5] * m[3] * m[14] + m[13] * m[2] * m[7] - m[13] * m[3] * m[6];

	inv[6] = -m[0] * m[6] * m[15] + m[0] * m[7] * m[14] + m[4] * m[2] * m[15]
			- m[4] * m[3] * m[14] - m[12] * m[2] * m[7] + m[12] * m[3] * m[6];

	inv[10] = m[0] * m[5] * m[15] - m[0] * m[7] * m[13] - m[4] * m[1] * m[15]
			+ m[4] * m[3] * m[13] + m[12] * m[1] * m[7] - m[12] * m[3] * m[5];

	inv[14] = -m[0] * m[5] * m[14] + m[0] * m[6] * m[13] + m[4] * m[1] * m[14]
			- m[4] * m[2] * m[13] - m[12] * m[1] * m[6] + m[12] * m[2] * m[5];

	inv[3] = -m[1] * m[6] * m[11] + m[1] * m[7] * m[10] + m[5] * m[2] * m[11]
			- m[5] * m[3] * m[10] - m[9] * m[2] * m[7] + m[9] * m[3] * m[6];

	inv[7] = m[0] * m[6] * m[11] - m[0] * m[7] * m[10] - m[4] * m[2] * m[11]
			+ m[4] * m[3] * m[10] + m[8] * m[2] * m[7] - m[8] * m[3] * m[6];

	inv[11] = -m[0] * m[5] * m[11] + m[0] * m[7] * m[9] + m[4] * m[1] * m[11]
			- m[4] * m[3] * m[9] - m[8] * m[1] * m[7] + m[8] * m[3] * m[5];

	inv[15] = m[0] * m[5] * m[10] - m[0] * m[6] * m[9] - m[4] * m[1] * m[10]
			+ m[4] * m[2] * m[9] + m[8] * m[1] * m[6] - m[8] * m[2] * m[5];

	det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

	if (det == 0)
		return false;

	det = 1.0 / det;

	for (i = 0; i < 16; i++)
		m[i] = inv[i] * det;

	return true;
}

void draw_grid() {
	float unit = 5;
	for (float i = -GameParameters::area_limit; i <= GameParameters::area_limit; i += unit) {
		glBegin(GL_LINES);
		glColor4f(1, 1, 1, 0.5);
		glVertex3f(-GameParameters::area_limit, 0, i);
		glVertex3f(GameParameters::area_limit, 0, i);
		glVertex3f(i, 0, -GameParameters::area_limit);
		glVertex3f(i, 0, GameParameters::area_limit);
		glEnd();
	}
}

double fractional_part(double d) {
	return fmod(d, 1);
}

double integer_part(double d) {
	return d - fractional_part(d);
}

double interpolate_bilinear
		(
			double x,
			double z,
			Vec3& orig,
			double px_x,
			double px_y,
			double pz_y,
			double pz_z,
			double pxz_y,
			double diff
		)
{
	double f;
	f =
		/*(	1
			/
			((px_x - orig.x) * (pz_z - orig.z))
		)*/
		diff
		*
		(
		orig.y * (px_x - x) * (pz_z - z)
	+	px_y * (x - orig.x) * (pz_z - z)
	+	pz_y * (px_x - x) * (z - orig.z)
	+	pxz_y * (x - orig.x) * (z - orig.z)
		);
	/*f = orig.y +
			(px_z - orig.z) * (x - (long)x)
			+ (pz_z - orig.z) * (z - (long)z)
			+ (pz_z - hx1z0 - hx0z1 + hx1z1) * (x - (int)x) * (z - (int)z);*/
	return f;
}
