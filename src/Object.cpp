/*
 * Object.cpp
 *
 *  Created on: Mar 30, 2013
 *      Author: Edward
 */

#include "Object.h"

Object::Object() {
	// TODO Auto-generated constructor stub

}

Object::~Object() {
	// TODO Auto-generated destructor stub
}

Vec3 Object::get_position() {
	return pos;
}

Vec3 Object::get_velocity() {
	return vel;
}

void Object::set_position(Vec3 _pos) {
	pos = _pos;
}

void Object::set_velocity(Vec3 _vel) {
	vel = _vel;
}
