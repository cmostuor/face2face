#pragma once
#include <QT>
#include <QMatrix4x4>
#include <QObject>
#include <iostream>

class ModellMessage
{
public:
	//attributes:
	int type;
	QMatrix4x4 modelMatrix;
	int model;
	QString fileName;
	

	//methods:
	ModellMessage(void);
	ModellMessage(int _type, QMatrix4x4 _modelMatrix, int _model = -1, QString _fileName = "");
	~ModellMessage(void);

	QString serialise();
	//deserialize
	ModellMessage(QString serialisedMessage);

};

