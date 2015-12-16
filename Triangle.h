/*
 * Triangle.h
 *
 *  Created on: 24.04.2014
 *      Author: paul
 */

#ifndef TRIANGLE_H_
#define TRIANGLE_H_
#include <QVector3D>
#include <QVector2D>
#include <QMatrix4x4>

#include "Ray.h"
#include "HitRec.h"
#include "AABB.h"

class Triangle {
public:
	QVector3D corners[3];
	Triangle();
	Triangle(QVector3D a, QVector3D b, QVector3D c);
	//creates a Triangle out of 9 floats out of a float array beginning at position
	Triangle(float* data, unsigned int position);
	virtual ~Triangle();

	void getExtents(const int axis, float &xmin, float &xmax);
	//returns axis aligned boundingbox over current an array of Triangles
	void getAABB(const Triangle* triangles, unsigned int numberTriangles, AABB &boundingBox);
	//returns axis aligned boundingbox over current Triangle
	void getAABB(AABB &bbox);
	bool intersect(const Ray &ray, HitRec &rec, const int tri_id);

};

#endif /* TRIANGLE_H_ */
