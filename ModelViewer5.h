#ifndef ModelViewerH
#define ModelViewerH

#include <iostream>

#include <QGLWidget>
#include <QOpenGLFunctions_2_0>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <qmatrix.h>


//ArcBall-Rotation:
#include <QTimer>
#include <QVector2D>
#include <QMouseEvent>
#include <cmath>

//Keyboard
#include <QKeyEvent>

#include "Camera.h"
#include "ModelManager.h"
//#include "EscapiThread.h"
#include "OpenCvThread.h"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"

class ModelViewer : public QGLWidget{
	Q_OBJECT

private:
	//OpenGL functions
	QOpenGLFunctions_2_0* ogl;
	//Shader
	QOpenGLShaderProgram* shader;
	//Vertex array object
	QOpenGLVertexArrayObject* vao;
	//Buffer object for vertex info
	QOpenGLBuffer* vertices;
	//Buffer object for normals
	QOpenGLBuffer* normals;
	//Buffer object for indices
	QOpenGLBuffer* indices;
	//Buffer object for texture coordinates
	QOpenGLBuffer* tex_coords;

	//Textures
	GLuint tex_id;
	QImage* texture;
	float* warpCoordinates;

	//Camera
	Camera* camera;

	ModelManager* models;

	QMatrix4x4 lightMatrix;

	//webcam environment:

	//camera image buffer
	cv::Mat imgBuffer;
	//simple texture only shader
	QOpenGLShaderProgram* backgroundShader;
	//Vertex array object 
	QOpenGLVertexArrayObject* camVao;
	//Buffer object for vertex info
	QOpenGLBuffer* camVertexBuffer;
	//Buffer object for indices
	QOpenGLBuffer* camIndexBuffer;
	//Buffer object for texture coordinates
	QOpenGLBuffer* camTexCoordBuffer;
	//webcam image to texture id
	GLuint webFeedId;

	//Load shader
	void loadShader();
	
	//Init geometry
	void initGeometry();

	//Load and init textures
	void initTextures();

public slots:
    //Rotation Renderer called by timer
    void renderRotation();
	//update Geometry if model has changed
	void updateGeometry();
	//receive latest webcam image
	void changeCamImg(cv::Mat _imgBuffer);

signals:
	//ArcBall-Signals
	void mousePressed(QVector2D mousePosition);
	void mouseMoved(QVector2D mousePosition);
	void mouseReleased();

protected:
	//Init OpenGL, called once at the beginning
	void initializeGL();
	//Paint scene
    void paintGL();
	//Resize event
	void resizeGL(int w, int h);

	//methods for ArcBall-Rotation:
	//Mouseevents:
	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);

public:
	ModelViewer( const QGLFormat& format, QWidget *parent = 0, const QGLWidget* shareWidget = 0, Qt::WindowFlags flags = 0);
	Camera* getCamera();
	QMatrix4x4 getModelMatrix();
	void setModelManager(ModelManager* _modelManager);
	

	~ModelViewer();

};

#endif
