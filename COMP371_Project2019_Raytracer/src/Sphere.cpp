#include "Sphere.h"
#include <iostream>


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

void Sphere::toString()
{
	std::cout << "This Sphere has: " << std::endl;
	std::cout << "Position: " << position.x << " " << position.y << " " << position.z << std::endl;
	std::cout << "Radius: " << radius << std::endl;
	std::cout << "Ambient Color: " << ambientColor.x << " " << ambientColor.y << " " << ambientColor.z << std::endl;
	std::cout << "Diffuse Color: " << diffuseColor.x << " " << diffuseColor.y << " " << diffuseColor.z << std::endl;
	std::cout << "Specular Color: " << specularColor.x << " " << specularColor.y << " " << specularColor.z << std::endl;
	std::cout << "Shininess: " << shininess << std::endl;
}
