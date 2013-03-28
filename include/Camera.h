/*
 * Camera.h
 *
 *  Created on: Mar 27, 2013
 *      Author: Edward
 */

#ifndef CAMERA_H_
#define CAMERA_H_
#include "Vec3.h"

class Camera {
public:
	Camera();
	~Camera();
	void set_position(Vec3);
	void set_center(Vec3);
	void set_up(Vec3);
	void set_velocity(Vec3);
	void rotate_view(Vec3);
	double* get_gaze();
	void debug();

	Vec3 pos;
	Vec3 center;
	Vec3 up;
	Vec3 vel;
};
#endif /* CAMERA_H_ */
