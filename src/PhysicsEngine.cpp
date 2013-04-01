/*
 * PhysicsEngine.cpp
 *
 *  Created on: Mar 30, 2013
 *      Author: Edward
 */

#include "PhysicsEngine.h"
#include <vector>

PhysicsEngine::PhysicsEngine(Vec3 min, Vec3 max) {
	Bound bound = Bound(min, max);
	octree = new Octree(bound, false);
}

PhysicsEngine::~PhysicsEngine() {
	delete octree;
}

void PhysicsEngine::add_object(Object* o)
{
	this->objects.insert(o);
}

void PhysicsEngine::advance_state(float t) {
	update_objects_position(t);
	handle_collisions();
}

void PhysicsEngine::update_objects_position(float t) {
	unsigned int i;
	for (set<Object*>::iterator itr = objects.begin(); itr != objects.end(); itr++) {
		Object* obj = *itr;
		Vec3 old_pos = obj->pos;
		obj->vel += obj->acc*t;
		obj->pos += obj->vel*t;
		if (obj->pos != old_pos) {
			octree->remove(obj);
			octree->add(obj);
		}
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

void PhysicsEngine::add(Object* obj) {
	objects.insert(obj);
	//octree->add(obj);
}

void PhysicsEngine::remove(Object* obj) {
	objects.erase(obj);
	octree->remove(obj);
}

set<Object*>::iterator PhysicsEngine::objects_iterator() {
	return objects.begin();
}

