#include "OpenCvThread.h"

OpenCvThread::OpenCvThread(){
	cameraFound = false;
	frame = cv::Mat::zeros( 720, 1280, CV_8UC3 );
	//initialize timer:
	cameraTimer = new QTimer();
	cameraTimer ->setInterval(64);
	QObject::connect(cameraTimer, SIGNAL(timeout()), this, SLOT(captureImage()));
	//start capturing
	cameraTimer -> start();
}


OpenCvThread::~OpenCvThread(){
	delete cameraTimer;
	delete webcam;
}

void OpenCvThread::run(){
    webcam = new cv::VideoCapture();
    webcam->open(0);
	if(!webcam->isOpened()){
		std::cout<<"OpenCV: No webcam found."<<std::endl;
		terminate();
	} else {
		std::cout<< "OpenCV: Webcam found." <<std::endl;
		cameraFound = true;
		webcam->set(CV_CAP_PROP_FRAME_WIDTH,1280);

		webcam->set(CV_CAP_PROP_FRAME_HEIGHT,720);
        if(webcam->isOpened()){
            webcam->read(frame);
    }
        std::cout<<"done setup"<<std::endl;
    }
}

void OpenCvThread::captureImage(){
	if(cameraFound){
		//capture new Image
        if(webcam->isOpened() && webcam->read(frame))
		{
			emit gotNewImg(frame);
		}
	}
}
