/*
 * Node.h
 *
 *  Created on: 24.04.2014
 *      Author: paul
 */

#ifndef NODE_H_
#define NODE_H_
#include "AABB.h"

//Node used to construct and manage the BVH

class Node {
public:
	AABB boundingBox;
	int leftChild;
	int rightChild;
	int triangleIndex;
	int numberOfTriangles;
	Node();
	Node(AABB _box, int _leftChild, int _rigthChild, int _triangleIndex, int _numberOfTriangles);
	virtual ~Node();
};

#endif /* NODE_H_ */
