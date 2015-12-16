#include "ModelController.h"


ModelController::ModelController(ModelManager* _modelManager, ModelViewer* _modelViewer, TUIOThread* _tuioThread, MainWindow* _mainWindow)
{
	//initialise Vars
	arcBallOn = false;
	startMousePosition = QVector2D(0,0);
	currentMousePosition = QVector2D(0,0);

	//connect to ModelManager
	modelManager = _modelManager;

	//connect to ModelViewer
	modelViewer = _modelViewer;

	//connect to TuioListener
	tuioDump = &_tuioThread->listener;

	//connect to mainWindow
	mainWindow = _mainWindow;


	//initializing Touchscreen Vectos for Vectors
	fingers = new QVector<QVector3D>(0);
	oldFingers = new QVector<QVector3D>(0);

	//initialise arcBallTimer (~60fps)
	arcBallTimer = new QTimer();
	arcBallTimer->setInterval(16);

	//initialise TUIOTimer (~60fps)
	QTimer* TUIOTimer = new QTimer();
	TUIOTimer->setInterval(16);
	TUIOTimer->start();

	//connect timers to computeArcBall() and processTuioTransform() method
	QObject::connect(arcBallTimer, SIGNAL(timeout()), this, SLOT(computeArcBallRotation()));
	QObject::connect(TUIOTimer, SIGNAL(timeout()), this, SLOT(processTuioTransform()));

	//connect mouse events to ArcBall methods
	QObject::connect(modelViewer, SIGNAL(mousePressed(QVector2D)), this, SLOT(startArcBallRotation(QVector2D)));
	QObject::connect(modelViewer, SIGNAL(mouseMoved(QVector2D)), this, SLOT(updateArcBallRotation(QVector2D)));
	QObject::connect(modelViewer, SIGNAL(mouseReleased()), this, SLOT(stopArcBallRotation()));

	//connect tuio events to methods
	 QObject::connect(tuioDump, SIGNAL(tuioCursorCreated(QVector3D)), this, SLOT(processTuioAddEvent(QVector3D)));
	 QObject::connect(tuioDump, SIGNAL(tuioCursorMoved(QVector3D)), this, SLOT(processTuioMoveEvent(QVector3D)));
	 QObject::connect(tuioDump, SIGNAL(tuioCursorReleased(int)), this, SLOT(processTuioDeleteEvent(int)));

	//connect keyboard to modelController
	QObject::connect(mainWindow, SIGNAL(keyPressed(QKeyEvent*)), this, SLOT(keyPressed(QKeyEvent*)));

	//connect activeModel and ModelController to View:
	QObject::connect(this, SIGNAL(updateView()), modelViewer, SLOT(updateGeometry()));
	QObject::connect(modelManager->getActiveModel(), SIGNAL(updateView()), modelViewer, SLOT(updateGeometry()));

	//connect 'C' to sendPing() in Connection:
	QObject::connect(this, SIGNAL(sendPing()), &connection, SLOT(sendPing()));
	//tcp
	QObject::connect(this,SIGNAL(sendMessage(ModellMessage)),&connection,SLOT(sendMessage(ModellMessage)));
	QObject::connect(&connection,SIGNAL(receivedMessage(ModellMessage)),this,SLOT(receiveMessage(ModellMessage)));

	//connect SideMenu signal to Model Changer
	QObject::connect(mainWindow, SIGNAL(modelChange(int)), this, SLOT(changeModel(int)));

	//unlock Viewer:
	localObjectLocked = false;
	remoteObjectLocked = true;

}

void ModelController::startArcBallRotation(QVector2D mousePosition){
	//break if model is locked
	if(localObjectLocked) return;
	//create lock Message:
	outgoingMessage.type = 0;
	emit sendMessage(outgoingMessage);

	QVector3D vec3;
	//check if you hit the model to start ArcBall rotation
	if(modelManager->getActiveModel()->intersect(*(modelViewer->getCamera()), mousePosition.x(), mousePosition.y(), vec3)){
		//save mouse position
		startMousePosition = currentMousePosition = mousePosition;

		//start arcBallTimer and activate arcBallRotation
		arcBallOn = true;
		arcBallTimer->start();
	}
}

