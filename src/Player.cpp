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
	cam = new Camera();
	cam->pos = _pos + Vec3(0, radius, 0);
	cam->view = cam->pos + Vec3(0, 0, 1);
	cam->up = Vec3(0, 1, 0);
}

Player::~Player() {
	delete cam;
}

void Player::regenerate() {

}

