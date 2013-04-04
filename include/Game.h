/*
 * Game.h
 *
 *  Created on: Mar 31, 2013
 *      Author: Billy
 */

#ifndef GAME_H_
#define GAME_H_

#include "PhysicsEngine.h"
#include "Player.h"
#include "AI.h"
#include "drone.h"

extern bool is_wireframe;

class Game
{
public:
	Game();
	virtual ~Game();

	PhysicsEngine* phys;
	Player* player;

	AI ai;
	Drone* test_drone;

	Object* current_object;
};

#endif /* GAME_H_ */
