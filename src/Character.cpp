/*
 * Character.cpp
 *
 *  Created on: Mar 31, 2013
 *      Author: Edward
 */

#include "Character.h"

Character::Character(Vec3 _pos, Vec3 _vel, Vec3 _acc, float _radius,
		float _mass, int _life, int _stamina) :
		Object(_pos, _vel, _acc, _radius, _mass) {
	life = _life;
	stamina = _stamina;

}

Character::~Character() {
	// TODO Auto-generated destructor stub
}

