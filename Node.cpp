/*
 * Node.cpp
 *
 *  Created on: 24.04.2014
 *      Author: paul
 */

#include "Node.h"

Node::Node(){
	boundingBox=AABB();
	leftChild=0;
	rightChild=0;
	triangleIndex=0;
	numberOfTriangles=-1;
}

Node::Node(AABB _box, int _leftChild, int _rigthChild, int _triangleIndex, int _numberOfTriangles) {
	boundingBox=_box;
	leftChild=_leftChild;
	rightChild=_rigthChild;
	triangleIndex=_triangleIndex;
	numberOfTriangles=_numberOfTriangles;

}

Node::~Node() {
	// TODO Auto-generated destructor stub
}

