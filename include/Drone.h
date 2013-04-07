/*
 * Drone.h
 *
 *  Created on: Mar 31, 2013
 *      Author: Edward
 */

#ifndef DRONE_H_
#define DRONE_H_

#include "Character.h"

static const float DRONE_HOVER_HEIGHT = 3.0f;
static const float DRONE_RADIUS = 1.0f;

class Drone: public Character {
public:
	Drone(Vec3, Vec3, Vec3);
	virtual ~Drone();
	void draw();
	Vec3 get_proxy_pos();
};

#endif /* DRONE_H_ */
