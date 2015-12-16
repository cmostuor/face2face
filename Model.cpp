#include "Model.h"



Model::Model(unsigned int _meshNumber, unsigned int _materialNumber, unsigned int* _vertexNumber, float** _vertexData, unsigned int* _indicesNumber, int** _indexData, float** _normals, Material** _materials, unsigned int* _materialIndex, float** _textureCoords):
	meshNumber(_meshNumber), materialNumber(_materialNumber), vertexNumber(_vertexNumber), materialIndex(_materialIndex), vertexData(_vertexData), indexNumber(_indicesNumber), indexData(_indexData), normalsData(_normals),
		materials(_materials), textureCoords(_textureCoords)
{	
	vao = new QOpenGLVertexArrayObject*[meshNumber];
	vertexBuffer = new QOpenGLBuffer*[meshNumber];
	normalBuffer = new QOpenGLBuffer*[meshNumber];
	indexBuffer = new QOpenGLBuffer*[meshNumber];
	tex_coordBuffer = new QOpenGLBuffer*[meshNumber];
	unsigned int totalIndexNumber;
	//center Model:
	centerModel();
	triangles = meshToTriangles(totalIndexNumber);
	boundingVolumeHierarchy = new BVH(triangles, totalIndexNumber/3);
	//calculate diagonal of bounding box:
	QVector3D* bounds = boundingVolumeHierarchy->getBoundingBox()-> bounds;
	boundingBoxDiagonal = bounds[0] - bounds[1];
	normalizeScale();
}

Model::~Model(void)
{
	delete boundingVolumeHierarchy;
}

unsigned int* Model::getVertexNumber(){
	return vertexNumber;
}

unsigned int* Model::getIndexNumber(){
	return indexNumber;
}

float** Model::getVertexData(){
	return vertexData;
}

float** Model::getNormalsData(){
	return normalsData;
}

int** Model::getIndexData(){
	return indexData;
}

QVector3D Model::getBoundingBoxDiagonal(){
	//returns the diagonal of the bounding box:
	return boundingBoxDiagonal;
}

QMatrix4x4* Model::getModelMatrix(){
	return &modelMatrix;
}

void Model::initModelGeometry(QOpenGLShaderProgram* shader, QOpenGLFunctions_2_0* ogl){
	for(int curMesh = 0; curMesh < meshNumber; curMesh++){
		//Create VAO
		vao[curMesh] = new QOpenGLVertexArrayObject();
		vao[curMesh]->create();
		vao[curMesh]->bind();

		//Create index BO
		indexBuffer[curMesh] = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
		indexBuffer[curMesh]->create();
		indexBuffer[curMesh]->setUsagePattern(QOpenGLBuffer::StaticDraw);
		indexBuffer[curMesh]->bind();

		indexBuffer[curMesh]->allocate(indexData[curMesh], indexNumber[curMesh]* sizeof(int));

		//Create vertex BO
		vertexBuffer[curMesh] = new QOpenGLBuffer();
		vertexBuffer[curMesh]->create();
		vertexBuffer[curMesh]->setUsagePattern(QOpenGLBuffer::StaticDraw);
		vertexBuffer[curMesh]->bind();

		//vertexBuffer->allocate(vertex_data, 2 * 8 * 3 * sizeof(float));
		vertexBuffer[curMesh]->allocate(vertexData[curMesh], vertexNumber[curMesh] * 3 * sizeof(float));

		//Enable shader attribute
		shader->enableAttributeArray( "in_Position" );
		shader->setAttributeArray( "in_Position", GL_FLOAT, 0, 3 );

		//Create normals BO
		normalBuffer[curMesh] = new QOpenGLBuffer();
		normalBuffer[curMesh]->create();
		normalBuffer[curMesh]->setUsagePattern(QOpenGLBuffer::StaticDraw);
		normalBuffer[curMesh]->bind();
		normalBuffer[curMesh]->allocate(normalsData[curMesh], vertexNumber[curMesh] * 3 * sizeof(float));

		//Enable shader attribute
		shader->enableAttributeArray( "in_Normals" );
		shader->setAttributeArray( "in_Normals", GL_FLOAT, 0, 3 );

		//Create texture BO
		tex_coordBuffer[curMesh] = new QOpenGLBuffer();
		tex_coordBuffer[curMesh]->create();
		tex_coordBuffer[curMesh]->setUsagePattern(QOpenGLBuffer::StaticDraw);
		tex_coordBuffer[curMesh]->bind();

		tex_coordBuffer[curMesh]->allocate(textureCoords[curMesh], vertexNumber[curMesh] * 2 * sizeof(float));

		//Enable shader attribute
		shader->enableAttributeArray( "in_TexCoords" );
		shader->setAttributeArray( "in_TexCoords", GL_FLOAT, 0, 2 );

		//initialize textures in materials
	}
	for(int curMaterial = 0; curMaterial < materialNumber; curMaterial++){
		if(materials[curMaterial]->hasTexture()){
			materials[curMaterial]->initMaterialTexture(ogl);
		}
	}
}

