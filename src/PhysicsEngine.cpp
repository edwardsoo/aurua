/*
 * PhysicsEngine.cpp
 *
 *  Created on: Mar 30, 2013
 *      Author: Edward
 */

#include "PhysicsEngine.h"
#include <vector>

PhysicsEngine::PhysicsEngine() {
	// TODO Auto-generated constructor stub

}

PhysicsEngine::~PhysicsEngine() {
	// TODO Auto-generated destructor stub
}

void PhysicsEngine::advance_state(float t) {
	handle_collisions();
}

void PhysicsEngine::update_objects_position(float t) {
	unsigned int i;
	for (i = 0; i < objects.size(); i++) {
		Object* obj = objects[i];
		obj->pos += obj->vel;
	}
}

void PhysicsEngine::handle_collisions() {
	unsigned int i;
	vector<ObjectPair> pairs;
	octree->get_object_pairs(pairs);
	for (i = 0; i < pairs.size(); i++) {
		ObjectPair pair = pairs[i];
		Object* obj_1 = pair.obj_1;
		Object* obj_2 = pair.obj_2;
		if (obj_1->collide(obj_2)) {
			reflect_objects(obj_1, obj_2);
		}
	}
}

void PhysicsEngine::reflect_objects(Object* obj_1, Object* obj_2) {
	// Reflect object velocities around normal of collision
	// disregard momentum, no energy loss
	// vel' = vel - 2*(n*(n dot vel))
	Vec3 n = obj_1->pos - obj_2->pos;
	n.normalize();
	obj_1->vel -= n * (n.dot(obj_1->vel)) * 2;
	obj_2->vel -= n * (n.dot(obj_2->vel)) * 2;
}

