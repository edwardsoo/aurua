/*
 * Bound.h
 *
 *  Created on: Mar 30, 2013
 *      Author: Edward
 */

#ifndef BOUND_H_
#define BOUND_H_

#include <stdio.h>
#include "Utils.h"
#include "SphereProxy.h"

class Bound {
public:
	Bound() {
		min = Vec3();
		max = Vec3();
	}

	Bound(Vec3 _min, Vec3 _max) {
		min = _min;
		max = _max;
	}

	~Bound() {
	}

	Bound& operator=(const Bound rhs) {
		if (this == &rhs)
			return *this;
		min = rhs.min;
		max = rhs.max;
		return *this;
	}

	double get_volume() {
		return (max.x - min.x) * (max.y - min.y) * (max.z - min.z);
	}

	double get_base_area() {
		return (max.x - min.x) * (max.y - min.y);
	}

	bool contains(Object* obj) {
		Proxy* proxy = obj->proxy;
		if (proxy == NULL)
			return false;
		if (proxy->get_type() == SPHERE_PROXY) {
			SphereProxy* s_proxy = (SphereProxy*) proxy;
			float r = s_proxy->radius;
			Vec3 pos = s_proxy->object->get_proxy_pos();
			bool in_z_span = pos.z + r > min.z && pos.z - r <= max.z;
			bool in_y_span = pos.y + r > min.y && pos.y - r <= max.y;
			bool in_x_span = pos.x + r > min.x && pos.x - r <= max.x;
			return in_z_span && in_y_span && in_x_span;
		}
		return false;
	}
	Vec3 min, max;
};

#endif /* BOUND_H_ */
