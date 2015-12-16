#ifndef ESCAPITHREAD_H_
#define ESCAPITHREAD_H_

#include <iostream>
#include "qthread.h"
#include "escapi/escapi.h"
#include "ModelViewer5.h"

class EscapiThread : public QThread
{
	Q_OBJECT
private:
	struct SimpleCapParams capture;
	int device, devices;
	QTimer* cameraTimer; 
	bool cameraFound;

private slots:
	void captureImage();
public:
	EscapiThread();
	~EscapiThread();
	void run();
signals:
	void gotNewImg(int* img);
};

#endif /* ESCAPITHREAD_H_ */

