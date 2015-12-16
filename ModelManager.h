#pragma once

#include <string>
#include <qfileinfo.h>
#include <qdiriterator.h>

#include "assimp/Importer.hpp"      // C++ importer interface
#include "assimp/scene.h"
#include "assimp/postprocess.h"     // Post processing flags

#include <il.h> //image reading library (DevIL)

#include <QMatrix4x4>
#include <QVector>
#include <qimage.h>
#include <QImageReader>
#include <DevILImage.h>

#include "Model.h"

using namespace std;
class ModelManager
{
	unsigned int numberOfModels;
	QVector<Model*> ModelList;
	unsigned int activeModel;

public:
	ModelManager(void);
	~ModelManager(void);
	Model* getActiveModel();
	Model* getModelAt(unsigned int position);
	int getNumberOfModels();
	bool changeActiveModel(unsigned int position);
	bool loadScene(string FilePath);
};