void ModelController::updateArcBallRotation(QVector2D mousePosition)
{
	QVector3D vec3;
    //check if ArcBall rotation is on
    if(arcBallOn){
		//update mouse position
		currentMousePosition = mousePosition;
	}else{
		//stop ArcBall rotation
		arcBallOn = false;
		arcBallTimer->stop();
	}
}

void ModelController::stopArcBallRotation()
{
	//stop ArcBall rotation
	arcBallOn = false;
	arcBallTimer->stop();
	//create lock Message:
	outgoingMessage.type = 1;
	emit sendMessage(outgoingMessage);
}

void ModelController::processTuioAddEvent(QVector3D newFinger)
{
	//handle side bar events
	if(fingers->size() == 0)
	{
		//the only finger on screen is the new one
		int pixelHPosition = newFinger.y()*modelViewer->width();
		int sideMenuLeftBorder = modelViewer->width()-50;
		if(pixelHPosition >= sideMenuLeftBorder)
		{
			//inside Menu Bar
			int pixelVPosition = newFinger.z()*modelViewer->width();
			int modelNumber = pixelVPosition / 50;
			if(modelNumber < modelManager->getNumberOfModels())
			{
				//model exists

				changeModel(modelNumber);
				
				//this fingers is ignored for everything else 
				return;
			}
		}
	}

	//check if finger hit the model
    QVector3D point=QVector3D();
    if(!modelManager->getActiveModel()->intersect(*(modelViewer->getCamera()), newFinger.y(), newFinger.z(), point)) return;
	//create lock Message:
	outgoingMessage.type = 0;
	emit sendMessage(outgoingMessage);

	fingers->append(newFinger);
	//if only one finger is one the screen, start arcball
	if(fingers->size() <= 1)
	{
		QVector2D mousePosition(newFinger.y(),newFinger.z()); 
		startArcBallRotation(mousePosition);
	}else if(fingers->size() > 1){
		stopArcBallRotation();
		//create lock Message:
		outgoingMessage.type = 0;
		emit sendMessage(outgoingMessage);
	}
}

void ModelController::processTuioMoveEvent(QVector3D updatedFinger)
{
	//if only one finger is on screen, pipe to arcball
	if(fingers->size() == 1)
	{
		QVector2D mousePosition(updatedFinger.y(),updatedFinger.z()); 
		updateArcBallRotation(mousePosition);
	}
	//always search for finger with id in fingers vector and update Position
	for(int i = 0; i < fingers->size(); i++)
	{
		if(fingers->at(i).x() == updatedFinger.x())
		{
			fingers->replace(i,updatedFinger);
			break;
		}
	}
}

void ModelController::processTuioDeleteEvent(int id)
{
	//search for finger with id in fingers vector
	for(int i = 0; i < fingers->size(); i++)
	{
		if(fingers->at(i).x() == id)
		{
			fingers->remove(i);
			break;
		}
	}
	//if only one finger remains, start arcball
	if(fingers->size() == 1)
	{
		QVector2D mousePosition(fingers->at(0).y(),fingers->at(0).z()); 
		startArcBallRotation(mousePosition);
	}
	//if no finger remains, stop arcball if active
	else if(fingers->size() == 0)
	{
		if(arcBallOn)
		{
			stopArcBallRotation();
			//create lock Message:
			outgoingMessage.type = 1;
			emit sendMessage(outgoingMessage);
		}
	}
	//more than one finger remains
	else
	{
		//restart TUIO events by checking intersection for all remaining fingers
		for(int i = 0; i < fingers->size(); i++)
		{
            QVector3D point= QVector3D();
            if(!modelManager->getActiveModel()->intersect(*(modelViewer->getCamera()),fingers->at(i).y(), fingers->at(i).z(),point))
			{
				//if finger does not intersect, throw it away recursively
				processTuioDeleteEvent(fingers->at(i).x());
				//dump old Fingers Vector
				oldFingers = new QVector<QVector3D>(*fingers);
				break;
			}
		}
	}
}


