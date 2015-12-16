/*
 * Triangle.cpp
 *
 *  Created on: 24.04.2014
 *      Author: paul
 */

#include "Triangle.h"
#include <cmath>



Triangle::Triangle(){
	corners[0]=QVector3D();
	corners[1]=QVector3D();
	corners[2]=QVector3D();
}

Triangle::Triangle (QVector3D a, QVector3D b, QVector3D c) {
	corners[0]=a;
	corners[1]=b;
	corners[2]=c;

}

Triangle::Triangle(float* data, unsigned int position){
	for (int i = 0;  i < 9; i+=3) {
		for (int j = 0; j < 3; j++) {
			corners[i][j]=data[position+i+j];
		}

	}
}


void Triangle::getExtents(const int axis, float &xmin, float &xmax){
	xmin = std::min(corners[0][axis], corners[1][axis]);
	xmax = std::max(corners[0][axis], corners[1][axis]);
	xmin = std::min(xmin, corners[2][axis]);
	xmax = std::max(xmax, corners[2][axis]);
}

void Triangle::getAABB(AABB &bbox){
	for (int axis = 0; axis < 3; axis++)
	{
		getExtents(axis, bbox.bounds[0][axis], bbox.bounds[1][axis]);
	}
}

void Triangle::getAABB(const Triangle* triangles, unsigned int numberTriangles, AABB &boundingBox){
	for (int currentTriangle = 0; currentTriangle < numberTriangles; currentTriangle++) {
		for (int i = 0; i < 3; i++) {
			boundingBox.bounds[0][i]=std::min(boundingBox.bounds[0][i], triangles[currentTriangle].corners[0][i]);
			boundingBox.bounds[1][i]=std::max(boundingBox.bounds[1][i], triangles[currentTriangle].corners[0][i]);
			boundingBox.bounds[0][i]=std::min(boundingBox.bounds[0][i], triangles[currentTriangle].corners[1][i]);
			boundingBox.bounds[1][i]=std::max(boundingBox.bounds[1][i], triangles[currentTriangle].corners[1][i]);
			boundingBox.bounds[0][i]=std::min(boundingBox.bounds[0][i], triangles[currentTriangle].corners[2][i]);
			boundingBox.bounds[1][i]=std::max(boundingBox.bounds[1][i], triangles[currentTriangle].corners[2][i]);
		}
	}
}

bool Triangle::intersect(const Ray &ray, HitRec &rec, const int tri_id){
	// plane normal
	QVector3D normal = (QVector3D::crossProduct(corners[1]-corners[0], corners[2]-corners[0])).normalized();
	
	// shortest distance from plane to ray origin
	float distance = QVector3D::dotProduct(- corners[0], normal);
	float t = - (QVector3D::dotProduct(ray.origin, normal) + distance) / QVector3D::dotProduct(ray.direction, normal);
	if(t <= 0)
		return false;
	if(rec.distance < t)
		return false;
	QVector3D hitPoint = ray.origin + t * ray.direction;

	QVector3D v0 = corners[1] - corners[0]; 
	QVector3D v1 = corners[2] - corners[0];
	QVector3D v2 = hitPoint - corners[0];
    float d00 = QVector3D::dotProduct(v0, v0);
    float d01 = QVector3D::dotProduct(v0, v1);
    float d11 = QVector3D::dotProduct(v1, v1);
    float d20 = QVector3D::dotProduct(v2, v0);
    float d21 = QVector3D::dotProduct(v2, v1);
    float denom = d00 * d11 - d01 * d01;
    float alpha = (d11 * d20 - d01 * d21) / denom;
	if(alpha < 0.f || alpha > 1.f) 
		return false;
    float beta = (d00 * d21 - d01 * d20) / denom;
	if(beta < 0.f || alpha + beta > 1.f) 
		return false;
	rec.distance = t;
	rec.id = tri_id;
	return true;
}

Triangle::~Triangle() {
	// TODO Auto-generated destructor stub
}


