#pragma once

#include <qvector4d.h>
#include <qimage.h>
#include <QOpenGLFunctions_2_0>
#include <DevILImage.h>

class Material{
  public:
	QVector4D ambient;
	QVector4D diffuse;
	QVector4D specular;
	float shininess;

	GLuint tex_id;
	unsigned int numTextures;
	DevILImage** textureImgs;

	Material();
	Material(QVector4D _ambient, QVector4D _diffuse, QVector4D _specular, float _shininess);
	Material(QVector4D _ambient, QVector4D _diffuse, QVector4D _specular, float _shininess, unsigned int _numTextures, DevILImage** _textureImgs);
	~Material(void);
	bool hasTexture();
	void initMaterialTexture(QOpenGLFunctions_2_0* ogl);
	void bindMaterialTexture(QOpenGLFunctions_2_0* ogl);
	DevILImage** getTextureImgAt(unsigned int idx);
};