//keyboard events
void ModelController::keyPressed(QKeyEvent* event)
{
	//pressed Key is a number
	if((event->key() < 58) && (event->key() > 48))
	{
		changeModel(event->key()-49);
	}else if(event->key() == 67){
		cout << "Send Ping" << endl;
		//sends ping to establish connection
		emit sendPing();
	}else if(event->key() == 82){
		//reset Model:
		modelManager->getActiveModel()->resetModel();
		cout<<"Model wurde zurückgesetzt" <<endl;
		//notify other viewer:
		outgoingMessage.type = 5;
		outgoingMessage.modelMatrix = *modelManager->getActiveModel()->getModelMatrix();
		emit sendMessage(outgoingMessage);
	}else if (event->key() == 70){
		//set window to fullscreen or not
		const QSize oldSize = QSize(mainWindow->width(), mainWindow->height());
		mainWindow->setWindowState(mainWindow->windowState() ^ Qt::WindowFullScreen);
	}
}


ModelController::~ModelController(void)
{
	delete arcBallTimer;
	delete fingers;
	delete oldFingers;

}

QVector3D ModelController::getArcBallVector(const QVector2D mousePosition)
{
	//get x- and y-coos in x,y in [-1,1]:
	float x = mousePosition.x()*2 -1;
	float y = mousePosition.y()*2 -1;

	//get ArcBall radius:
	float radius = 0.5*(*modelManager->getActiveModel()->getModelMatrix()*modelManager->getActiveModel()->getBoundingBoxDiagonal()).length();

	//convert window coos to normalized device coos (f(x)= (2/length)x -1)
	//invert y-coord (QT vs. OpenGL)
	QVector3D arcBallVector = QVector3D(x, -y, 0) ;

	//compute z-coordinate (z=sqrt(r-(x^2+y^2)))
	float middleToSurface = arcBallVector.x()*arcBallVector.x()*arcBallVector.y()*arcBallVector.y();

	//if xxyy > 1 normalize the vector:
	if (middleToSurface > radius)
	{
		arcBallVector.normalize();
		arcBallVector *= radius;
	}else{
		arcBallVector.setZ(sqrt(radius-middleToSurface));
	}
	return arcBallVector;
}

void ModelController::computeArcBallRotation(){

	//stop arcBallTimer if not needed
	if(!arcBallOn){
		arcBallTimer->stop();
		return;
	}
	//check if mouse has been moved
	if(startMousePosition != currentMousePosition){
		QVector3D startVector;
		QVector3D newVector;
	
		//get ArcBallVectors:
		startVector= getArcBallVector(startMousePosition);
		newVector= getArcBallVector(currentMousePosition);

		//compute angle between the 2 Vectors (alpha = cos^(-1)*(v_1 * v_2)/(|v_1| * |v_2|))
		float angle = acos(QVector3D::dotProduct(newVector, startVector)/(startVector.length()*newVector.length()));
		
		//QVector2D to QVector3D on Screen:
		QVector3D mouseMovementVector = QVector3D((-currentMousePosition.x() +startMousePosition.x()) * modelViewer->width(),
			(currentMousePosition.y() - startMousePosition.y())* modelViewer->height(), 0);
		//compute rotation axis:
		QVector3D rotationAxis = QVector3D::crossProduct( mouseMovementVector, QVector3D(0.0f, 0.0f ,modelViewer->getCamera()->getEyeNearPlane()));
		
		//convert rotationAxis
		rotationAxis = (modelViewer->getCamera()->getViewMatrix() * (*modelManager->getActiveModel()->getModelMatrix())).inverted() * rotationAxis;
		
		//break if remote model isn't locked
		if(!remoteObjectLocked) return;

		//else rotate the Model:
        modelManager->getActiveModel()->rotate(100*angle,  rotationAxis);
		
		//create Message:
		outgoingMessage.type = 5;
		outgoingMessage.modelMatrix = *modelManager->getActiveModel()->getModelMatrix();
		emit sendMessage(outgoingMessage);
		

		//reset Positions:
		startMousePosition = currentMousePosition;		
	}
}

