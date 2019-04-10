#include "Sphere.h"
#include "Plane.h"
#include"Mesh.h"
#include <iostream>
#include <vector>


Sphere::Sphere()
{
}


Sphere::~Sphere()
{
}

bool Sphere::doesRayIntersect(Ray& ray, float &t)
{
	/*
	Equation of a sphere: (x-xc)^2 + (y-yc)^2 + (z-zc)^2 - r^2 = 0
	If we take a point p = (x,y,z) and C = (xc,yc,zc)
	p - C = (x-xc, y-yc,z-zc)
	dot(p-C, p-C) = (x-xc)^2 + (y-yc)^2 + (z-zc)^2
	dot(p-C,p-C) = r^2, in other words if we can find a point p that satisfies this equation, then that point
	is on the sphere
	ray = p(t) = Origin + t*Direction 
	*/

	glm::vec3 sphereOC = ray.getOrigin() - this->getPosition(); //Origin - Center
	float a = glm::dot(ray.getDirection(), ray.getDirection()); //xd^2 + yd^2 + zd^2
	float b = 2.0 * glm::dot(sphereOC, ray.getDirection()); //2(xd(x0-xc)^2 + yd(y0-yc)^2 + zd(z0-zc)^2
	float c = glm::dot(sphereOC, sphereOC) - (this->getRadius() * this->getRadius()); //(x0-xc)^2 + (y0-yd)^2 + (z0-zd)^2 - r^2
	float discriminant = (b * b) - (4 * a*c);

	if (discriminant < 0.0) { // No roots
		return false;
	}
	else {
		//Either one or two roots
		float t0 = (-b - std::sqrt(discriminant)) / (2 * a);
		float t1 = (-b + std::sqrt(discriminant)) / (2 * a);

		if (t0 > 0.0 && t1 > 0.0) {
			t = std::fminf(t0, t1); // Get the closest intersection point
		}
		else if (t0 < 0.0) {
			t = t1; 
		}
		else if (t1 < 0.0) {
			t = t0;
		} 
		

		return true;
	}
}

glm::vec3 Sphere::calcColor(Ray& ray, Light& light, Plane& plane, std::vector<Sphere*>& spheres, Mesh& mesh, float& t)
{
	//First we figure out if this point is in shadow or not
	glm::vec3 lightDir = (light.getPosition() - ray.calcPointAlongRay(t));
	float lightDistance = glm::pow(glm::length(lightDir), 2.0);
	
	Ray shadowRay;
	shadowRay.setOrigin(ray.calcPointAlongRay(t));
	shadowRay.setDirection(lightDir);
	
	float temp = t;
	for (int i = 0; i < spheres.size(); i++) {
		if (spheres[i] != this && t <= lightDistance && spheres[i]->doesRayIntersect(shadowRay, temp))
			return this->getAmbientColor();
	}
	
	if (t <= lightDistance && plane.doesRayIntersect(shadowRay, temp) ) {
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
	glm::vec3 normal = glm::normalize(ray.calcPointAlongRay(t) - this->getPosition());
	lightDir = glm::normalize(lightDir);
	float diffuseStrength = glm::max(glm::dot(normal, lightDir), 0.0f);
	glm::vec3 diffuse = (diffuseStrength * this->getDiffuseColor()) * light.getDiffuseColor();
	
	//Specular
	glm::vec3 viewDir = glm::normalize(ray.getOrigin() - ray.calcPointAlongRay(t));
	glm::vec3 reflectDir = glm::normalize(glm::reflect(-lightDir, normal));
	float specularStrength = glm::pow(glm::max(glm::dot(viewDir, reflectDir), 0.0f), this->getShininess());
	glm::vec3 specular = (specularStrength * this->getSpecularColor()) * light.getSpecularColor();
	

	glm::vec3 result = ambient + diffuse + specular;

	
	return result;
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
