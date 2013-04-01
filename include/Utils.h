#ifndef UTILS_H_
#define UTILS_H_

#include "Camera.h"

// debug matrix
void print_matrix(double* m);

// debug vector
void print_vector(Vec3 vec3);

// debug vector
void print_vector(double* m);

// debug camera
void debug_camera(Camera* cam);

// debug Vec3
void debug_vec3(Vec3 *vec);

// get system time in ms, only useful for time difference
unsigned long get_system_time();

// inversion routine originally from MESA
bool invert_pose(float *m);

void draw_grid();

#endif /* UTILS_H_ */
