/*
 * Game.cpp
 *
 *  Created on: Mar 31, 2013
 *      Author: Billy
 */

#include "Game.h"

bool is_wireframe = true;

Game::Game()
{
	// Collision stuff
	phys = new PhysicsEngine(Vec3(-1000, -1000, -1000), Vec3(1000, 1000, 1000));

	// Player initializations

	player = new Player(Vec3(0, 2, 0), Vec3(0, 0, 0), Vec3(0, 0, 0), 2, 1);
	phys->add(player);

	this->ai = AI();
}

Game::~Game()
{
	// TODO Auto-generated destructor stub
	delete phys;
	delete player;
}

