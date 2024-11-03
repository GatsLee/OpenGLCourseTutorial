#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

class Light
{
public:
	Light();
	Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, 
		GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat dIntensity);
	~Light();

	void UseLight(GLuint ambientIntensityLocation, GLuint ambientColorLocation,
					GLfloat diffuseIntensityLocation, GLfloat directionLocation);

private:
	GLfloat ambientIntensity;

	glm::vec3 colour;

	glm::vec3 direction;
	GLfloat diffuseIntensity;
};

