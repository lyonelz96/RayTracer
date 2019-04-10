#include "Mesh.h"
#include <vector>
#include <iostream>


Mesh::Mesh()
{
}


Mesh::~Mesh()
{
}

bool Mesh::doesRayIntersect(Ray& ray,std::vector<int>& indices, std::vector<glm::vec3>& vertices, float& t)
{

	bool firstTriangleIntersected = false;
	float closestDistance = 0.0;
	float temp = 0.0;

	//For every triangle in the mesh we need to test if the ray intersects, then we pick the triangle that is closest
	for (int i = 0; i < indices.size(); i+=3) {
		glm::vec3 v0 = vertices[indices[i]];
		glm::vec3 v1 = vertices[indices[i + 1]];
		glm::vec3 v2 = vertices[indices[i + 2]];

		//Computing the planes normal
		glm::vec3 v0v1 = v1 - v0;
		glm::vec3 v0v2 = v2 - v0;
		glm::vec3 normal = glm::cross(v0v1, v0v2);
		float normalLength = glm::length(normal);

		//Check if ray and plane are parallel
		if (glm::dot(normal, ray.getDirection()) == 0)
			continue;

		t = (glm::dot(normal, ray.getOrigin()) + glm::dot(normal, v0)) / glm::dot(normal, ray.getDirection());

		//Triangle is behind
		if (t < 0)
		  continue;

		//Intersection Point
		glm::vec3 intersectionPoint = ray.getOrigin() + t * ray.getDirection();

		//Inside-Out Test
		glm::vec3 perpendicularToPlane;

		//First Edge
		glm::vec3 firstEdge = v1 - v0;
		glm::vec3 intersectV0 = intersectionPoint - v0;
		perpendicularToPlane = glm::cross(firstEdge, intersectV0);
		
		//Test if the intersection point is on the inside or outside
		if (glm::dot(normal, perpendicularToPlane) < 0)
			continue;

		//Second Edge
		glm::vec3 secondEdge = v2 - v1;
		glm::vec3 intersectV1 = intersectionPoint - v1;
		perpendicularToPlane = glm::cross(secondEdge, intersectV1);

		//Test if the intersection point is on the inside or outside
		if (glm::dot(normal, perpendicularToPlane) < 0)
			continue;

		//Third Edge
		glm::vec3 thirdEdge = v0 - v2;
		glm::vec3 intersectV2 = intersectionPoint - v2;
		perpendicularToPlane = glm::cross(thirdEdge, intersectV2);

		//Test if the intersection point is on the inside or outside
		if (glm::dot(normal, perpendicularToPlane) < 0)
			continue;

		if (firstTriangleIntersected == false) {
			closestDistance = t;
			firstTriangleIntersected = true;
		}
		else {
			if (t < closestDistance) {
				closestDistance = t;
			}
		}

	}

	if (firstTriangleIntersected == false) {
		return false;
	}
	else {
		t = closestDistance;
		return true;
	}
	
	
}

glm::vec3 Mesh::calcColor(Ray& ray, Light& light, Plane& plane, std::vector<Sphere*>& spheres, Mesh& mesh, float& t)
{
	//First we figure out if this point is in shadow or not
	glm::vec3 lightDir = (light.getPosition() - ray.calcPointAlongRay(t));
	float lightDistance = glm::pow(glm::length(lightDir), 2.0);

	Ray shadowRay;
	shadowRay.setOrigin(ray.calcPointAlongRay(t));
	shadowRay.setDirection(lightDir);

	float temp = t;
	for (int i = 0; i < spheres.size(); i++) {
		if (t <= lightDistance && spheres[i]->doesRayIntersect(shadowRay, temp))
			return this->getAmbientColor();
	}

	if (t <= lightDistance && plane.doesRayIntersect(shadowRay, temp)) {
		return this->getAmbientColor();
	}

	if ((&mesh != this) && t <= lightDistance && mesh.doesRayIntersect(shadowRay, indices, vertices, temp)) {
		return this->getAmbientColor();
	}

	//Ambient
	glm::vec3 ambient = this->ambientColor;

	/*
	//Diffuse
	glm::vec3 normal = glm::normalize(ray.calcPointAlongRay(t) - this->getPosition());
	lightDir = glm::normalize(lightDir);
	float diffuseStrength = glm::max(glm::dot(normal, lightDir), 0.0f);
	glm::vec3 diffuse = (diffuseStrength * this->getDiffuseColor()) * light.getDiffuseColor();
	*/

	/*
	//Specular
	glm::vec3 viewDir = glm::normalize(ray.getOrigin() - ray.calcPointAlongRay(t));
	glm::vec3 reflectDir = glm::normalize(glm::reflect(-lightDir, normal));
	float specularStrength = glm::pow(glm::max(glm::dot(viewDir, reflectDir), 0.0f), this->getShininess());
	glm::vec3 specular = (specularStrength * this->getSpecularColor()) * light.getSpecularColor();
	*/


	glm::vec3 result = ambient;


	return result;
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

std::vector<int> Mesh::getIndices()
{
	return indices;
}

std::vector<glm::vec3> Mesh::getVertices()
{
	return vertices;
}

std::vector<glm::vec3> Mesh::getNormals()
{
	return normals;
}

std::vector<glm::vec2> Mesh::getUVS()
{
	return UVs;
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

void Mesh::setIndices(std::vector<int> indices)
{
	this->indices = indices;
}

void Mesh::setVertices(std::vector<glm::vec3> vertices)
{
	this->vertices = vertices;
}

void Mesh::setNormals(std::vector<glm::vec3> normals)
{
	this->normals = normals;
}

void Mesh::setUVS(std::vector<glm::vec2> UVs)
{
	this->UVs = UVs;
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
