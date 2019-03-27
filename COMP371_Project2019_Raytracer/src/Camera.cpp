#include "Camera.h"



Camera::Camera()
{
}


Camera::~Camera()
{
}

glm::vec3 Camera::getPosition()
{
	return position;
}

float Camera::getTheta()
{
	return theta;
}

float Camera::getFocalLength()
{
	return focalLength;
}

float Camera::getAspectRatio()
{
	return aspectRatio;
}

void Camera::setPosition(glm::vec3 position)
{
	this->position = position;
}

void Camera::setTheta(float theta)
{
	this->theta = theta;
}

void Camera::setFocalLength(float focalLength)
{
	this->focalLength = focalLength;
}

void Camera::setAspectRatio(float aspectRatio)
{
	this->aspectRatio = aspectRatio;
}
