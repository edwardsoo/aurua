/*
 * SphereProxy.h
 *
 *  Created on: 2013-04-05
 *      Author: Edward
 */

#ifndef SPHEREPROXY_H_
#define SPHEREPROXY_H_

#include "Proxy.h"

class Object;
class SphereProxy: public Proxy {
public:
	SphereProxy(Object*, double);
	virtual ~SphereProxy();
	bool collide(Proxy* other);
	std::string get_type();
	double radius;
};

#endif /* SPHEREPROXY_H_ */
