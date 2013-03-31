/*
 * PhysicsEngine.h
 *
 *  Created on: Mar 30, 2013
 *      Author: Edward
 */

#ifndef PHYSICSENGINE_H_
#define PHYSICSENGINE_H_
#include <vector>

#include "Object.h"
#include "Octree.h"
using std::vector;

class PhysicsEngine {
public:
	static const float GRAVITY = 8.0f;
	PhysicsEngine();
	virtual ~PhysicsEngine();
	void advance_state(float t);
private:
	vector<Object*> objects;
	Octree* octree;
	void update_objects_position(float t);
	void handle_collisions();
	void reflect_objects(Object*, Object*);
};

#endif /* PHYSICSENGINE_H_ */
