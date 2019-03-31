#pragma once

#include "glm.hpp"

class Light
{
private:
	glm::vec3 position;
	glm::vec3 diffuseColor;
	glm::vec3 specularColor;
public:
	Light();
	~Light();

	//Getters
	glm::vec3 getPosition();
	glm::vec3 getDiffuseColor();
	glm::vec3 getSpecularColor();

	//Setters
	void setPosition(glm::vec3 position);
	void setDiffuseColor(glm::vec3 diffuseColor);
	void setSpecularColor(glm::vec3 specularColor);

	void toString();
};