
#include <iostream>
#include "string.h"

#include <QtWidgets/QApplication>
#include <QTimer>
#include <QFile>
#include <qmessagebox.h>

#include "ModelManager.h"
#include "ModelViewer5.h"
#include "ModelController.h"

#include "tuiothread.h"
#include "OpenCvThread.h"
//#include "EscapiThread.h"

#include "qlabel.h"
#include "qgridlayout.h"

#include "MainWindow.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	
	//initialize ModelManager	
	ModelManager* modelManager = new ModelManager();
	bool ModelsUnavailable = true;

	//Open File for input 
	try {
		QFile file("models.txt");
		if(file.open(QIODevice::ReadOnly))
		{
			QTextStream in(&file);
			while(!in.atEnd())
			{
				modelManager->loadScene(in.readLine().toLatin1().data());
				ModelsUnavailable = false;
			}
		}
		file.close();
	}catch(int x){
	   ModelsUnavailable = true;
	   cout<<"catch" << endl;
   }
   
	if(!ModelsUnavailable){

		//setup Mainwindow containing openGL view & sidebar
		MainWindow *mainWindow = new MainWindow();
		mainWindow->resize(640,360);

		//intialize ModelViewer
		QGLFormat gl_format;
		gl_format.setVersion(2,1);
		ModelViewer* modelViewer = new ModelViewer(gl_format,mainWindow);
		modelViewer->setModelManager(modelManager);
		modelViewer->setGeometry(0,0,640,360);
		QWidget *sideMenu = new QWidget(mainWindow);
		int modelCount = modelManager->getNumberOfModels();
		int height = (modelCount*50);
		sideMenu->setGeometry(QRect((mainWindow->width()-50),0,50,height));
		QGridLayout *gridLayout = new QGridLayout(mainWindow);
		gridLayout->setSpacing(0);
		gridLayout->setMargin(0);
		gridLayout->setVerticalSpacing(1);


		for (int i = 0; i < modelCount;i++)
		{
			QLabel *sideMenuItem = new QLabel(QString::number(i+1));
			sideMenuItem->setStyleSheet("background-color : rgba(100,100,100,100); color: white; border: 2px solid white; border-radius: 10px;");
			QFont f( "Arial", 20, QFont::Bold);
			sideMenuItem->setFont(f);
			sideMenuItem->setAlignment(Qt::AlignCenter);
			gridLayout->addWidget(sideMenuItem,i,0);
		}
		sideMenu->setLayout(gridLayout);
	
		mainWindow->setChilds(modelViewer, sideMenu);

		mainWindow->show();

	

		//initialize new Thread for TUIO integration
		TUIOThread* tuioListener = new TUIOThread();
		tuioListener->start();

		//initialize new thread for webcam integration
		//EscapiThread* webcam = new EscapiThread();
		//webcam->start();

		//initialize new thread for webcam integration
		OpenCvThread* webcam = new OpenCvThread();
		webcam->start();

		//connect the webcam to the viewer which receives a new webcam image as soon as it's available
		QObject::connect(webcam, SIGNAL(gotNewImg(cv::Mat)), modelViewer, SLOT(changeCamImg(cv::Mat)));
	
		//initialize ModelController
		ModelController modelController(modelManager, modelViewer, tuioListener, mainWindow);

		return a.exec();

		//delete threads
		delete tuioListener;
		delete webcam;
		//delete Objects:
		delete modelViewer;
		delete modelManager;
	}else{
		QMessageBox msgBox;
		msgBox.setWindowTitle("Fehler");
		msgBox.setText("Modellliste nicht gefunden. Prgramm wird beendet.");
		msgBox.exec();
		return a.exec();
	}

	
}
