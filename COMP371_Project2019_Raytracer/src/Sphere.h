#pragma once
	
#include "glm.hpp"
	
class Sphere
{
private:
	glm::vec3 position;
	float radius;
	glm::vec3 ambientColor;
	glm::vec3 diffuseColor;
	glm::vec3 specularColor;
	float shininess;
public:
	Sphere();
	~Sphere();

	//Getters
	glm::vec3 getPosition();
	float getRadius();
	glm::vec3 getAmbientColor();
	glm::vec3 getDiffuseColor();
	glm::vec3 getSpecularColor();
	float getShininess();

	//Setters
	void setPosition(glm::vec3 position);
	void setRadius(float radius);
	void setAmbientColor(glm::vec3 ambientColor);
	void setDiffuseColor(glm::vec3 diffuseColor);
	void setSpecularColor(glm::vec3 specularColor);
	void setShininess(float shininess);

	void toString();
};

