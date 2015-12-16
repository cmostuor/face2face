/*
 * AABB.cpp
 *
 *  Created on: 24.04.2014
 *      Author: paul
 */

#include "AABB.h"
#include <math.h>

//returns min Values of 2 Vectors
QVector3D minf(QVector3D &u, const QVector3D &v)
{
	u.setX(u.x() < v.x() ? u.x() : v.x());
	u.setY(u.y() < v.y() ? u.y() : v.y());
	u.setZ(u.z() < v.z() ? u.z() : v.z());
	return u;
}

//returns max Values of 2 Vectors
QVector3D maxf(QVector3D &u, const QVector3D &v)
{
	u.setX(u.x() > v.x() ? u.x() : v.x());
	u.setY(u.y() > v.y() ? u.y() : v.y());
	u.setZ(u.z() > v.z() ? u.z() : v.z());
	return u;
}

 // returns the max Values of x,y,z from a Vector
int maxIndex(QVector3D &u)
{
	if (u.x() > u.y())
	{
		if (u.x() > u.z())
			return 0;
		else
			return 2;
	}
	else if (u.z() > u.y())
		return 2;
	else
		return 1;
}

AABB::AABB() {
	bounds[0]=QVector3D(FLT_MAX,FLT_MAX,FLT_MAX);
	bounds[1]=QVector3D(-FLT_MAX,-FLT_MAX,-FLT_MAX);
}

AABB::AABB(QVector3D minCorner, QVector3D maxCorner){
	bounds[0]=minCorner;
	bounds[1]=maxCorner;
}

void AABB::extent(const AABB &boundingBox){
	bounds[0]=minf(bounds[0],boundingBox.bounds[0]);
	bounds[1]=maxf(bounds[1],boundingBox.bounds[1]);
}

bool AABB::intersect(const Ray &r, float &intervalMin, float &intervalMax, const QVector3D &invRayDir, const unsigned int raySign[3][2])
{
	const float xMin = (bounds[raySign[0][0]][0] - r.origin[0])
			* invRayDir[0];
	const float xMax = (bounds[raySign[0][1]][0] - r.origin[0])
			* invRayDir[0];

	const float yMin = (bounds[raySign[1][0]][1] - r.origin[1])
			* invRayDir[1];
	const float yMax = (bounds[raySign[1][1]][1] - r.origin[1])
			* invRayDir[1];

	const float zMin = (bounds[raySign[2][0]][2] - r.origin[2])
			* invRayDir[2];
	const float zMax = (bounds[raySign[2][1]][2] - r.origin[2])
			* invRayDir[2];

	intervalMin = std::max(intervalMin, xMin);
	intervalMin = std::max(intervalMin, yMin);
	intervalMin = std::max(intervalMin, zMin);
	
	intervalMax = std::min(intervalMax, xMax);
	intervalMax = std::min(intervalMax, yMax);
	intervalMax = std::min(intervalMax, zMax);

	return (intervalMin <= intervalMax);
}

int AABB::getMaxAxis()
{
	QVector3D ex = bounds[1] - bounds[0];
	return maxIndex(ex);
}

QVector3D AABB::getCenter()
{
	return (bounds[1] + bounds[0]) * 0.5f;
}



AABB::~AABB() {
	// TODO Auto-generated destructor stub
}


