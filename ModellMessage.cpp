#include "ModellMessage.h"


ModellMessage::ModellMessage(void)
{
	
}

ModellMessage::ModellMessage(int _type, QMatrix4x4 _modelMatrix, int _model, QString _fileName):
type(_type), modelMatrix(_modelMatrix), model(_model), fileName(_fileName){
}


ModellMessage::ModellMessage(QString serialisedMessage){
	QList<QString> messages=serialisedMessage.split('|');

	//read type:
	type = messages[0].toInt();
	
	if (type > 3){
		//read modelMatrix
		float floatMatrix[16];									//ModellMatrix in float
		QList<QString> byteMatrix=messages[1].split(',');	//ModelMarix in ByteArray
		for(int i=0; i<16; i++){
			floatMatrix[i]=byteMatrix[i].toFloat();
		}
		modelMatrix= QMatrix4x4(floatMatrix).transposed();

		//read model
		model = messages[2].toInt();

		//read fileName:
		fileName = messages[3];
	}
}

QString ModellMessage::serialise(){
	QString message;

	//write type:
	message =QString::number(type) + "|";

	if(type > 3){
		//write modelMatrix
		float* mmData=modelMatrix.data();
		for(int i=0; i<16; i++){
			message+=QString::number(mmData[i]);
			message+=",";
		}
		message+="|";

		//write model:
		message+= QString::number(model) + "|";

		//write fileName
		message+= fileName;
	}
	return message.toUtf8();

}

ModellMessage::~ModellMessage(void)
{
}
