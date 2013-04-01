/*
 * Drone.h
 *
 *  Created on: Mar 31, 2013
 *      Author: Edward
 */

#ifndef DRONE_H_
#define DRONE_H_

#include "Character.h"

class Drone: public Character {
public:
	Drone(Vec3, Vec3, Vec3);
	virtual ~Drone();
	void draw();
};

#endif /* DRONE_H_ */
