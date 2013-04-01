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
	PhysicsEngine(Vec3 min, Vec3 max);
	virtual ~PhysicsEngine();
	void advance_state(float t);
	void add(Object* obj);
	void remove(Object* obj);
	set<Object*> objects;
private:
	Octree* octree;
	void add_object(Object*);
	void update_objects_position(float t);
	void handle_collisions();
	void reflect_objects(Object*, Object*);
	void rebounce_objects(Object*, Object*);
};

#endif /* PHYSICSENGINE_H_ */
