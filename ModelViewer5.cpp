#include "ModelViewer5.h"
#include "ModelData.h"
#include  "opencv2/opencv.hpp"

ModelViewer::ModelViewer(const QGLFormat& format, QWidget *parent, const QGLWidget* shareWidget, Qt::WindowFlags flags): QGLWidget(format, parent, shareWidget, flags){   
	//webcam image buffer default white image so it isn't empty until the first image is received
	//imgBuffer = new uchar[1280*720*3];
	//for(int i = 0; i < 1280*720*3; i++)
	//	imgBuffer[i] = 0;
    imgBuffer = cv::Mat::zeros( 720, 1280, CV_8UC(3) );

	
	warpCoordinates = new float[8];
	//read warp coos:
	try {
		QFile file("warpCoordinates.txt");
		if(file.open(QIODevice::ReadOnly))
		{
			QTextStream in(&file);
			for(int i= 0; i<8; i++)
			{
				warpCoordinates[i]= in.readLine().toFloat();
			}
		}else{
			//load default coords:
			warpCoordinates[0] = 1.0f;
			warpCoordinates[1] = 1.0f;
			warpCoordinates[2] = 0.0f;
			warpCoordinates[3] = 1.0f;
			warpCoordinates[4] = 0.0f;
			warpCoordinates[5] = 0.0f;
			warpCoordinates[6] = 1.0f;
			warpCoordinates[7] = 0.0f;
		}
		file.close();
	}catch(int x){
		//load default coords
		warpCoordinates[0] = 1.0f;
		warpCoordinates[1] = 1.0f;
		warpCoordinates[2] = 0.0f;
		warpCoordinates[3] = 1.0f;
		warpCoordinates[4] = 0.0f;
		warpCoordinates[5] = 0.0f;
		warpCoordinates[6] = 1.0f;
		warpCoordinates[7] = 0.0f;
   }

}

ModelViewer::~ModelViewer(){
	delete warpCoordinates;
}

void ModelViewer::setModelManager(ModelManager* _modelManager){
	models = _modelManager;	
}

Camera* ModelViewer::getCamera(void){
	return camera;
}


void ModelViewer::renderRotation(){
    //rotate Objects each 1 degree
    //modelMatrix.rotate(1.0f,0.0f,0.0f,1.0f);
	lightMatrix.rotate(1.0f,1.0f,0.0f,0.0f);
    updateGL();
}

void ModelViewer::initializeGL(){
	//Get a set of OpenGL functions of version 2,0
	ogl = new QOpenGLFunctions_2_0();
	ogl->initializeOpenGLFunctions();

	//Set clear color
	qglClearColor(QColor(50,50,50,255));

	//Enable depth buffer
	glEnable(GL_DEPTH_TEST);

	//Setup virtual camera
	camera = new Camera(0.1f,10000.0f);

    //Load the shaders
	loadShader();

	//Initialize geometry
	initGeometry();
}

void ModelViewer::paintGL(){
	//Clear depth buffer and color buffer
	ogl->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//draw webcam image to background
	backgroundShader->bind();
	backgroundShader->setUniformValue("in_ProjMat", camera->getProjMatrix());
	backgroundShader->setUniformValue("in_ViewMat", camera->getViewMatrix());
	//get camera image
	//Bind that texture
	ogl->glBindTexture(GL_TEXTURE_2D, webFeedId);
	//Fill OpenGL memory with webcam data
	ogl->glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,imgBuffer.cols,imgBuffer.rows,0,GL_RGB, GL_UNSIGNED_BYTE,imgBuffer.ptr());
	//Set texture filtering parameters
	ogl->glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
	ogl->glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	camVao->bind();
	ogl->glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	camVao->release();
	backgroundShader->release();
	
	//Bind the shader program to use for models
	shader->bind();

	//Set shader uniform variables
	shader->setUniformValue("in_ProjMat", camera->getProjMatrix());
	shader->setUniformValue("in_ViewMat", camera->getViewMatrix());
	shader->setUniformValue("in_ModelMat", (*models->getActiveModel()->getModelMatrix()));

	shader->setUniformValue("in_NormalMat", (camera->getViewMatrix()*(*models->getActiveModel()->getModelMatrix())).normalMatrix());

	shader->setUniformValue("in_InvertedViewMat", camera->getViewMatrix().inverted());

	shader->setUniformValue("in_LightMatrix", lightMatrix);

	//Bind VAO and draw elements of the index buffer
	models->getActiveModel()->paintModel(shader, ogl);
	shader->release();
}

void ModelViewer::resizeGL(int w, int h){
	//Create a viewport of appropriate size
	glViewport(0, 0, (GLint)w, (GLint)h);
}

