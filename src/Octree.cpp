/*
 * Octree.cpp
 *
 *  Created on: Mar 30, 2013
 *      Author: Edward
 */

#include "Octree.h"
using namespace std;

Octree::Octree(Bound _bound, bool _is_leaf) :
		children() {
	bound = _bound;
	Vec3 min = bound.min;
	Vec3 max = bound.max;
	print_vector(min);
	print_vector(max);
	is_leaf = _is_leaf;
	if (!is_leaf) {
		Vec3 mid = (min + max) / 2;
		child_bounds[0][0][0] = Bound(min, mid);
		child_bounds[0][0][1] = Bound(Vec3(mid.x, min.y, min.z),
				Vec3(max.x, mid.y, mid.z));
		child_bounds[0][1][0] = Bound(Vec3(min.x, mid.y, min.z),
				Vec3(mid.x, max.y, mid.z));
		child_bounds[0][1][1] = Bound(Vec3(mid.x, mid.y, min.z),
				Vec3(max.x, max.y, mid.z));
		child_bounds[1][0][0] = Bound(Vec3(min.x, min.y, mid.z),
				Vec3(mid.x, mid.y, max.z));
		child_bounds[1][0][1] = Bound(Vec3(mid.x, min.y, mid.z),
				Vec3(max.x, mid.y, max.z));
		child_bounds[1][1][0] = Bound(Vec3(min.x, mid.y, mid.z),
				Vec3(mid.x, max.y, max.z));
		child_bounds[1][1][1] = Bound(mid, max);
	}
}

Octree::~Octree() {
	int x, y, z;
	for (x = 0; x < 2; x++) {
		for (y = 0; y < 2; y++) {
			for (z = 0; z < 2; z++) {
				if (children[z][y][x] != NULL) {
					delete children[z][y][x];
				}
			}
		}
	}
}

void Octree::add(Object* obj) {
	int x, y, z;
	if (is_leaf) {
		objects.insert(obj);
	}
	for (x = 0; x < 2; x++) {
		for (y = 0; y < 2; y++) {
			for (z = 0; z < 2; z++) {
				if (child_bounds[z][y][x].contains(obj)) {
					printf("%d%d%d volume=%f\n", z, x, y,
							child_bounds[z][y][x].get_volume());
					if (children[z][y][x] == NULL) {
						if (child_bounds[z][y][x].get_volume() < 125000) {
							children[z][y][x] = new Octree(
									child_bounds[z][y][x], true);
						} else {
							children[z][y][x] = new Octree(
									child_bounds[z][y][x], false);
						}
						children[z][y][x]->add(obj);
					}
				}
			}
		}
	}
}

void Octree::remove(Object* obj) {
	int x, y, z;
	if (!bound.contains(obj)) {
		return;
	}
	if (is_leaf) {
		objects.erase(obj);
	}
	for (x = 0; x < 2; x++) {
		for (y = 0; y < 2; y++) {
			for (z = 0; z < 2; z++) {
				if (children[z][y][x] != NULL) {
					children[z][y][x]->remove(obj);
				}
			}
		}
	}
}

void Octree::get_object_pairs(vector<ObjectPair> &pairs) {
	int x, y, z;
	ObjectPair obj_pair;
	if (is_leaf) {
		for (set<Object*>::iterator itr = objects.begin(); itr != objects.end();
				itr++) {
			for (set<Object*>::iterator itr2 = objects.begin();
					itr2 != objects.end(); itr2++) {
				if (*itr < *itr2) {
					obj_pair.obj_1 = *itr;
					obj_pair.obj_2 = *itr2;
					pairs.push_back(obj_pair);
				}
			}
		}
		return;
	}
	for (x = 0; x < 2; x++) {
		for (y = 0; y < 2; y++) {
			for (z = 0; z < 2; z++) {
				if (children[z][y][x] != NULL) {
					children[z][y][x]->get_object_pairs(pairs);
				}
			}
		}
	}
}
