/*
 * Player.h
 *
 *  Created on: Mar 30, 2013
 *      Author: Edward
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "Object.h"

class Player: public Object {
public:
	Player(Vec3 _pos, Vec3 _vel, Vec3 _acc, float _radius, float _mass);
	virtual ~Player();
	void regenerate();

	int life, stamina;
};

#endif /* PLAYER_H_ */
