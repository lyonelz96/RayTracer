#pragma once

#include "glm.hpp"

class Camera
{
private:
	glm::vec3 position;
	float theta;
	float focalLength;
	float aspectRatio;
public:
	Camera();
	~Camera();

	//Getters
	glm::vec3 getPosition();
	float getTheta();
	float getFocalLength();
	float getAspectRatio();

	//Setters
	void setPosition(glm::vec3 position);
	void setTheta(float theta);
	void setFocalLength(float focalLength);
	void setAspectRatio(float aspectRatio);

};

