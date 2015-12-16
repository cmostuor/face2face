#ifndef OPENCVTHREAD_H_
#define OPENCVTHREAD_H_

#include <iostream>
#include "qthread.h"
#include "ModelViewer5.h"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"

class OpenCvThread : public QThread
{
	Q_OBJECT
private:
	cv::VideoCapture *webcam;
	cv::Mat frame;
	QTimer* cameraTimer; 
	bool cameraFound;

private slots:
	void captureImage();
public:
	OpenCvThread();
	~OpenCvThread();
	void run();
signals:
	void gotNewImg(cv::Mat img);
};

#endif /* OPENCVTHREAD_H_ */

