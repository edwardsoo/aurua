/*
 * Camera.cpp
 *
 *  Created on: Mar 27, 2013
 *      Author: Edward
 */
#include "Camera.h"
#include "Vec3.h"
#include <math.h>

Camera::Camera() {
	// TODO Auto-generated constructor stub
}

Camera::~Camera() {
	// TODO Auto-generated destructor stub
}

void Camera::set_position(Vec3 _pos) {
	pos = _pos;
}

void Camera::set_velocity(Vec3 _vel) {
	vel = _vel;
}


