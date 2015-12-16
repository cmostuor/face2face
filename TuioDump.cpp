/*
	TUIO C++ Example - part of the reacTIVision project
	http://reactivision.sourceforge.net/

	Copyright (c) 2005-2009 Martin Kaltenbrunner <mkalten@iua.upf.edu>

	Permission is hereby granted, free of charge, to any person obtaining
	a copy of this software and associated documentation files
	(the "Software"), to deal in the Software without restriction,
	including without limitation the rights to use, copy, modify, merge,
	publish, distribute, sublicense, and/or sell copies of the Software,
	and to permit persons to whom the Software is furnished to do so,
	subject to the following conditions:

	The above copyright notice and this permission notice shall be
	included in all copies or substantial portions of the Software.

	Any person wishing to distribute modifications to the Software is
	requested to send the modifications to the original developer so that
	they can be incorporated into the canonical version.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
	MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
	IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR
	ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
	CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
	WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "TuioDump.h"
		
void TuioDump::addTuioObject(TuioObject *tobj) {
}

void TuioDump::updateTuioObject(TuioObject *tobj) {
}

void TuioDump::removeTuioObject(TuioObject *tobj) {
}

void TuioDump::addTuioCursor(TuioCursor *tcur) {
	//std::cout << "add cur " << tcur->getCursorID() << " (" <<  tcur->getSessionID() << ") " << tcur->getX() << " " << tcur->getY() << std::endl;

	//create vector with id and position
	QVector3D cursorPosition = QVector3D(tcur->getCursorID(), tcur->getX(), tcur->getY());
	//emit the vector (to controller)
	emit tuioCursorCreated(cursorPosition);
}

void TuioDump::updateTuioCursor(TuioCursor *tcur) {
	//std::cout << "set cur " << tcur->getCursorID() << " (" <<  tcur->getSessionID() << ") " << tcur->getX() << " " << tcur->getY() 
	//			<< " " << tcur->getMotionSpeed() << " " << tcur->getMotionAccel() << " " << std::endl;
	
	//create vector with id and position
	QVector3D cursorPosition = QVector3D(tcur->getCursorID(), tcur->getX(), tcur->getY());
	//emit the vector (to controller)
	emit tuioCursorMoved(cursorPosition);
}

void TuioDump::removeTuioCursor(TuioCursor *tcur) {
	//std::cout << "del cur " << tcur->getCursorID() << " (" <<  tcur->getSessionID() << ")" << std::endl;
	
	//emit removal of cursor with id of cursor
	emit tuioCursorReleased(tcur->getCursorID());
}

void  TuioDump::refresh(TuioTime frameTime) {
	//std::cout << "refresh " << frameTime.getTotalMilliseconds() << std::endl;
}


