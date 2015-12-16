#pragma once

#include <il.h>
#include <string>
#include <iostream>

class DevILImage
{
public:
	int type;
	int width;
	int height;
	int format;
	ILubyte *data;
	DevILImage();
	DevILImage(ILstring path);
	~DevILImage(void);
};

