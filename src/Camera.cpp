/*
 * Camera.cpp
 *
 *  Created on: Mar 27, 2013
 *      Author: Edward
 */
#include "Camera.h"
#include "Vec3.h"
#include <math.h>
#include <stdio.h>

Camera::Camera() {
	// TODO Auto-generated constructor stub
}

Camera::~Camera() {
	// TODO Auto-generated destructor stub
}

/*
 * Rotate the view vector of the camera.
 * xz_rot is the angle of rotation on the xz-plane
 * y_rot is the angle of rotation around view.y cross view.z
 * angles in radians
 */
void Camera::rotate_view(double xz_rot, double y_rot) {
	// First rotate in xz plane, get intermediate xz vector
	view.z = (sin(xz_rot) * view.x + cos(xz_rot) * view.z);
	view.x = (cos(xz_rot) * view.x - sin(xz_rot) * view.z);

	// Then change y component and update x and z
	// TODO there is some bug in here, should cap view vector with a cone at extreme y
	Vec3 view_xz = Vec3(view.x, 0, view.z);
	double no_y_xz_len = view_xz.length();
	view.y = cos(y_rot) * view.y - sin(y_rot) * no_y_xz_len;
	double xz_len = fabs(sin(y_rot) * view.y + cos(y_rot) * no_y_xz_len);
	double xz_mod = xz_len / no_y_xz_len;

	view.x *= xz_mod;
	view.z *= xz_mod;


	// angle to y-axis is arccos(cos_angle)
	// -1 <= cos_angle <= 1
	// hard cap at 10 degree near 0 and pi, cos_angle ~= +/- 0.996
	/*Vec3 y_axis(0, 1, 0);
	double cos_angle = view.dot(y_axis);
	const double hard_cap = 0.996;
	if (cos_angle < -hard_cap || cos_angle > hard_cap) {

	}*/

	view.normalize();
}
