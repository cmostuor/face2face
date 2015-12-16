/*
 * Ray.cpp
 *
 *  Created on: 24.04.2014
 *      Author: paul
 */

#include "Ray.h"

Ray::Ray(QVector3D &_origin, QVector3D &_direction, float _minDistance, float _maxDistance) {
	origin=_origin;
	direction=_direction;
	minDistance=_minDistance;
	maxDistance=_maxDistance;

}

Ray::Ray(const QVector3D _origin, const QVector3D _direction, float _minDistance, float _maxDistance) {
    origin=_origin;
    direction=_direction;
    minDistance=_minDistance;
    maxDistance=_maxDistance;

}

Ray::~Ray() {
	// TODO Auto-generated destructor stub
}

