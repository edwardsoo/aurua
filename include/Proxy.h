/*
 * Proxy.h
 *
 *  Created on: 2013-04-05
 *      Author: Edward
 */

#ifndef PROXY_H_
#define PROXY_H_
#define SPHERE_PROXY "sphere"
#define AABB_PROXY "aabb"

#include <string>
#include "Object.h"

class Proxy {
public:
	Proxy();
	virtual ~Proxy();
	virtual bool collide(Proxy*);
	virtual std::string get_type();
	Object* object;
};

#endif /* PROXY_H_ */
