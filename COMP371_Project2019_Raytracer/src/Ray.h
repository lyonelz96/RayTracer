#pragma once

#include "glm.hpp"

class Ray
{

private:
	glm::vec3 origin; 
	glm::vec3 direction; // Direction 
	float t; // "How far" along the ray

public:
	Ray();
	~Ray();


	glm::vec3 calcPointAlongRay(float t);
	
	//Getters
	glm::vec3 getOrigin();
	glm::vec3 getDirection();
	float getDistance();

	//Setters
	void setOrigin(glm::vec3 origin);
	void setDirection(glm::vec3 direction);
	void setDistance(float t);
};

