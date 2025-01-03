#include "Material.h"

Material::Material()
{
	this->specularIntensity = 0.0f;
	this->shininess = 0.0f;
}

Material::Material(GLfloat sIntensity, GLfloat shine)
{
	this->specularIntensity = sIntensity;
	this->shininess = shine;
}

Material::~Material()
{
}

void Material::UseMaterial(GLuint specularIntensityLocation, GLuint shininessLocation)
{
	glUniform1f(specularIntensityLocation, this->specularIntensity);
	glUniform1f(shininessLocation, this->shininess);
}