void Model::paintModel(QOpenGLShaderProgram* shader, QOpenGLFunctions_2_0* ogl){
	for(int curMesh = 0; curMesh < meshNumber; curMesh++){
		shader->setUniformValue("in_hasTexture", materials[materialIndex[curMesh]]->hasTexture());
		shader->setUniformValue("in_ambient", materials[materialIndex[curMesh]]->ambient);
		shader->setUniformValue("in_diffuse", materials[materialIndex[curMesh]]->diffuse);
		shader->setUniformValue("in_specular", materials[materialIndex[curMesh]]->specular);
		shader->setUniformValue("in_shininess", materials[materialIndex[curMesh]]->shininess);
		materials[materialIndex[curMesh]]->bindMaterialTexture(ogl);
		vao[curMesh]->bind();
		ogl->glDrawElements(GL_TRIANGLES, indexNumber[curMesh], GL_UNSIGNED_INT, 0);
		vao[curMesh]->release();
	}
}

void Model::printData()
{
	for(int meshes = 0; meshes < meshNumber; meshes++){
		for (int vertices = 0; vertices < vertexNumber[meshes]; vertices++)
		{
			cout<<"Vertex Number "<<vertices<<" ";
			for(int coords = 0; coords < 3; coords++){
				cout << vertexData[meshes][vertices+coords] << " | ";
			}
			cout<<endl;
		}
	}
}

void Model::printIndices()
{
	cout<<"index numbers:"<<endl;
	for(int meshes = 0; meshes < meshNumber; meshes++){
		for (int index = 0; index < indexNumber[meshes]; index+=3)
		{
			cout << indexData[meshes][index] << " | " << indexData[meshes][index+1] << " | " << indexData[meshes][index+2] << endl;
		} 
	}
}

void Model::printNormals()
{
	for(int meshes = 0; meshes < meshNumber; meshes++){
		for (int normals = 0; normals < vertexNumber[meshes]; normals++)
		{
			cout<<"Normal Number "<<normals<<" ";
			for(int coords = 0; coords < 3; coords++){
				cout << normalsData[meshes][normals+coords] << " | ";
			}
			cout<<endl;
		}
	}
}

void Model::printTexCoords(){
	for(int meshes = 0; meshes < meshNumber; meshes++){
		for (int texCoord = 0; texCoord < vertexNumber[meshes]; texCoord++)
		{
			cout<<"texCoord Number "<<texCoord<<" ";
			for(int coords = 0; coords < 2; coords++){
				cout << textureCoords[meshes][texCoord+coords] << " | ";
			}
			cout<<endl;
		}
    }
}


Triangle* Model::meshToTriangles(unsigned int &totalIndexNumber){
	totalIndexNumber = 0;
	for(int curMesh = 0; curMesh < meshNumber; curMesh++){
		totalIndexNumber += indexNumber[curMesh];
	}
	Triangle* triangles=new Triangle[totalIndexNumber/3];
	int currentTriangle=0;
	for(int curMesh = 0; curMesh < meshNumber; curMesh++){
		for(int i=0; i < indexNumber[curMesh]; i+=3){
			triangles[currentTriangle]=Triangle(QVector3D(vertexData[curMesh][indexData[curMesh][i]*3],vertexData[curMesh][indexData[curMesh][i]*3+1],vertexData[curMesh][indexData[curMesh][i]*3+2]),
				QVector3D(vertexData[curMesh][indexData[curMesh][i+1]*3],vertexData[curMesh][indexData[curMesh][i+1]*3+1],vertexData[curMesh][indexData[curMesh][i+1]*3+2]),
				QVector3D(vertexData[curMesh][indexData[curMesh][i+2]*3],vertexData[curMesh][indexData[curMesh][i+2]*3+1],vertexData[curMesh][indexData[curMesh][i+2]*3+2]));
			currentTriangle++;
		}
	}
	cout<<"Mesh zu Triangle"<<endl;
	return triangles;
}

