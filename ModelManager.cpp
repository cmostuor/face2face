#include "ModelManager.h"




ModelManager::ModelManager(void)
{
}


ModelManager::~ModelManager(void)
{
}


/* creates an importer, loads the desired file and returns the importer since handing over the scene does not work
@param pFile: string that contains the filename of the scene

*/

static Assimp::Importer* import3DScene( const string& pFile)
{
	cout<<"Importing 3D Scene...";

  // Create an instance of the Importer class
	Assimp::Importer* importer=new Assimp::Importer();

		importer->ReadFile( pFile, 
		aiProcess_GenNormals			 | 
		aiProcess_GenSmoothNormals		 |
        aiProcess_CalcTangentSpace       | 
        aiProcess_Triangulate            |
        aiProcess_JoinIdenticalVertices  |
        aiProcess_SortByPType);

  
 
  // testing if import worked
		if( !(importer->GetScene()))
  {
	cerr<<"Couldn't load Scene"<<endl;
    return NULL;
  }
	cout<<"done!"<<endl;
	return importer;

}

bool ModelManager::loadScene(string FilePath)
{
	cerr<<"Loading Scene..."<<endl;
	//handing over an aiScene does not work, therefore we hand over the importer instead, GetScene() loads the last imported scene.
	Assimp::Importer* importer=import3DScene(FilePath);
	const aiScene* scene = importer->GetScene();

	unsigned int* vertexNumber = new unsigned int[scene->mNumMeshes];
	unsigned int* indicesNumber = new unsigned int[scene->mNumMeshes];
	unsigned int* materialIndex = new unsigned int[scene->mNumMeshes];

	float** vertexData = new float*[scene->mNumMeshes];
	int** indicesData = new int*[scene->mNumMeshes];
	float** normals = new float*[scene->mNumMeshes];

	Material** materials = new Material*[scene->mNumMaterials];

	float** textureCoords = new float*[scene->mNumMeshes];


	if (scene != NULL) 
	{
		cout<<scene->mNumMeshes; 
		for(int curMesh = 0; curMesh<scene->mNumMeshes; curMesh++)
		{
			cout<<".";
			vertexNumber[curMesh] = scene->mMeshes[curMesh]->mNumVertices;
			indicesNumber[curMesh] = 3*scene->mMeshes[curMesh]->mNumFaces;
			materialIndex[curMesh] = scene->mMeshes[curMesh]->mMaterialIndex;
			vertexData[curMesh] = new float[vertexNumber[curMesh] * 3];
			textureCoords[curMesh] = new float[vertexNumber[curMesh] * 2];
			indicesData[curMesh] = new int[3*scene->mMeshes[curMesh]->mNumFaces];
			normals[curMesh] = new float[3*scene->mMeshes[curMesh]->mNumVertices];
			for(int curFace = 0; curFace < scene->mMeshes[curMesh]->mNumFaces; curFace++){

				for(int curIndex = 0; curIndex < 3; curIndex++)
				{
					//cout<<scene->mMeshes[curMesh]->mFaces[curFace].mIndices[curIndex]<<" | ";
					indicesData[curMesh][curFace*3+curIndex] = scene->mMeshes[curMesh]->mFaces[curFace].mIndices[curIndex];
				}
				//cout<<endl;
			}	

			for(int curVertex = 0; curVertex<vertexNumber[curMesh]; curVertex++)
			{
				for(unsigned int coords=0; coords<3; coords++)
				{
					vertexData[curMesh][curVertex*3+coords] = scene->mMeshes[curMesh]->mVertices[curVertex][coords];
				}
			}

			QVector<int>* facesPerVertex = new QVector<int>[scene->mMeshes[curMesh]->mNumVertices];
			QVector3D* faceNormals = new QVector3D[scene->mMeshes[curMesh]->mNumFaces];
			aiVector3D temp1,temp2;
			for(int curFace = 0; curFace < scene->mMeshes[curMesh]->mNumFaces; curFace++){
				for(int idx = 0; idx < 3; idx++){
					facesPerVertex[scene->mMeshes[curMesh]->mFaces[curFace].mIndices[idx]].append(curFace);
				}
				temp1 = scene->mMeshes[curMesh]->mVertices[scene->mMeshes[curMesh]->mFaces[curFace].mIndices[0]] - 
						scene->mMeshes[curMesh]->mVertices[scene->mMeshes[curMesh]->mFaces[curFace].mIndices[1]];
				temp2 = scene->mMeshes[curMesh]->mVertices[scene->mMeshes[curMesh]->mFaces[curFace].mIndices[2]] - 
						scene->mMeshes[curMesh]->mVertices[scene->mMeshes[curMesh]->mFaces[curFace].mIndices[1]];
				faceNormals[curFace] = QVector3D::crossProduct(QVector3D(temp1.x,temp1.y,temp1.z).normalized(),QVector3D(temp2.x,temp2.y,temp2.z).normalized());
				//faceNormals[curFace].normalize();
			}
			QVector3D vertexNormal;
			for(int curVertex = 0; curVertex < scene->mMeshes[curMesh]->mNumVertices; curVertex++){
				vertexNormal = QVector3D(0.0f, 0.0f, 0.0f);
				//cout<<"Vertex "<<curVertex<<" is adjacent to "<<facesPerVertex[curVertex].size()<<" faces"<<endl;
				for(int normal = 0; normal < facesPerVertex[curVertex].size(); normal++){
					vertexNormal += faceNormals[facesPerVertex[curVertex].at(normal)];
				}
				//vertexNormal/ facesPerVertex[curVertex].size();
				vertexNormal.normalize();
				normals[curMesh][curVertex*3] = vertexNormal[0];
				normals[curMesh][curVertex*3+1] = vertexNormal[1];
				normals[curMesh][curVertex*3+2] = vertexNormal[2];
			}
			delete[] facesPerVertex;
			delete[]faceNormals;	
			if(scene->mMeshes[curMesh]->HasTextureCoords(0)){
				//cout<<"loading object texture coordinates"<<endl;
				for(int curVertex = 0; curVertex<vertexNumber[curMesh]; curVertex++)
				{		//Assimp stores texture coordinates in different texture channels
						//mTextureCoords[0] refers to the diffuse texture channel
						textureCoords[curMesh][curVertex*2] = scene->mMeshes[curMesh]->mTextureCoords[0][curVertex].x;
						textureCoords[curMesh][curVertex*2+1] = scene->mMeshes[curMesh]->mTextureCoords[0][curVertex].y;
				}
			} else {
				cout<<"There is no Texture Mapped"<<endl;
			}
		}

		aiColor3D color;
		QVector4D ambient;
		QVector4D diffuse;
		QVector4D specular;
		float shininess;
		//cout<<"Number of Materials: "<<scene->mNumMaterials<<endl;
		aiString materialName;
		for(int curMaterial = 0; curMaterial < scene->mNumMaterials; curMaterial++){
			//if Assimp created a default material create own, better default material
			scene->mMaterials[curMaterial]->Get(AI_MATKEY_NAME, materialName);
			string nameBuffer = materialName.data;
			if(nameBuffer == "DefaultMaterial"){
				cout<<"default material generated"<<endl;
				materials[curMaterial] = new Material();
			} else { // otherwise, take the model's material
				scene->mMaterials[curMaterial]->Get(AI_MATKEY_COLOR_AMBIENT, color);
				ambient.setX(color.r);
				ambient.setY(color.g);
				ambient.setZ(color.b);
				ambient.setW(1.0f);
				scene->mMaterials[curMaterial]->Get(AI_MATKEY_COLOR_DIFFUSE, color);
				diffuse.setX(color.r);
				diffuse.setY(color.g);
				diffuse.setZ(color.b);
				diffuse.setW(1.0f);
				//cout<<"Diffuse Color: "<<diffuse[0]<<" | "<<diffuse[1]<<" | "<<diffuse[2]<<endl;
				scene->mMaterials[curMaterial]->Get(AI_MATKEY_COLOR_SPECULAR, color);
				specular.setX(color.r);
				specular.setY(color.g);
				specular.setZ(color.b);
				specular.setW(1.0f);
				scene->mMaterials[curMaterial]->Get(AI_MATKEY_SHININESS, shininess);
				
				aiString aiFilePath;
				aiReturn texFound = scene->mMaterials[curMaterial]->GetTexture(aiTextureType_DIFFUSE, 0, &aiFilePath);
				if(texFound == AI_SUCCESS) {
					
					DevILImage** textureImg = new DevILImage*[1];
					textureImg[0] = new DevILImage();
					
					QString textureFileName(aiFilePath.data);
					
					textureFileName = QFileInfo(textureFileName).fileName();
					QString mainPath = QFileInfo(QString::fromStdString(FilePath)).absolutePath();
					QByteArray temp;
					char *textureFilePath;

					QDirIterator dirIt(mainPath,QDirIterator::Subdirectories);
					while (dirIt.hasNext()) {
						dirIt.next();
						if (QFileInfo(dirIt.filePath()).isFile()){
							
							if (QFileInfo(dirIt.filePath()).fileName().compare(&textureFileName, Qt::CaseInsensitive) == 0)
							{
								cout << QFileInfo(dirIt.filePath()).fileName().toStdString() << endl;
								temp = dirIt.filePath().toLocal8Bit();
								textureFilePath = temp.data();
							}
						}
					}
					/////////////////////////////////////////////////////
					textureImg[0] = new DevILImage((ILstring)textureFilePath);
					materials[curMaterial] = new Material(ambient, diffuse, specular, shininess, 1, textureImg);
					/////////////////////////////////////////////////////
                    

				} else {
					materials[curMaterial] = new Material(ambient, diffuse, specular, shininess);
				}
			}
		}
		ModelList.append(new Model(scene->mNumMeshes, scene->mNumMaterials, vertexNumber, vertexData, indicesNumber, indicesData, normals, materials, materialIndex, textureCoords));
		activeModel = ModelList.length() -1;
		numberOfModels = ModelList.length();
		cerr<<"done!"<<endl;
		return true;
	}

	cerr<<"Couldn't read Scene-Data"<<endl;
	return false;
}

//returns the currently active Model
Model* ModelManager::getActiveModel(){
	return ModelList[activeModel];
}

Model* ModelManager::getModelAt(unsigned int position)
{
	if(position < ModelList.size())
	{
		return ModelList[position];
	}
	cout << "OutOfBounds-Fehler" << endl;
	return 0;
}

bool ModelManager::changeActiveModel(unsigned int position){
	if(position < ModelList.length()){
		activeModel = position;
		return true;
	}else{
		return false;
	}
}

int ModelManager::getNumberOfModels()
{
	return numberOfModels;
}
