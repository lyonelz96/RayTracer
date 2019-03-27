#include "Sphere.h"



Sphere::Sphere()
{
}


Sphere::~Sphere()
{
}

glm::vec3 Sphere::getPosition()
{
	return position;
}

float Sphere::getRadius()
{
	return radius;
}

glm::vec3 Sphere::getAmbientColor()
{
	return ambientColor;
}

glm::vec3 Sphere::getDiffuseColor()
{
	return diffuseColor;
}

glm::vec3 Sphere::getSpecularColor()
{
	return specularColor;
}

float Sphere::getShininess()
{
	return shininess;
}

void Sphere::setPosition(glm::vec3 position)
{
	this->position = position;
}

void Sphere::setRadius(float radius)
{
	this->radius = radius;
}

void Sphere::setAmbientColor(glm::vec3 ambientColor)
{
	this->ambientColor = ambientColor;
}

void Sphere::setDiffuseColor(glm::vec3 diffuseColor)
{
	this->diffuseColor = diffuseColor;
}

void Sphere::setSpecularColor(glm::vec3 specularColor)
{
	this->specularColor = specularColor;
}

void Sphere::setShininess(float shininess)
{
	this->shininess = shininess;
}
