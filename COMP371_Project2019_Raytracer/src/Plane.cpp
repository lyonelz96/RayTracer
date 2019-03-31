#include "Plane.h"
#include <iostream>


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

void Plane::toString()
{
	std::cout << "This Plane has: " << std::endl;
	std::cout << "Normal: " << normal.x << " " << normal.y << " " << normal.z << std::endl;
	std::cout << "Position: " << position.x << " " << position.y << " " << position.z << std::endl;
	std::cout << "Ambient Color: " << ambientColor.x << " " << ambientColor.y << " " << ambientColor.z << std::endl;
	std::cout << "Diffuse Color: " << diffuseColor.x << " " << diffuseColor.y << " " << diffuseColor.z << std::endl;
	std::cout << "Specular Color: " << specularColor.x << " " << specularColor.y << " " << specularColor.z << std::endl;
	std::cout << "Shininess: " << shininess << std::endl;
}
