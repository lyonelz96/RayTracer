#include "Light.h"
#include <iostream>



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

void Light::toString()
{
	std::cout << "This Light has: " << std::endl;
	std::cout << "Position: " << position.x << " " << position.y << " " << position.z << std::endl;
	std::cout << "Diffuse Color: " << diffuseColor.x << " " << diffuseColor.y << " " << diffuseColor.z << std::endl;
	std::cout << "Specular Color: " << specularColor.x << " " << specularColor.y << " " << specularColor.z << std::endl;
}
