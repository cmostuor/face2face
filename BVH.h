/*
 * BVH.h
 *
 *  Created on: 24.04.2014
 *      Author: paul
 */

#ifndef BVH_H_
#define BVH_H_

#include "AABB.h"
#include "Triangle.h"
#include "Node.h"
#include "TraversalStack.h"

//Bounding Volume Hirachie Tree, containing Axis Aligned Boundingboxes

class BVH {
	AABB boundingBox;
	Triangle* triangles;
	int numberOfTriangles;
	Node* nodes;
	int addedNodes;
	int* indices;

	void buildBVH(int nodeIndex, int triangleIndex, int numberOfTriangles, AABB box, int depth);
	int sortTris(int trianglIndex, int numberOfTris, float plane, int axis, AABB &leftBox, AABB &rightBox);
	//used to recursivly build the BVH
	void intersectRecursive(int nodeIndex, HitRec &rec, const Ray &ray, QVector3D invRayDir, const unsigned int raySign[3][2]);

public:
	BVH();
	BVH(Triangle* _triangles, unsigned int _numberOfTriangles);
	virtual ~BVH();
	HitRec intersect(const Ray &ray);
	AABB* getBoundingBox();


};

#endif /* BVH_H_ */
