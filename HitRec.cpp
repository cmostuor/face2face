/*
 * HitRec.cpp
 *
 *  Created on: 24.04.2014
 *      Author: paul
 */

#include "HitRec.h"

HitRec::HitRec(){
	distance = FLT_MAX;
	id=-1;
}

HitRec::HitRec(float _distance, int _id) {
	distance =_distance;
	id=_id;

}

HitRec::~HitRec() {
	// TODO Auto-generated destructor stub
}

