/*
 * HitRec.h
 *
 *  Created on: 24.04.2014
 *      Author: paul
 */

#ifndef HITREC_H_
#define HITREC_H_

//Hit Record, contains the hitpoint and the id of the Triangle that was hit
#include <float.h>
#include <qvector3d.h>

class HitRec {
public:
	float distance;
	int id;
	HitRec();
	HitRec(float _distance, int _id);
	virtual ~HitRec();
};

#endif /* HITREC_H_ */
