/*
 * AI.h
 *
 *  Created on: Mar 31, 2013
 *      Author: Billy
 */

#ifndef AI_H_
#define AI_H_

enum AIState
{
	AI_NORMAL,
	AI_EVADE,
	AI_KILL,
	AI_TRY_KILL
};

class AI
{
public:
	AI();
	virtual ~AI();
};

#endif /* AI_H_ */
