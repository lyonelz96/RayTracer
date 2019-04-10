#pragma once

#include "glm.hpp"
#include "Ray.h"
#include "Light.h"
#include <vector>
class Sphere;
class Mesh;


class Plane
{
private:
	glm::vec3 normal;
	glm::vec3 position;
	glm::vec3 ambientColor;
	glm::vec3 diffuseColor;
	glm::vec3 specularColor;
	float shininess;
public:
	Plane();
	~Plane();

	bool doesRayIntersect(Ray& ray, float& t);
	glm::vec3 calcColor(Ray& ray, Light& light, Plane& plane, std::vector<Sphere*>& spheres, Mesh& mesh, float& t);

	//Getters
	glm::vec3 getNormal();
	glm::vec3 getPosition();
	glm::vec3 getAmbientColor();
	glm::vec3 getDiffuseColor();
	glm::vec3 getSpecularColor();
	float getShininess();

	//Setters
	void setNormal(glm::vec3 normal);
	void setPosition(glm::vec3 position);
	void setAmbientColor(glm::vec3 ambientColor);
	void setDiffuseColor(glm::vec3 diffuseColor);
	void setSpecularColor(glm::vec3 specularColor);
	void setShininess(float shininess);

	void toString();

};

