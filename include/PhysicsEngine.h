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
	static const double GRAVITY = -20.0;
	static const double FRICTION = 0.8;
	static const double NORMAL_FORCE = 0.5;
	static const double ABS_GROUND_TOL = 0.05;
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
	bool object_on_ground(Object* obj);
	void pre_move_change(float t);
	void post_move_change(float t);
	void reflect_objects(Object*, Object*);
	void rebounce_objects(Object*, Object*);
};

#endif /* PHYSICSENGINE_H_ */
