/*
 * PhysicsEngine.cpp
 *
 *  Created on: Mar 30, 2013
 *      Author: Edward
 */

#include <vector>
#include <stdio.h>

#include "PhysicsEngine.h"

static const double FRICTION = 0.8;

PhysicsEngine::PhysicsEngine(Vec3 min, Vec3 max) {
	Bound bound = Bound(min, max);
	octree = new Octree(bound, false);
}

PhysicsEngine::~PhysicsEngine() {
	delete octree;
}

void PhysicsEngine::add_object(Object* o) {
	this->objects.insert(o);
}

void PhysicsEngine::advance_state(float t) {
	update_objects_position(t);
	handle_collisions();
	apply_global(t);
}

void PhysicsEngine::update_objects_position(float dt_ms) {
	float dt_sec = dt_ms / 1000.0;
	for (set<Object*>::iterator itr = objects.begin(); itr != objects.end();
			itr++) {
		Object* obj = *itr;
		Vec3 old_pos = obj->pos;

		// Accelerate
		if (obj->acc.length() != 0) {
			obj->vel += obj->acc * dt_sec;
			obj->acc = Vec3(0, 0, 0);
		}

		// Move object
		obj->pos += obj->vel * dt_sec;

		octree->remove(obj);
		octree->add(obj);
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
			// reflect_objects(obj_1, obj_2);
			rebounce_objects(obj_1, obj_2);
		}
	}
}

void PhysicsEngine::apply_global(float dt_ms) {
	float dt_sec = dt_ms / 1000.0;
	for (set<Object*>::iterator itr = objects.begin(); itr != objects.end();
			itr++) {
		Object* obj = *itr;

		// Apply shitty physics friction
		obj->vel *= pow(1 - FRICTION, dt_sec);
	}
}

void PhysicsEngine::reflect_objects(Object* obj_1, Object* obj_2) {
	// Reflect object velocities around normal of collision
	// disregard momentum, no energy loss
	// vel' = vel - 2*(n*(n dot vel))
	printf("Before:\n");
	debug_vec3(obj_1->vel);
	debug_vec3(obj_2->vel);

	Vec3 n = obj_1->pos - obj_2->pos;
	float net_mass = obj_1->mass + obj_2->mass;
	n.normalize();
	obj_1->vel -= n * (n.dot(obj_1->vel)) * 2 * (obj_2->mass / net_mass);
	obj_2->vel -= n * (n.dot(obj_2->vel)) * 2 * (obj_1->mass / net_mass);

	printf("After:\n");
	debug_vec3(obj_1->vel);
	debug_vec3(obj_2->vel);
}

void PhysicsEngine::rebounce_objects(Object* obj_1, Object* obj_2) {
	printf("Before:\n");
	debug_vec3(obj_1->vel);
	debug_vec3(obj_2->vel);

	float net_mass = obj_1->mass + obj_2->mass;
	float net_magnitude = obj_2->vel.length() + obj_1->vel.length();
	Vec3 disp_1 = obj_1->pos - obj_2->pos;
	disp_1.normalize();
	Vec3 disp_2 = obj_2->pos - obj_1->pos;
	disp_2.normalize();

	obj_1->vel = disp_1 * (net_magnitude * (obj_2->mass / net_mass));
	obj_2->vel = disp_2 * (net_magnitude * (obj_1->mass / net_mass));

	printf("After:\n");
	debug_vec3(obj_1->vel);
	debug_vec3(obj_2->vel);
}

void PhysicsEngine::add(Object* obj) {
	objects.insert(obj);
	octree->add(obj);
}

void PhysicsEngine::remove(Object* obj) {
	objects.erase(obj);
	octree->remove(obj);
}

