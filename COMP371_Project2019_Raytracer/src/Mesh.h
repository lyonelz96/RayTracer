#pragma once

#include "glm.hpp"
#include <string>

class Mesh
{
private:
	std::string fileName;
	glm::vec3 ambientColor;
	glm::vec3 diffuseColor;
	glm::vec3 specularColor;
	float shininess;

public:
	Mesh();
	~Mesh();

	//Getters
	std::string getFileName();
	glm::vec3 getAmbientColor();
	glm::vec3 getDiffuseColor();
	glm::vec3 getSpecularColor();
	float getShininess();

	//Setters
	void setFileName(std::string fileName);
	void setAmbientColor(glm::vec3 ambientColor);
	void setDiffuseColor(glm::vec3 diffuseColor);
	void setSpecularColor(glm::vec3 specularColor);
	void setShininess(float shininess);
};

