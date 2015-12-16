/*
 * BVH.cpp
 *
 *  Created on: 24.04.2014
 *      Author: paul
 */

#include "BVH.h"
#include <cmath>
#include <cfloat>



BVH::BVH(void)
{
}


BVH::BVH(Triangle* _triangles, unsigned int _numberOfTriangles) {
	triangles=_triangles;
	numberOfTriangles=_numberOfTriangles;
	boundingBox=AABB();
	Triangle a = Triangle(QVector3D(),QVector3D(),QVector3D()); //needs to be there to call getAABB
	a.getAABB(triangles, numberOfTriangles, boundingBox);

	nodes=new Node[numberOfTriangles*2];
	indices=new int[numberOfTriangles];
	for (int i = 0; i < numberOfTriangles; i++)
			indices[i] = i;

	addedNodes=1; //root-Node
	buildBVH(0, 0, numberOfTriangles, boundingBox, 0);
}

void BVH::buildBVH(int nodeIndex, int triangleIndex, int numberOfTriangles, AABB box, int depth){
	nodes[nodeIndex].boundingBox=box;

	if (numberOfTriangles <= 3 || depth > 63)
	{ // make leaf (normal termination)
		nodes[nodeIndex].leftChild = -1;
		nodes[nodeIndex].rightChild = -1;
		nodes[nodeIndex].triangleIndex = triangleIndex;
		nodes[nodeIndex].numberOfTriangles = numberOfTriangles;
	}
	else
	{
		float plane;
		int split;
		AABB leftBox, rightBox;
		bool foundSplit = false;
		int axis = box.getMaxAxis();

		for (int i = 0; i < 3; i++)
		{ // if split failes in dim(axis), try to split along other dimensions
			plane = (box.bounds[0][axis] + box.bounds[1][axis]) * 0.5f;
			split = sortTris(triangleIndex, numberOfTriangles, plane, axis, leftBox, rightBox);
			if (split != 0 && split != numberOfTriangles)
			{
				foundSplit = true;
				break;
			}
			axis = (axis + 1) % 3;
		}
		if (!foundSplit)
		{ // leaf-Node
			nodes[nodeIndex].leftChild = -1;
			nodes[nodeIndex].rightChild = -1;
			nodes[nodeIndex].triangleIndex = triangleIndex;
			nodes[nodeIndex].numberOfTriangles = numberOfTriangles;
		}
		else
		{ // inner node
			int freeNode = addedNodes;
			addedNodes += 2;

			nodes[nodeIndex].leftChild = freeNode;
			nodes[nodeIndex].rightChild = freeNode + 1; // right = left+1 ... could be optimized

			buildBVH(freeNode, triangleIndex, split, leftBox, depth + 1); // recursively call buildBVH for left and right sub-tree
			buildBVH(freeNode + 1, triangleIndex + split, numberOfTriangles - split, rightBox,
					depth + 1);
		}
	}
}

int BVH::sortTris(int triangleIndex, int numberOfTriangles, float plane, int axis, AABB &leftBox, AABB &rightBox)
{
	int left = 0;
	int right = numberOfTriangles - 1;

	while (left <= right)
	{ // with unsigned int this wont work! Modify this if you have more than 2^31 triangles
		AABB triangleBox;
		triangles[indices[triangleIndex + left]].getAABB(triangleBox);
		const float tri_mid = (triangleBox.bounds[0][axis] + triangleBox.bounds[1][axis])
				* 0.5f;

		if (plane > tri_mid)
		{ // triangle is left
			left++;
			leftBox.extent(triangleBox);
		}
		else
		{ // triangle is right
			int temp = indices[triangleIndex + left];
			indices[triangleIndex + left] = indices[triangleIndex + right];
			indices[triangleIndex + right] = temp;
			right--;
			rightBox.extent(triangleBox);
		}
	}
	return left;
}

AABB* BVH::getBoundingBox(){
	return &boundingBox;
}

HitRec BVH::intersect(const Ray &ray)
{
	// precompute inverse ray direction for bounding box intersection
	// -> compute only once for bvh travesal
	QVector3D invRayDir(1.0f / ray.direction.x(), 1.0f / ray.direction.y(), 1.0f / ray.direction.z());

	// index array for ray signs (direction of the ray)
	// -> saving costly if-operations during box intersection and traversal
	unsigned int raySign[3][2];
	raySign[0][0] = invRayDir[0] < 0;
	raySign[1][0] = invRayDir[1] < 0;
	raySign[2][0] = invRayDir[2] < 0;

	raySign[0][1] = invRayDir[0] >= 0;
	raySign[1][1] = invRayDir[1] >= 0;
	raySign[2][1] = invRayDir[2] >= 0;

	HitRec rec;
	float tmin = ray.minDistance;
	float tmax = ray.maxDistance;

	if (!nodes->boundingBox.intersect(ray, tmin, tmax, invRayDir, raySign))
		return rec;

	int nodeIndex = 0;
	
	intersectRecursive(nodes[nodeIndex].leftChild, rec, ray, invRayDir, raySign);
	intersectRecursive(nodes[nodeIndex].rightChild, rec, ray, invRayDir, raySign);
	return rec;
}

void BVH::intersectRecursive(int nodeIndex, HitRec &rec, const Ray &ray, QVector3D invRayDir, const unsigned int raySign[3][2]){
	// check if boundingBox is intersected
	float tmin = ray.minDistance;
	float tmax = ray.maxDistance;
	if (!nodes[nodeIndex].boundingBox.intersect(ray, tmin, tmax, invRayDir, raySign))
		return;
	if (nodes[nodeIndex].numberOfTriangles != -1) {
	// in a leaf node, check if triangles are intersected
		for (int i = 0; i < nodes[nodeIndex].numberOfTriangles; i++){
			triangles[indices[nodes[nodeIndex].triangleIndex + i]].intersect(ray, rec, indices[nodes[nodeIndex].triangleIndex + i]);
		}
	}else{
		intersectRecursive(nodes[nodeIndex].leftChild, rec, ray, invRayDir, raySign);
		intersectRecursive(nodes[nodeIndex].rightChild, rec, ray, invRayDir, raySign);
	}
}

BVH::~BVH() {
	delete[] nodes;
	delete[] indices;
	delete[] triangles;
}

