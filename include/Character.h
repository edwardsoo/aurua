/*
 * Character.h
 *
 *  Created on: Mar 31, 2013
 *      Author: Edward
 */

#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "Object.h"

class Character: public Object {
public:
	Character(Vec3, Vec3, Vec3, float, int, int);
	virtual ~Character();
	void regenerate();
	int life, stamina;
};

#endif /* CHARACTER_H_ */
