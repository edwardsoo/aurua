/*
 * Player.cpp
 *
 *  Created on: Mar 30, 2013
 *      Author: Edward
 */

#include "Player.h"

Player::Player(Vec3 _pos, Vec3 _vel, Vec3 _acc, float _radius, float _mass) :
		Object(_pos, _vel, _acc, _radius, _mass) {
	life = 100;
	stamina = 100;

}

Player::~Player() {
	// TODO Auto-generated destructor stub
}

void Player::regenerate() {

}

