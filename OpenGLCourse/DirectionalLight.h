#pragma once
#include "Light.h"

class DirectionalLight : public Light
{
public:
	DirectionalLight();
	DirectionalLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity,
		GLfloat dIntensity, GLfloat xDir, GLfloat yDir, GLfloat zDir);
	~DirectionalLight();

	void UseLight(GLuint ambientIntensityLocation, GLuint ambientColorLocation,
		GLfloat diffuseIntensityLocation, GLfloat directionLocation);

private:
	glm::vec3 direction;
};

