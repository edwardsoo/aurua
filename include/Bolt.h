/*
 * Bolt.h
 *
 *  Created on: Mar 30, 2013
 *      Author: Edward
 */

#ifndef BOLT_H_
#define BOLT_H_

#include "Object.h"
static const float BOLT_RADIUS = 0.1f;
static const float BOLT_SPEED = 500.0f;

class Bolt: public Object {
public:

	Bolt(Vec3 _pos, Vec3 _vel, Vec3 _acc);
	virtual ~Bolt();
	void draw();
};

#endif /* BOLT_H_ */
