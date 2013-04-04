/*
 * AI.cpp
 *
 *  Created on: Mar 31, 2013
 *      Author: Billy
 */

#include "AI.h"
#include "Object.h"

AI::AI()
{
	this->state = AI_NORMAL;
}

AI::~AI()
{
}

void AI::go_to_random_pos()
{
}

void AI::evade_enemy()
{
}

void AI::kill_enemy()
{
}

void AI::set_enemy(Object* enemy)
{
	this->enemy = enemy;
}

void AI::update()
{
}

Vec3 AI::get_enemy_pos()
{
	return this->enemy->pos;
}
