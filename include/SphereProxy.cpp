/*
 * SphereProxy.cpp
 *
 *  Created on: 2013-04-05
 *      Author: Edward
 */

#include "SphereProxy.h"

SphereProxy::SphereProxy(Object* _object, double _radius) {
	object = _object;
	radius = _radius;

}

SphereProxy::~SphereProxy() {
	// TODO Auto-generated destructor stub
}

bool SphereProxy::collide(Proxy *other) {
	bool overlap;
	float distance =
			(object->get_proxy_pos() - other->object->get_proxy_pos()).length();
	if (other->get_type() == SPHERE_PROXY) {
		SphereProxy* s_other = (SphereProxy*) other;
		float distance = (object->get_proxy_pos()
				- s_other->object->get_proxy_pos()).length();
		// Check if objects are overlapping
		overlap = distance < (radius + s_other->radius);
	}

	if (overlap) {
		// Check if objects are moving toward each other
		return (object->vel - other->object->vel).dot(
				object->get_proxy_pos() - other->object->get_proxy_pos())
				< 0;
	}
	return false;
}

std::string SphereProxy::get_type() {
	return SPHERE_PROXY;
}
