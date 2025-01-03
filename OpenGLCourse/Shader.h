#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "CommonValues.h"

class Shader
{
	public:
		Shader();
		~Shader();

		void CreateFromString(const char* vertexCode, const char* fragmentCode);
		void CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);

		std::string ReadFile(const char* fileLocation);

		GLuint GetModelLocation();
		GLuint GetProjectionLocation();
		GLuint GetViewLocation();
		GLuint GetAmbientIntensityLocation();
		GLuint GetAmbientColourLocation();
		GLuint GetDiffuseIntensityLocation();
		GLuint GetDirectionLocation();
		GLuint GetEyePositionLocation();
		GLuint GetSpecularIntensityLocation();
		GLuint GetShininessLocation();

		void SetDirectionalLight(DirectionalLight* dLight);
		void SetPointLights(PointLight* pLight, unsigned int lightCount);
		void SetSpotLights(SpotLight* sLight, unsigned int lightCount);

		void UseShader();
		void ClearShader();

	private:
		int pointLightCount;
		int spotLightCount;

		GLuint shaderID, uniformModel, uniformProjection, uniformView, uniformEyePosition,
					uniformSpecularIntensity, uniformShininess;

		struct {
			GLuint uniformColour;
			GLuint uniformAmbientIntensity;
			GLuint uniformDiffuseIntensity;

			GLuint uniformDirection;
		} uniformDirectionalLight;

		GLuint uniformPointLightCount;

		struct {
			GLuint uniformColour;
			GLuint uniformAmbientIntensity;
			GLuint uniformDiffuseIntensity;

			GLuint uniformPosition;
			GLuint uniformConstant;
			GLuint uniformLinear;
			GLuint uniformExponent;
		} uniformPointLight[MAX_POINT_LIGHTS];

		GLuint uniformSpotLightCount;

		struct {
			GLuint uniformColour;
			GLuint uniformAmbientIntensity;
			GLuint uniformDiffuseIntensity;

			GLuint uniformPosition;
			GLuint uniformConstant;
			GLuint uniformLinear;
			GLuint uniformExponent;

			GLuint uniformDirection;
			GLuint uniformEdge;
		} uniformSpotLight[MAX_SPOT_LIGHTS];


		void CompileShader(const char* vertexCode, const char* fragmentCode);
		void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
};

