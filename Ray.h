/*
 * Ray.h
 *
 *  Created on: 24.04.2014
 *      Author: paul
 */

#ifndef RAY_H_
#define RAY_H_
#include <QVector3D>

//Ray used for BVH traversal and Triangle intersection

class Ray {
public:
	QVector3D origin;
	QVector3D direction;
	//possible intersections closer than minDistance are ignored
	float minDistance;
	//possible intersections further than maxDistance are ignored
	float maxDistance;
	Ray(QVector3D &_origin, QVector3D &_direction, float _minDistance, float _maxDistance);
    Ray(const QVector3D _origin, const QVector3D _direction, float _minDistance, float _maxDistance);
	virtual ~Ray();
};

#endif /* RAY_H_ */
