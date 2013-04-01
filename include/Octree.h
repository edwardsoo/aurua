/*
 * Octree.h
 *
 *  Created on: Mar 30, 2013
 *      Author: Edward
 */

#ifndef OCTREE_H_
#define OCTREE_H_

#include <set>
#include <stdlib.h>
#include <vector>

#include "Object.h"
#include "Bound.h"

using std::vector;
using std::set;

class Octree {

public:

	static const float MIN_TREE_VOLUME = 1000000000;
	Octree(Bound, bool);
	virtual ~Octree();
	void add(Object* obj);
	void remove(Object* obj);
	int size();
	void get_object_pairs(vector<ObjectPair> &pairs);

private:

	/*
	 * children[*][*][0] contains subtrees with space within minX-midX
	 * children[*][0][*] contains subtrees with space within minY-midY
	 * children[0][*][*] contains subtrees with space within minZ-midZ
	 * Lazy instantiation of children
	 */
	Octree *children[2][2][2];
	Bound child_bounds[2][2][2];

	// Whether this has any subtree
	bool is_leaf;

	// Objects if this is a leaf
	set<Object*> objects;

	// Bound of this
	Bound bound;

};

#endif /* OCTREE_H_ */
