#pragma once

#include <GL/glew.h>

class Material
{
public:
	Material();
	Material(GLfloat sIntensity, GLfloat shine);
	~Material();

	void SetAmbient(float r, float g, float b, float a);
	void SetDiffuse(float r, float g, float b, float a);
	void SetSpecular(float r, float g, float b, float a);
	void SetShininess(float shininess);

	void Apply();

private:
	GLfloat specularIntensity;
	GLfloat shininess;
};

