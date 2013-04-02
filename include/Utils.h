#ifndef UTILS_H_
#define UTILS_H_

#include "Camera.h"
#include "Player.h"
#include "math.h"

void print_matrix(double* m);
void print_vector(double* m);
void debug_camera(Camera* cam);
void debug_vec3(Vec3 vec);
void debug_player(Player *player);
unsigned long get_system_time();
bool invert_pose(float *m);
void draw_grid();

double fractional_part(double d);

double integer_part(double d);

/*float interpolate_bilinear
	(
		float x,
		float z,
		Vec3& orig,
		float px_x,
		float px_y,
		float pz_y,
		float pz_z,
		float pxz_y
	);*/

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
	);

#endif /* UTILS_H_ */
