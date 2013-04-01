/*
 * Player.cpp
 *
 *  Created on: Mar 30, 2013
 *      Author: Edward
 */

#include "Player.h"

Player::Player(Vec3 _pos, Vec3 _vel, Vec3 _acc, float _radius, float _mass) :
	Character(_pos, _vel, _acc, _radius, _mass, 100, 100) {
	cam = new Camera();
	cam->view = _pos + Vec3(0, radius, 0) + Vec3(0, 0, 1);
	cam->up = Vec3(0, 1, 0);
}

Player::~Player() {
	delete cam;
}

