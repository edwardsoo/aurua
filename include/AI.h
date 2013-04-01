/*
 * AI.h
 *
 *  Created on: Mar 31, 2013
 *      Author: Billy
 */
#ifndef AI_H_
#define AI_H_
#include "Vec3.h"

enum AIState
{
	AI_NORMAL,
	AI_EVADE,
	AI_KILL
};

class AI
{
public:
	AI();
	virtual ~AI();

	void set_enemy();

	void go_to_random_pos();
	void evade_enemy();
	virtual void kill_enemy();

private:
	AIState state;

	Vec3 get_enemy_pos();
};

#endif /* AI_H_ */
