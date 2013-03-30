/*
 * Object.h
 *
 *  Created on: Mar 30, 2013
 *      Author: Edward
 */

#ifndef OBJECT_H_
#define OBJECT_H_
#include "Vec3.h"

class Object {
public:
	Object();
	virtual ~Object();
	Vec3 get_position();
	Vec3 get_velocity();
	void set_position(Vec3);
	void set_velocity(Vec3);

private:
	Vec3 pos;
	Vec3 vel;
};

#endif /* OBJECT_H_ */
