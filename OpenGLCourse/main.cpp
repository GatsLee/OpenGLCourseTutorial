// OpenGLCourse.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cstdlib>

#include "Mesh.h"
#include "Shader.h"
#include "Window.h"
#include "Camera.h"
#include "Texture.h"

const float toRadians = 3.14159265f / 180.0f;

Window mainWindow;
std::vector <Mesh*> meshList;
std::vector <Shader> shaderList;
Camera camera;
Texture brickTexture;
Texture dirtTexture;

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

// Shaders Path
static const char* vShader = "../Shaders/shader.vert";
static const char* fShader = "../Shaders/shader.frag";

void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2 };

	GLfloat vertices[] = {
		// x, y, z,				u, v
		-1.0f, -1.0f, 0.0f,		0.0f, 0.0f,
		0.0f, -1.0f, 1.0f,		0.5f, 0.0f,
		1.0f, -1.0f, 0.0f,		1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,		0.5f, 1.0f
	};

	Mesh* testObj = new Mesh();
	testObj->CreateMesh(vertices, indices, 20, 12);
	meshList.push_back(testObj);

	Mesh* testObj2 = new Mesh();
	testObj2->CreateMesh(vertices, indices, 20, 12);
	meshList.push_back(testObj2);
}

void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}

int main()
{
	mainWindow = Window(800, 600);
	if (mainWindow.Initialize() == 1)
	{
		return 1;
	}

	CreateObjects();
	CreateShaders();

	camera = Camera(glm::abs(glm::vec3(0.0f, 0.0f, -2.0f)), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 1.0f, 0.5f);
	lastTime = glfwGetTime();

	dirtTexture = Texture("../Textures/dirt.png");
	if (!dirtTexture.LoadTexture())
	{
		return 1;
	}
	brickTexture = Texture("../Textures/brick.png");
	if (!brickTexture.LoadTexture())
	{
		return 1;
	}

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.GetBufferWidth() / (GLfloat)mainWindow.GetBufferHeight(), 0.1f, 100.0f);

	while (!mainWindow.GetShouldClose()) {
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		lastTime = now;

		glfwPollEvents();

		camera.KeyControl(mainWindow.GetKeys(), deltaTime);
		camera.MouseControl(mainWindow.GetXChange(), mainWindow.GetYChange());

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderList[0].UseShader();
		GLuint uniformModel = shaderList[0].GetModelLocation();
		GLuint uniformProjection = shaderList[0].GetProjectionLocation();
		GLuint uniformView = shaderList[0].GetViewLocation();

		glm::mat4 model(1.0f);

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.CalculateViewMatrix()));
		brickTexture.UseTexture();
		meshList[0]->RenderMesh();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, -2.5f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.CalculateViewMatrix()));
		dirtTexture.UseTexture();
		meshList[1]->RenderMesh();

		glUseProgram(0);

		mainWindow.SwapBuffers();
	}

	return 0;
}
