#include "tuiothread.h"

TUIOThread::TUIOThread()
{

}

TUIOThread::~TUIOThread()
{

}

void TUIOThread::run()
{
	//TUIO Client
	int port = 3333;
	TuioClient client(port);
	client.addTuioListener(&listener);
	client.connect(true);
}