void ModelController::processTuioTransform()
{
	//break if remote model isn't locked
	if(!remoteObjectLocked) return;

	//special case for first run (no previous position exists)
	if((oldFingers->size() < 2 )||(fingers->size() < 2))
	{
		oldFingers = new QVector<QVector3D>(*fingers);
	}
	else
	{
		//get ids of 2 first fingers
		int id1 = fingers->at(0).x();
		int id2 = fingers->at(1).x();

		//get new positions of fingers 1 & 2
		const QVector2D p1New(fingers->at(0).y(), fingers->at(0).z());
		const QVector2D p2New(fingers->at(1).y(), fingers->at(1).z());
		
		//get old Positions of fingers 1 & 2
		QVector2D p1Old;
		QVector2D p2Old;
		
		if(oldFingers->at(0).x() == id1 && oldFingers->at(1).x() == id2) {
			p1Old = QVector2D(oldFingers->at(0).y(), oldFingers->at(0).z());
			p2Old = QVector2D(oldFingers->at(1).y(), oldFingers->at(1).z());
		} else {
			for(int i = 2; i < oldFingers->size(); i++)
			{
				bool found1 = false;
				if(oldFingers->at(i).x() == id1)
				{
					p1Old = QVector2D(oldFingers->at(i).y(), oldFingers->at(i).z());
					found1 = true;
				}
				else if(oldFingers->at(i).x() == id2)
				{
					p2Old = QVector2D(oldFingers->at(i).y(), oldFingers->at(i).z());
					if(found1) break;
					found1 = true;
				}
			}
			QVector3D hitPoint, hitPoint2;
			modelManager->getActiveModel()->intersect(*(modelViewer->getCamera()), p1Old.x(), p1Old.y(), hitPoint);
			modelManager->getActiveModel()->intersect(*(modelViewer->getCamera()), p2Old.x(), p2Old.y(), hitPoint2);
			Ztranslate = (modelViewer->getCamera()->getProjMatrix() * modelViewer->getCamera()->getViewMatrix() * ((hitPoint + hitPoint2) / 2.f)).z();
		}
		if(p1Old == p1New && p2Old == p2New)
			return;
		//set new fingerPosition to old (for next calculation)
		oldFingers = new QVector<QVector3D>(*fingers);

		//Calculate Scaling
		float distNew = sqrt((p2New.x()-p1New.x())*(p2New.x()-p1New.x())+(p2New.y()-p1New.y())*(p2New.y()-p1New.y()));
		float distOld = sqrt((p2Old.x()-p1Old.x())*(p2Old.x()-p1Old.x())+(p2Old.y()-p1Old.y())*(p2Old.y()-p1Old.y()));
        

		//CalculateTranslation
		//Calculate Middle of both pairs
		QVector3D old1(p1Old.x() *2.f-1.f, 1.f-2.f*p1Old.y(),Ztranslate);
		QVector3D old2(p2Old.x() *2.f-1.f, 1.f-2.f*p2Old.y(),Ztranslate);
		QVector3D new1(p1New.x() *2.f-1.f, 1.f-2.f*p1New.y(),Ztranslate);
		QVector3D new2(p2New.x() *2.f-1.f, 1.f-2.f*p2New.y(),Ztranslate);

		QMatrix4x4 transformToModelSpace = (modelViewer->getCamera()->getProjMatrix() * modelViewer->getCamera()->getViewMatrix() * (*modelManager->getActiveModel()->getModelMatrix())).inverted();
		QVector3D midOld = (transformToModelSpace * old1 + transformToModelSpace * old2) / 2.f;
		QVector3D midNew = (transformToModelSpace * new1 + transformToModelSpace * new2) / 2.f;

		QVector3D translation = midNew - midOld;
		//Calculate & set Rotation
		QVector2D pitchNew = (p2New - p1New).normalized();
		QVector2D pitchOld = (p2Old - p1Old).normalized();
		//get angle
		float angle = 0.0f;
		if ((pitchNew.length() * pitchOld.length()) > 0.0f) {
			angle = qAcos(QVector2D::dotProduct(pitchNew, pitchOld) / (pitchNew.length() * pitchOld.length()))* 180.0f/3.14159265359f;
		}
		//rotation axis is z in view space
		QVector4D rotationAxis = QVector3D::crossProduct(pitchNew.toVector3D(), pitchOld.toVector3D()).toVector4D();
		rotationAxis = (modelViewer->getCamera()->getProjMatrix() * modelViewer->getCamera()->getViewMatrix() * (*modelManager->getActiveModel()->getModelMatrix())).inverted() * rotationAxis;

		//else execute Scaling, Translation and Rotation
		if(distOld != 0.f) modelManager->getActiveModel()->scale(distNew/distOld);
		modelManager->getActiveModel()->translate(translation);
		modelManager->getActiveModel()->rotate(-angle, rotationAxis.toVector3D());

		//create Message:
		outgoingMessage.type = 5;
		outgoingMessage.modelMatrix = *modelManager->getActiveModel()->getModelMatrix();
		emit sendMessage(outgoingMessage);
	}
}