void Model::normalizeScale(){
	//get size of model and scale it so it fits into the window
	modelMatrix.scale(/*0.1/boundingBoxDiagonal.length()*/ 1/1000.);

}
void Model::scale(float factor){
	//modify temporary modelMatrix
	QMatrix4x4 newModelMatrix = modelMatrix;
	newModelMatrix.scale(factor);
	//check if it's too small:
	if((newModelMatrix*boundingBoxDiagonal).length() < 1.f) return;
	//check if model is too large:
	if((newModelMatrix*boundingBoxDiagonal).length() > 4.9f) return;

	modelMatrix = newModelMatrix;
	emit updateView();
}

void Model::translate(QVector3D translationVector){
    modelMatrix.translate(translationVector);
	emit updateView();
}

void Model::rotate(float angle, QVector3D rotationAxis){
    modelMatrix.rotate(angle, rotationAxis);
	emit updateView();
}


void Model::setModelMatrix(QMatrix4x4 _modelMatrix){
    modelMatrix = _modelMatrix;
    emit updateView();
}

void Model::centerModel(){
	//compute barycenter:
	QVector3D barycenter = QVector3D();
	int totalVertexNumber = 0;
	cout << "computing barycenter " ;
	//sum up all vertices
	for(int curMesh = 0; curMesh<meshNumber; curMesh++){
		for(int curVertex = 0; curVertex<vertexNumber[curMesh]; curVertex++)
		{
			barycenter.setX(barycenter.x()+vertexData[curMesh][curVertex*3]); 
			barycenter.setY(barycenter.y()+vertexData[curMesh][curVertex*3+1]);
			barycenter.setZ(barycenter.z()+vertexData[curMesh][curVertex*3+2]);
		}
		cout<<".";
		totalVertexNumber += vertexNumber[curMesh];
	}
	barycenter /= totalVertexNumber;
	cout <<"completed" << endl;

	cout << "centering model ";
	//move barycenter to (0,0,0):
	for(int curMesh = 0; curMesh<meshNumber; curMesh++){
		for(int curVertex = 0; curVertex<vertexNumber[curMesh]; curVertex++)
		{
			vertexData[curMesh][curVertex*3] -= barycenter.x();
			vertexData[curMesh][(curVertex*3)+1] -= barycenter.y();
			vertexData[curMesh][(curVertex*3)+2] -= barycenter.z();
		}
		cout << ".";
	}
	
	emit updateView();
	cout << "complete" << endl;
}

void Model::resetModel(){
	//reset model position/rotation
	modelMatrix.setToIdentity();
	normalizeScale();
	emit updateView();
	cout<<"reseted model"<<endl;
}

bool Model::intersect(Camera &camera, float x, float y, QVector3D &hitPoint){
	// invert y due to different definition in QT-screen / openGL
	// see http://antongerdelan.net/opengl/raycasting.html
	Ray ray( (camera.getViewMatrix() * modelMatrix).inverted() * QVector3D(0.f, 0.f, 0.f),
			((camera.getProjMatrix() * camera.getViewMatrix() * modelMatrix).inverted() * QVector3D(2.f * x -1.f, 1.f -2.f * y, 1.f)), 
            0.f, FLT_MAX);
	ray.direction.normalize();
	HitRec hitRec = boundingVolumeHierarchy->intersect(ray);
	// intersect triangles transformed into projection space with touch/click 
	if(hitRec.id<0)//no intersection
		return false;
	hitPoint = modelMatrix *  (ray.origin + hitRec.distance * ray.direction);
	//transform the hitpoint back into world space
	cout<<"Hitpoint: "<<hitPoint.x()<<" | "<<hitPoint.y()<<" | "<<hitPoint.z()<<", Triangle-Id: "<<hitRec.id<<endl;
	return true;
}


