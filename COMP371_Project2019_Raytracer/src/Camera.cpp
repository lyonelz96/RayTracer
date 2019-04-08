#include "Camera.h"
#include <iostream>


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

float Camera::getFOV()
{
	return fov;
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

void Camera::setFOV(float fov)
{
	this->fov = fov;
}

void Camera::setFocalLength(float focalLength)
{
	this->focalLength = focalLength;
}

void Camera::setAspectRatio(float aspectRatio)
{
	this->aspectRatio = aspectRatio;
}

void Camera::toString()
{
	std::cout << "This Camera has: " << std::endl;
	std::cout << "Position: " << position.x << " " << position.y << " " << position.z << std::endl;
	std::cout << "FOV: " << fov << std::endl;
	std::cout << "Focal Length: " << focalLength << std::endl;
	std::cout << "Aspect Ratio: " << aspectRatio << std::endl;
}
