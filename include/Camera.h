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
	void rotate_view(double, double);
	Vec3 view;
	Vec3 up;
};
#endif /* CAMERA_H_ */
