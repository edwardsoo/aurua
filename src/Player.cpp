/*
 * Player.cpp
 *
 *  Created on: Mar 30, 2013
 *      Author: Edward
 */

#include "Player.h"
#include "SphereProxy.h"

Player::Player(Vec3 _pos, Vec3 _vel, Vec3 _acc, float _mass) :
		Character(_pos, _vel, _acc, _mass, 100, 100) {
	cam = new Camera();
	cam->view = _pos + Vec3(0, PLAYER_HEIGHT, 0) + Vec3(0, 0, 1);
	proxy = new SphereProxy(this, PLAYER_HEIGHT / 2);
	cam->up = Vec3(0, 1, 0);
	aiming = false;
}

Player::~Player() {
	delete cam;
	delete proxy;
}

Vec3 Player::get_eye() {
	return pos + Vec3(0, PLAYER_HEIGHT, 0);
}

Vec3 Player::get_proxy_pos() {
	return Vec3(0, PLAYER_HEIGHT / 2, 0);
}
