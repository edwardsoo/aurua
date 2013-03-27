/*
 * Camera.cpp
 *
 *  Created on: Mar 27, 2013
 *      Author: Edward
 */
#include "Camera.h"

Camera::Camera() {
	// TODO Auto-generated constructor stub
}

Camera::~Camera() {
	// TODO Auto-generated destructor stub
}

void Camera::set_position(double pos_x, double pos_y, double pos_z) {
	pos[0] = pos_x;
	pos[1] = pos_y;
	pos[2] = pos_z;
}

void Camera::set_velocity(double vel_x, double vel_y, double vel_z) {
	vel[0] = vel_x;
	vel[1] = vel_y;
	vel[2] = vel_z;
}

