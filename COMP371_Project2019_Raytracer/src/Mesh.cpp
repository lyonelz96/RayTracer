#include "Mesh.h"
#include <iostream>


Mesh::Mesh()
{
}


Mesh::~Mesh()
{
}

std::string Mesh::getFileName()
{
	return fileName;
}

glm::vec3 Mesh::getAmbientColor()
{
	return ambientColor;
}

glm::vec3 Mesh::getDiffuseColor()
{
	return diffuseColor;
}

glm::vec3 Mesh::getSpecularColor()
{
	return specularColor;
}

float Mesh::getShininess()
{
	return shininess;
}

void Mesh::setFileName(std::string fileName)
{
	this->fileName = fileName;
}

void Mesh::setAmbientColor(glm::vec3 ambientColor)
{
	this->ambientColor = ambientColor;
}

void Mesh::setDiffuseColor(glm::vec3 diffuseColor)
{
	this->diffuseColor = diffuseColor;
}

void Mesh::setSpecularColor(glm::vec3 specularColor)
{
	this->specularColor = specularColor;
}

void Mesh::setShininess(float shininess)
{
	this->shininess = shininess;
}

void Mesh::toString()
{
	std::cout << "This Mesh has: " << std::endl;
	std::cout << "FileName: " << fileName << std::endl;
	std::cout << "Ambient Color: " << ambientColor.x << " " << ambientColor.y << " " << ambientColor.z << std::endl;
	std::cout << "Diffuse Color: " << diffuseColor.x << " " << diffuseColor.y << " " << diffuseColor.z << std::endl;
	std::cout << "Specular Color: " << specularColor.x << " " << specularColor.y << " " << specularColor.z << std::endl;
	std::cout << "Shininess: " << shininess << std::endl;
}
