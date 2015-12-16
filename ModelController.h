#pragma once

#include <iostream>
#include "ModelViewer5.h"
#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include <QT>
#include <qmath.h>

//ArcBall-Rotation:
#include <QTimer>
#include <QVector2D>
#include <QVector3D>
#include <QMouseEvent>

//Keyboard
#include <QKeyEvent>

//TUIO
#include <TuioThread.h>
#include <TuioDump.h>

//Network
#include "Connection.h"

class ModelController : public QObject
	
{
	Q_OBJECT

	ModelManager* modelManager;
	ModelViewer* modelViewer;
	TuioDump* tuioDump;
	MainWindow *mainWindow;

	//network:
	bool localObjectLocked;
	bool remoteObjectLocked;
    Connection connection;
    ModellMessage incommingMessage;
    ModellMessage outgoingMessage;
    
	
	//ArcBall-Rotation:
	QTimer* arcBallTimer;
	bool arcBallOn;
	//saves mouse positions:
	QVector2D startMousePosition;
	QVector2D currentMousePosition;
	
	//Vector of current Multitouch fingers (TUIO)
	QVector<QVector3D>* fingers;
	//Vector of Multitouch fingers after last update event(TUIO)
	QVector<QVector3D>* oldFingers;
	//z-coordinate of movement plane
	float Ztranslate;
	
private:
	QVector3D getArcBallVector(const QVector2D mousePosition);

public:
	ModelController(ModelManager* _modelManager, ModelViewer* _modelViewer, TUIOThread* _tuioThread, MainWindow *mainWindow);
	~ModelController();

public slots:
	//ArcBall
	void computeArcBallRotation();
	void startArcBallRotation(QVector2D mousePosition);
	void updateArcBallRotation(QVector2D mousePosition);
	void stopArcBallRotation();
	//Tuio
	void processTuioAddEvent(QVector3D newFinger);
	void processTuioMoveEvent(QVector3D updatedFinger);
	void processTuioDeleteEvent(int id);
	void processTuioTransform();
	//keyboard events
	void keyPressed(QKeyEvent* event);
	//model manipulation
	void receiveMessage(ModellMessage _incomingMessage);
	void changeModel(int modelNumber);

signals:
	void updateView();
	//sends ping to establish connection
	void sendPing();
    //send Message to other Viewer
    void sendMessage(ModellMessage _modelMessage);
};

