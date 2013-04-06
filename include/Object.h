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
	Object(Vec3, Vec3, Vec3, float, float, Proxy*);
	virtual ~Object();
	bool collide(Object*);
	virtual void draw();
	Vec3 get_proxy_pos();
	Proxy* proxy;
	Vec3 pos;
	Vec3 vel;
	Vec3 acc;
	float mass;
};

struct ObjectPair {
	Object *obj_1;
	Object *obj_2;
};

#endif /* OBJECT_H_ */
