#pragma once

#include "glm.hpp"
#include "Ray.h"
#include "Light.h"
#include "Sphere.h"
#include "Plane.h"
#include <string>
#include <vector>

class Mesh
{
private:
	std::string fileName;
	glm::vec3 ambientColor;
	glm::vec3 diffuseColor;
	glm::vec3 specularColor;
	float shininess;

	std::vector<int> indices;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> UVs;

public:
	Mesh();
	~Mesh();

	bool doesRayIntersect(Ray& ray, std::vector<int>& indices, std::vector<glm::vec3>& vertices, float& t, float& closestIndex);
	glm::vec3 calcColor(Ray& ray, Light& light, Plane& plane, std::vector<Sphere*>& spheres, Mesh& mesh, float& t, float& closestIndex);

	//Getters
	std::string getFileName();
	glm::vec3 getAmbientColor();
	glm::vec3 getDiffuseColor();
	glm::vec3 getSpecularColor();
	std::vector<int> getIndices();
	std::vector<glm::vec3> getVertices();
	std::vector<glm::vec3> getNormals();
	std::vector<glm::vec2> getUVS();
	float getShininess();

	//Setters
	void setFileName(std::string fileName);
	void setAmbientColor(glm::vec3 ambientColor);
	void setDiffuseColor(glm::vec3 diffuseColor);
	void setSpecularColor(glm::vec3 specularColor);
	void setShininess(float shininess);
	void setIndices(std::vector<int> indices);
	void setVertices(std::vector<glm::vec3> vertices);
	void setNormals(std::vector<glm::vec3> normals);
	void setUVS(std::vector<glm::vec2> UVs);

	void toString();
};