void ModelViewer::loadShader(){
	//Load the shader programs from file
	//We make use of the Qt resources. Be sure to recompile resource files when shaders have been changed
	//Dont't refactor the source file path, but name the shaders accordingly
	
	//first the shader for the camera image plane
	backgroundShader = new QOpenGLShaderProgram();
	if(!backgroundShader->addShaderFromSourceFile(QOpenGLShader::Vertex,"backgroundshader.vert")) std::cout << "Error loading vertex backgroundShader! " << backgroundShader->log().toStdString() << std::endl;
	if(!backgroundShader->addShaderFromSourceFile(QOpenGLShader::Fragment,"backgroundshader.frag")) std::cout << "Error loading fragment backgroundShader! " << backgroundShader->log().toStdString() << std::endl;
	if(!backgroundShader->link()) std::cout << "Error linking shader" << std::endl;
	
	//model shader
	shader = new QOpenGLShaderProgram();
    if(!shader->addShaderFromSourceFile(QOpenGLShader::Vertex,"./shader.vert")) std::cout << "Error loading vertex shader! " << shader->log().toStdString() << std::endl;
    if(!shader->addShaderFromSourceFile(QOpenGLShader::Fragment,"./shader.frag")) std::cout << "Error loading fragment shader! " << shader->log().toStdString() << std::endl;
	if(!shader->link()) std::cout << "Error linking shader" << std::endl;
}

void ModelViewer::initGeometry(){
	//set a rectangle to receive webcam images
	QVector3D topLeft, bottomRight;
	//camera->getPlaneDimensions(camera->getEyeFarPlane(), topLeft, bottomRight);
	//coordinates hardcoded since plane dimensions of camera return unusable values
	float camPlaneVertexData[] = {
	-4.97f, -3.75f,  -4.f,
	 4.97f, -3.75f,  -4.f,
	 4.97f,  3.75f,  -4.f,
	-4.97f,  3.75f,  -4.f};//{topLeft.x(), bottomRight.y(), bottomRight.z(), bottomRight.x(), bottomRight.y(), bottomRight.z(),  bottomRight.x(), topLeft.y(), bottomRight.z(), topLeft.x(), topLeft.y(), bottomRight.z()};
	int camPlaneIndices[] = {0, 1, 2, 
		0, 2, 3};//{0, 1, 2, 2, 3, 0};

	//Create VAO
	camVao = new QOpenGLVertexArrayObject();
	camVao->create();
	camVao->bind();

	//Create index BO
	camIndexBuffer = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
	camIndexBuffer->create();
	camIndexBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
	camIndexBuffer->bind();

	camIndexBuffer->allocate(camPlaneIndices, 6 * sizeof(int));

	//Create vertex BO
	camVertexBuffer = new QOpenGLBuffer();
	camVertexBuffer->create();
	camVertexBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
	camVertexBuffer->bind();

	camVertexBuffer->allocate(camPlaneVertexData, 4 * 3 * sizeof(float));

	//Enable backgroundShader attribute
	backgroundShader->enableAttributeArray( "in_Position" );
	backgroundShader->setAttributeArray( "in_Position", GL_FLOAT, 0, 3 );

	//Create texture BO
	camTexCoordBuffer = new QOpenGLBuffer();
	camTexCoordBuffer->create();
	camTexCoordBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
	camTexCoordBuffer->bind();

	camTexCoordBuffer->allocate(warpCoordinates, 4 * 2 * sizeof(float));

	//Enable backgroundShader attribute
	backgroundShader->enableAttributeArray( "in_TexCoords" );
	backgroundShader->setAttributeArray( "in_TexCoords", GL_FLOAT, 0, 2 );

	//initialize background texture
	//Generate texture id
	ogl->glGenTextures(1, &webFeedId);

	//initialize model geometry
	for (int i=0; i < models->getNumberOfModels(); i++){
		models->getModelAt(i)->initModelGeometry(shader, ogl);
	}
	
}


void ModelViewer::initTextures(){
	texture = new QImage();
	bool s = texture->load(":/koala.jpg");

	//Generate texture id
	ogl->glGenTextures(1, &tex_id);
	//Bind that texture
	ogl->glBindTexture(GL_TEXTURE_2D, tex_id);
	//Fill OpenGL memory of the texture with data
	ogl->glTexImage2D(GL_TEXTURE_2D,0,GL_RGB8,texture->width(),texture->height(),0,GL_BGRA,GL_UNSIGNED_BYTE,texture->bits());

	//Set texture filtering parameters
	ogl->glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
	ogl->glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

//mouse events for ArcBall-Rotation:
void ModelViewer::mousePressEvent(QMouseEvent* event)
{
	//compute mouse position in y,x in [0,1]
	float x = event->x();
	float y = event->y();
	QVector2D mousePosition = QVector2D(x/width(), y/height());
	
	emit mousePressed(mousePosition);
	
	QVector3D hitPoint;
	models->getActiveModel()->intersect(*camera , x/width(), y/height() ,hitPoint);
}

void ModelViewer::mouseMoveEvent(QMouseEvent* event)
{
	//compute mouse position in y,x in [0,1]
	float x = event->x();
	float y = event->y();
	QVector2D mousePosition = QVector2D(x/width(), y/height());
	emit mouseMoved(mousePosition);
}


void ModelViewer::mouseReleaseEvent(QMouseEvent* event)
{
	emit mouseReleased();
}


void ModelViewer::updateGeometry(){
	updateGL();
}

void ModelViewer::changeCamImg(cv::Mat _imgBuffer){
	
	//get new camera image
	imgBuffer= _imgBuffer;
	updateGL();
	
}
