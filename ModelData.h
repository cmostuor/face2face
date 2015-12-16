#ifndef ModelDataH
#define ModelDataH

#include <QMatrix4x4>

float vertex_data[] = 
{	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f
};

int indices_data[] = 
{	0, 1, 2, 
	0, 2, 3,
	3, 2, 6,
	3, 6, 7,
	7, 6, 5,
	7, 5, 4,
	12, 8, 11,
	12, 11, 15,
	12, 13, 9,
	12, 9, 8,
	9, 13, 14,
	9, 14, 10
};

float tex_c[] = {
    // First three faces
    0.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f,
	1.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,
	0.0f, 0.0f,

	// Second three faces
    1.0f, 1.0f,
    0.0f, 1.0f,
    1.0f, 1.0f,
	0.0f, 1.0f,
	1.0f, 0.0f,
	0.0f, 0.0f,
	1.0f, 0.0f,
	0.0f, 0.0f,
};

QMatrix4x4 modelMatrix;

#endif