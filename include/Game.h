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

class Game
{
public:
	Game();
	virtual ~Game();

	PhysicsEngine* phys;
	Player* player;
};

#endif /* GAME_H_ */
