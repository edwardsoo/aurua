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
	Player(Vec3 _pos, Vec3 _vel, float _radius);
	virtual ~Player();

};

#endif /* PLAYER_H_ */
