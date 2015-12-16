#include "Camera.h"
#include <cmath>
#include <iostream>

Camera::Camera(){
	near_plane = 1;
	far_plane = 20;

	sensor = new Sensor();
	lens = new Lens();
	
	eye=QVector3D(0,0,0);
	center=QVector3D(0,0,-1);
	up=QVector3D(0,1,0);
	
	updateViewMatrix();
	updateProjectionMatrix();
}

Camera::Camera(float near, float far){
	near_plane = near;
	far_plane = far;
	
	sensor = new Sensor();
	lens = new Lens();

	eye=QVector3D(0,0,-1);
	center=QVector3D(0,0,0);
	up=QVector3D(0,1,0);
	
	updateViewMatrix();
	updateProjectionMatrix();

	std::cout << "Setting fovy to " << getFovy() << std::endl;
}

Camera::~Camera(){
	if (sensor){
		delete sensor;
		sensor = NULL;
	}
	if (lens){
		delete lens;
		lens = NULL;
	}
}

void Camera::getPlaneDimensions(float z, QVector3D& top_left, QVector3D& bottom_right){
	float np = getNearPlane();
	float fp = getFarPlane();
	if(z > fp || z < np){
		/*top_left.setX(0); top_left.setY(0); top_left.setZ(0);
		bottom_right.setX(0); bottom_right.setY(0); bottom_right.setZ(0);
		return;*/
		throw 1;
	}

	float half_plane_height = tan( degToRad(getFovy() / 2.0f) ) * z;
	float half_plane_width = tan( degToRad(getFovy() / 2.0f) ) * getAspectRatio() * z;

	QVector3D line_of_sight = center - eye;

	QVector3D plane_center = eye + line_of_sight * fabs(z);

	top_left.setX(plane_center.x() - half_plane_width);
	top_left.setY(plane_center.y() + half_plane_height);
	top_left.setZ(plane_center.z());

	bottom_right.setX(plane_center.x() + half_plane_width);
	bottom_right.setY(plane_center.y() - half_plane_height);
	bottom_right.setZ(plane_center.z());
}

float Camera::getFocussedDistance(){
	return lens->getFocalDistance() * lens->getSensorDistance() / (lens->getSensorDistance() - lens->getFocalDistance());
}

float Camera::calcCoC(float d){
	//Object distance
	float od = abs(d);
	
	//Focussed distance
	float fd = getFocussedDistance();
	float f = lens->getFocalDistance();

	//CoC
	float c = abs(od - fd) * f * f / (od * (fd - f) * lens->getFNum()); // in mm
	
	return c / sensor->getPixelSize() * 1000.0f; // in px
}

void Camera::updateProjectionMatrix(){
	proj_mat.setToIdentity(); 
	proj_mat.perspective(getFovy(), getAspectRatio(), near_plane, far_plane);
}

void Camera::updateViewMatrix(){
	view_mat.setToIdentity(); 
	view_mat.lookAt(eye, center, up);
}