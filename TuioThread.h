//Thread for TUIO Listener
//Without new Thread the TUIO Client blocks entire thread

#ifndef TUIOTHREAD_H
#define TUIOTHREAD_H

#include <QThread>
#include "TuioDump.h"
#include "TUIO/TuioClient.h"

class TUIOThread : public QThread
{
	Q_OBJECT

public:
	TUIOThread();
	~TUIOThread();
	TuioDump listener;

 protected:
     void run();


private:
	
};

#endif // TUIOTHREAD_H
