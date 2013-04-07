/*
 * Player.h
 *
 *  Created on: Mar 30, 2013
 *      Author: Edward
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "Character.h"
#include "Camera.h"

static const float WALK_SPEED = 30.0f;
static const float RUN_SPEED = 100.0f;
static const float ACC = 100.0f;
static const float SLOW = 10.0f;
static const float AIM_DIST = 50.0f;
static const float PLAYER_HEIGHT = 5.0f;

class Player: public Character {
public:
	Player(Vec3, Vec3, Vec3, float);
	virtual ~Player();
	Vec3 get_proxy_pos();
	Vec3 get_eye();
	Camera* cam;
	bool aiming;
	Vec3 aim;
};

#endif /* PLAYER_H_ */
