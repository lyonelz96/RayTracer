#include "Plane.h"



Plane::Plane()
{
}


Plane::~Plane()
{
}

glm::vec3 Plane::getNormal()
{
	return normal;
}

glm::vec3 Plane::getPosition()
{
	return position;
}

glm::vec3 Plane::getAmbientColor()
{
	return ambientColor;
}

glm::vec3 Plane::getDiffuseColor()
{
	return diffuseColor;
}

glm::vec3 Plane::getSpecularColor()
{
	return specularColor;
}

float Plane::getShininess()
{
	return shininess;
}

void Plane::setNormal(glm::vec3 normal)
{
	this-> normal = normal;
}

void Plane::setPosition(glm::vec3 position)
{
	this->position = position;
}

void Plane::setAmbientColor(glm::vec3 ambientColor)
{
	this->ambientColor = ambientColor;
}

void Plane::setDiffuseColor(glm::vec3 diffuseColor)
{
	this->diffuseColor = diffuseColor;
}

void Plane::setSpecularColor(glm::vec3 specularColor)
{
	this->specularColor = specularColor;
}

void Plane::setShininess(float shininess)
{
	this->shininess = shininess;
}
