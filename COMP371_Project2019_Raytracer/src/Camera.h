#pragma once

#include "glm.hpp"

class Camera
{
private:
	glm::vec3 position;
	float fov;
	float focalLength;
	float aspectRatio;
public:
	Camera();
	~Camera();

	//Getters
	glm::vec3 getPosition();
	float getFOV();
	float getFocalLength();
	float getAspectRatio();

	//Setters
	void setPosition(glm::vec3 position);
	void setFOV(float fov);
	void setFocalLength(float focalLength);
	void setAspectRatio(float aspectRatio);

	void toString();

};

