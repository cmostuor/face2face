#include "TriangleManager.h"

TriangleManager::TriangleManager(Triangle* _triangles, unsigned int _numberOfTriangles) : triangles(_triangles), numberOfTriangles(_numberOfTriangles)
{
}

TriangleManager::~TriangleManager(void)
{
}

HitRec* TriangleManager::intersect(QVector2D coords, QMatrix4x4 transform) const
{
	//iterate over all triangles to find the frontmost intersection with user touch/click
	HitRec* rec = new HitRec();
	for( int idx = 0; idx < numberOfTriangles; idx++){
		triangles[idx].intersectRasterized(coords, transform, *rec, idx);
	}
	return rec;
}