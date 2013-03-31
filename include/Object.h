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
	Object(Vec3 _pos, Vec3 _vel, float _radius);
	virtual ~Object();
	bool collide(Object*);
	Vec3 pos;
	Vec3 vel;
	float radius;
};

#endif /* OBJECT_H_ */
