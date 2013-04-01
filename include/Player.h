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

static const float WALK_SPEED = 50.0f;
static const float RUN_SPEED = 150.0f;
static const float ACC = 200.0f;
static const float SLOW = 10.0f;
static const float AIM_DIST = 50.0f;

class Player: public Character {
public:
	Player(Vec3, Vec3, Vec3, float, float);
	virtual ~Player();
	Vec3 get_eye();
	Camera* cam;
	bool aiming;
	Vec3 aim;
};

#endif /* PLAYER_H_ */