//slots:

void ModelController::receiveMessage(ModellMessage _incomingMessage){
	switch (_incomingMessage.type){
	case 0: //lock local model and send confirmation
		localObjectLocked = true;
		outgoingMessage.type = 2;
		emit sendMessage(outgoingMessage);
		break;
	case 1: //unlock local model and send confirmation
		localObjectLocked = false;
		outgoingMessage.type = 3;
		emit sendMessage(outgoingMessage);
		break;
	case 2: //remote model is locked
		remoteObjectLocked = true;
		break;
	case 3: //remote model is unlocked
		remoteObjectLocked = false;
		break;

    case 5: //manipulate model
		modelManager->getActiveModel()->setModelMatrix(_incomingMessage.modelMatrix);
        break;
	case 6: //change model
		//break if local model ist locked
		if(localObjectLocked) break;
		//disconnect old activeModel:
		QObject::disconnect(modelManager->getActiveModel(), SIGNAL(updateView()), modelViewer, SLOT(updateGeometry()));
		if (modelManager->changeActiveModel(_incomingMessage.model))
		{
			emit updateView();
			cout << "Wechsel zu Modell " << (_incomingMessage.model+1) << " erfolgreich" << endl;
		}else{
			cout << "Wechsel zu Modell " << (_incomingMessage.model+1) << " fehlgeschlagen, kein " 
				<< (_incomingMessage.model) << ". Model vorhanden" << endl;
		}
		//reconnect new activeModel:
		QObject::connect(modelManager->getActiveModel(), SIGNAL(updateView()), modelViewer, SLOT(updateGeometry()));
		break;
    }

}

void ModelController::changeModel(int modelNumber)
{
	//disconnect old activeModel:
	QObject::disconnect(modelManager->getActiveModel(), SIGNAL(updateView()), modelViewer, SLOT(updateGeometry()));
	if (modelManager->changeActiveModel(modelNumber))
	{
		emit updateView();
		cout << "Wechsel zu Modell " << (modelNumber+1) << " erfolgreich" << endl;
		//create Message:
		outgoingMessage.type = 6;
		outgoingMessage.model = (modelNumber);
		emit sendMessage(outgoingMessage);
	}else{
		cout << "Wechsel zu Modell " << (modelNumber+1) << " fehlgeschlagen, kein " 
			<< (modelNumber+1) << ". Model vorhanden" << endl;
	}
	//reconnect new activeModel:
	QObject::connect(modelManager->getActiveModel(), SIGNAL(updateView()), modelViewer, SLOT(updateGeometry()));
}
