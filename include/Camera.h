/*
 * Camera.h
 *
 *  Created on: Mar 27, 2013
 *      Author: Edward
 */

#ifndef CAMERA_H_
#define CAMERA_H_

class Camera {
public:
	Camera();
	~Camera();
	void set_position(double pos_x, double pos_y, double pos_z);
	void set_view(double view_x, double view_y, double view_z);
	void set_up(double up_x, double up_y, double up_z);
	void set_velocity(double vel_x, double vel_y, double vel_z);
	void rotate_view(double x, double y, double z);

	double pos[3];
	double view[3];
	double up[3];
	double vel[3];
};
#endif /* CAMERA_H_ */
