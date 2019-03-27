#include "Mesh.h"



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
