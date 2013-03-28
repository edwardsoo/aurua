/*
 * Camera.cpp
 *
 *  Created on: Mar 27, 2013
 *      Author: Edward
 */
#include "Camera.h"
#include "Vec3.h"
#include <math.h>
#include<stdio.h>

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

void Camera::debug() {
	printf("pos %f %f %f\n", pos.x, pos.y, pos.z);
	printf("center %f %f %f\n", center.x, center.y, center.z);
	printf("up %f %f %f\n", up.x, up.y, up.z);
	printf("vel %f %f %f\n", vel.x, vel.y, vel.z);
}

