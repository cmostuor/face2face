/*
 * AABB.h
 *
 *  Created on: 24.04.2014
 *      Author: paul
 */

#ifndef AABB_H_
#define AABB_H_
#include <QVector3D>
#include "HitRec.h"
#include "Ray.h"
#include <math.h>
#include <cmath>


/*
*Axis Aligned Bounding Box, bounds[0] is the corner with the min. coordinates, bounds [1] is the corner withe the max. coordinates
*/

class AABB {
	
public:
	QVector3D bounds[2];
	AABB();
	AABB(QVector3D minCorner, QVector3D maxCorner);
	//merges boundingBox with current AABB
	void extent(const AABB &boundingBox);
	bool intersect(const Ray &r, float &intervalMin, float &intervalMax,
				const QVector3D &invRayDir, const unsigned int raySign[3][2]);
	int getMaxAxis();
	QVector3D getCenter();

	virtual ~AABB();
};

#endif /* AABB_H_ */
