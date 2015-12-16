/*
 * TraversalStack.cpp
 *
 *  Created on: 24.04.2014
 *      Author: paul
 */

#include "TraversalStack.h"

TraversalStack::TraversalStack(){

}
TraversalStack::TraversalStack(int _nodeIndex, float _minDistance) {
	nodeIndex=_nodeIndex;
	minDistance=_minDistance;

}

TraversalStack::~TraversalStack() {
	// TODO Auto-generated destructor stub
}

