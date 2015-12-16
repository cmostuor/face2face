/*
 * TraversalStack.h
 *
 *  Created on: 24.04.2014
 *      Author: paul
 */

#ifndef TRAVERSALSTACK_H_
#define TRAVERSALSTACK_H_

class TraversalStack {
public:


	int nodeIndex;
	float minDistance;
	TraversalStack();
	TraversalStack(int _nodeIndex, float _minDistance);
	virtual ~TraversalStack();
};

#endif /* TRAVERSALSTACK_H_ */
