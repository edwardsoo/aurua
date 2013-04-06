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
	radius = 0;
	mass = 0;
	is_on_ground = true;
}

Object::Object(Vec3 _pos, Vec3 _vel, Vec3 _acc, float _radius, float _mass,
		Proxy* _proxy) {
	pos = _pos;
	vel = _vel;
	acc = _acc;
	radius = _radius;
	mass = _mass;
	is_on_ground = true;
	proxy = _proxy;
}

Object::~Object() {
	// TODO Auto-generated destructor stub
}
