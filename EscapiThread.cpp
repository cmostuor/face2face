#include "EscapiThread.h"

EscapiThread::EscapiThread(){
	cameraFound = false;

	//initialize timer:
	cameraTimer = new QTimer();
	cameraTimer ->setInterval(64);
	QObject::connect(cameraTimer, SIGNAL(timeout()), this, SLOT(captureImage()));
	//start capturing
	cameraTimer -> start();
}


EscapiThread::~EscapiThread(){
	delete cameraTimer;
}

void EscapiThread::run(){
	devices = setupESCAPI();
	if(devices == 0){
		std::cout<<"No webcam found."<<std::endl;
		terminate();
	} else {
		char namebuffer[128];
		getCaptureDeviceName(0, namebuffer, 128);
		std::cout<<"Device name: "<<namebuffer<<std::endl;
		cameraFound = true;
		
	}
	capture.mWidth = 1280;
	capture.mHeight = 720;
	capture.mTargetBuf = new int[1280*720];
	if(initCapture(0, &capture) == 1){
		device = 0;
		std::cout<<"Capture initialized"<<std::endl;
		doCapture(0);
	} else {
		device = -1;
		std::cout<<"Capture couldn't be initialized"<<std::endl;
	}
	
}

void EscapiThread::captureImage(){
	if(cameraFound){
		//capture new Image
		emit gotNewImg(capture.mTargetBuf);
		doCapture(0);
	}
}
