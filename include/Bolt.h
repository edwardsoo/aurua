/*
 * Bolt.h
 *
 *  Created on: Mar 30, 2013
 *      Author: Edward
 */

#ifndef BOLT_H_
#define BOLT_H_

#include "Object.h"

class Bolt: public Object {
public:
	Bolt(Vec3 _pos, Vec3 _vel, Vec3 _acc, float _radius);
	virtual ~Bolt();
};

#endif /* BOLT_H_ */
