#include "Light.h"



Light::Light()
{
}


Light::~Light()
{
}

glm::vec3 Light::getPosition()
{
	return position;
}

glm::vec3 Light::getDiffuseColor()
{
	return diffuseColor;
}

glm::vec3 Light::getSpecularColor()
{
	return specularColor;
}

void Light::setPosition(glm::vec3 position)
{
	this->position = position;
}

void Light::setDiffuseColor(glm::vec3 diffuseColor)
{
	this->diffuseColor = diffuseColor;
}

void Light::setSpecularColor(glm::vec3 specularColor)
{
	this->specularColor = specularColor;
}
