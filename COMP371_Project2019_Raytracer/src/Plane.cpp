#include "Plane.h"
#include <iostream>
#include "Sphere.h"
#include <vector>


Plane::Plane()
{
}


Plane::~Plane()
{
}

bool Plane::doesRayIntersect(Ray& ray, float& t)
{
	//No intersection, ray parallel to plane
	if (glm::dot(ray.getDirection(), normal) == 0.0) {
		return false;
	}

	
	t = (glm::dot((position - ray.getOrigin()),glm::normalize(normal))) / (glm::dot(ray.getDirection(), glm::normalize(normal)));

	//Behind ray origin
	if (t <= 0) {
		return false;
	}
	else {
		return true;
	}

	
}

glm::vec3 Plane::calcColor(Ray& ray, Light& light, Plane& plane, std::vector<Sphere*>& spheres, Mesh& mesh, float& t)
{
	//First we figure out if this point is in shadow or not
	glm::vec3 lightDir = (light.getPosition() - ray.calcPointAlongRay(t));
	float lightDistance = glm::pow(glm::length(lightDir), 2.0);

	Ray shadowRay;
	shadowRay.setOrigin(ray.calcPointAlongRay(t));
	shadowRay.setDirection(lightDir);

	float temp = t;
	for (int i = 0; i < spheres.size(); i++) {
		if (t <= lightDistance && spheres[i]->doesRayIntersect(shadowRay, temp) ) {
			return this->getAmbientColor();
		}
	}

	if ((&plane != this) && t <= lightDistance && plane.doesRayIntersect(shadowRay, temp) ) {
		return this->getAmbientColor();
	}

	std::vector<int> indices = mesh.getIndices();
	std::vector<glm::vec3> vertices = mesh.getVertices();

	if (t <= lightDistance && mesh.doesRayIntersect(shadowRay, indices, vertices, temp)) {
		return this->getAmbientColor();
	}

	//Ambient
	glm::vec3 ambient = this->ambientColor;

	//Diffuse
	glm::vec3 normal = glm::normalize(this->getNormal());
	lightDir = glm::normalize(lightDir);
	float diffuseStrength = glm::max(glm::dot(normal, lightDir), 0.0f);
	glm::vec3 diffuse = (diffuseStrength * this->getDiffuseColor()) * light.getDiffuseColor();

	//Specular
	glm::vec3 viewDir = glm::normalize(ray.getOrigin() - ray.calcPointAlongRay(t));
	glm::vec3 reflectDir = glm::normalize(glm::reflect(-lightDir, normal));
	float specularStrength = glm::pow(glm::max(glm::dot(viewDir, reflectDir), 0.0f), this->getShininess());
	glm::vec3 specular = (specularStrength * this->getSpecularColor()) * light.getSpecularColor();

	glm::vec3 result = (ambient + diffuse + specular);

	return result;
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
