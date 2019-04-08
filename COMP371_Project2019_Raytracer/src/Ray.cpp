#include "Ray.h"



Ray::Ray()
{
}


Ray::~Ray()
{
}

glm::vec3 Ray::calcPointAlongRay(float t)
{
	return origin + t * direction;
}

glm::vec3 Ray::getOrigin()
{
	return origin;
}

glm::vec3 Ray::getDirection()
{
	return direction;
}

float Ray::getDistance()
{
	return t;
}

void Ray::setOrigin(glm::vec3 origin)
{
	this->origin = origin;
}

void Ray::setDirection(glm::vec3 direction)
{
	this->direction = glm::normalize(direction);
}

void Ray::setDistance(float t)
{
	this->t = t;
}
