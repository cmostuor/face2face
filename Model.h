#pragma once

#include <string>
#include <iostream>

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>
#include <assimp/postprocess.h>     // Post processing flags 

#include <QMatrix4x4>
#include <qvector3d.h>

#include <QOpenGLFunctions_2_0>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>

#include "Camera.h"
#include "BVH.h"
#include "HitRec.h"
#include "Ray.h"
#include "Triangle.h"
#include "Material.h"

using namespace std;

class Model : public QObject
{
	Q_OBJECT

	unsigned int meshNumber;
	unsigned int materialNumber;
	unsigned int* vertexNumber;
	unsigned int* indexNumber;

	unsigned int* materialIndex;

	float** vertexData;
	int** indexData;
	float** normalsData;

	Material** materials;
	float** textureCoords;

	//Für Test:
	Triangle* triangles;

	QMatrix4x4 modelMatrix;

	//Vertex array object 
	QOpenGLVertexArrayObject** vao;
	//Buffer object for vertex info
	QOpenGLBuffer** vertexBuffer;
	//Buffer object for normals
	QOpenGLBuffer** normalBuffer;
	//Buffer object for indices
    QOpenGLBuffer** indexBuffer;
	//Buffer object for texture coordinates
	QOpenGLBuffer** tex_coordBuffer;

	BVH* boundingVolumeHierarchy;

	Triangle* meshToTriangles(unsigned int &totalIndexNumber);
	QVector3D boundingBoxDiagonal;

public:
	Model(unsigned int _meshNumber, unsigned int _materialNumber, 
		unsigned int* _vertexNumber, float** _vertexData, 
		unsigned int* _indexNumber, int** _indexData, float** _normals, 
		Material** _materials, unsigned int* _materialIndex, float** _textureCoords);
	void centerModel();

	~Model(void);

	unsigned int* getVertexNumber();
	unsigned int* getIndexNumber();
	float** getVertexData();
	float** getNormalsData();
	int** getIndexData();
	QVector3D getBoundingBoxDiagonal();
	QMatrix4x4* getModelMatrix();

	void initModelGeometry(QOpenGLShaderProgram* shader, QOpenGLFunctions_2_0* ogl);
	void paintModel(QOpenGLShaderProgram* shader, QOpenGLFunctions_2_0* ogl);

	void normalizeScale();

	void printData();
	void printIndices();
	void printNormals();
	void printTexCoords();

    //manupilate Model:
    void scale(float factor);
    void translate(QVector3D translationVector);
    void rotate(float angle, QVector3D rotationAxis);
    void setModelMatrix(QMatrix4x4 _modelMatrix);
	void resetModel();

	/*shoots a ray from the camera through the given pixel
	returns true if modell is hit
	width and hight are width and hight of the current window
	hitpoint contains where the ray intersects the modell */
	bool intersect(Camera &camera, float x, float y, QVector3D &hitPoint);
signals:
	void updateView();

};

