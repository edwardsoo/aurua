/*
 * Object.cpp
 *
 *  Created on: Mar 30, 2013
 *      Author: Edward
 */

#include "Object.h"

Object::Object() {
	proxy = NULL;
	pos = Vec3();
	vel = Vec3();
	acc = Vec3();
	mass = 0;
}

Object::Object(Vec3 _pos, Vec3 _vel, Vec3 _acc, float _mass) {
	pos = _pos;
	vel = _vel;
	acc = _acc;
	mass = _mass;
	proxy = NULL;
}

Object::~Object() {
	// TODO Auto-generated destructor stub
}

Vec3 Object::get_proxy_pos() {
	return Vec3(0, 0, 0);
}

void Object::draw() {
}
