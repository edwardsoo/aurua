/*
 * Proxy.cpp
 *
 *  Created on: 2013-04-05
 *      Author: Edward
 */

#include "Proxy.h"

Proxy::Proxy() {
	object = NULL;

}

Proxy::~Proxy() {
	// TODO Auto-generated destructor stub
}

bool Proxy::collide(Proxy* other) {
	return false;
}

std::string Proxy::get_type() {
	return "";
}
