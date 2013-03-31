/*
 * Object.cpp
 *
 *  Created on: Mar 30, 2013
 *      Author: Edward
 */

#include "Object.h"

Object::Object(Vec3 _pos, Vec3 _vel, float _radius) {
	pos = _pos;
	vel = _vel;
	radius = _radius;

}

Object::~Object() {
	// TODO Auto-generated destructor stub
}

bool Object::collide(Object *other) {
	float distance = (pos - other->pos).length();
	// Check if objects are overlapping
	if (distance < (radius + other->radius)) {
		// Check if objects are moving toward each other
		return (vel - other->vel).dot(pos - other->pos) < 0;
	}
	return false;
}
