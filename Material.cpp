#include "Material.h"

Material::Material() : ambient(QVector4D(0.2f, 0.2f, 0.2f, 1.0f)), diffuse(QVector4D(1.0f, 0.8f, 0.8f, 1.0f)), specular(QVector4D(1.0f, 1.0f, 1.0f, 1.0f)), shininess(5.0f), numTextures(0){
}

Material::Material(QVector4D _ambient, QVector4D _diffuse, QVector4D _specular, float _shininess) : ambient(_ambient), diffuse(_diffuse), specular(_specular), shininess(_shininess), numTextures(0){
}

Material::Material(QVector4D _ambient, QVector4D _diffuse, QVector4D _specular, float _shininess, unsigned int _numTextures, DevILImage** _textureImgs) : ambient(_ambient), diffuse(_diffuse), specular(_specular), shininess(_shininess), textureImgs(_textureImgs), 	numTextures(_numTextures){
}

Material::~Material(void){
	for(int tex = 0; tex < numTextures; tex++){
		delete[] textureImgs[tex];
	}
}

void Material::initMaterialTexture(QOpenGLFunctions_2_0* ogl){
	//Generate texture id
	ogl->glGenTextures(1, &tex_id);
	//Bind that texture
	ogl->glBindTexture(GL_TEXTURE_2D, tex_id);
	
	//Set texture filtering parameters
	ogl->glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
	ogl->glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	ogl->glTexImage2D(GL_TEXTURE_2D, 0, textureImgs[0]->type, textureImgs[0]->width,
     textureImgs[0]->height, 0, textureImgs[0]->format, GL_UNSIGNED_BYTE,
     textureImgs[0]->data);
}

void Material::bindMaterialTexture(QOpenGLFunctions_2_0* ogl){
		ogl->glBindTexture(GL_TEXTURE_2D,tex_id);
}

bool Material::hasTexture(){
	return numTextures > 0;
}
 
DevILImage** Material::getTextureImgAt(unsigned int idx){
	return textureImgs;
}