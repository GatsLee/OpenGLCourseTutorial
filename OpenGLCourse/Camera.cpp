#include "Camera.h"

Camera::Camera()
{
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	this->yaw = -90.0f;
	this->pitch = 0.0f;
	front = glm::vec3(0.0f, 0.0f, -1.0f);

	movementSpeed = 3.0f;
	turnSpeed = 0.1f;

	Update();
}

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed)
{
	position = startPosition;
	worldUp = startUp;
	this->yaw = startYaw;
	this->pitch = startPitch;
	front = glm::vec3(0.0f, 0.0f, -1.0f);

	movementSpeed = startMoveSpeed;
	turnSpeed = startTurnSpeed;

	Update();
}

Camera::~Camera()
{
}

void Camera::KeyControl(bool* keys, GLfloat deltaTime)
{
	if (keys[GLFW_KEY_W])
	{
		position += front * movementSpeed * deltaTime;
	}
	if (keys[GLFW_KEY_S])
	{
		position -= front * movementSpeed * deltaTime;
	}
	if (keys[GLFW_KEY_A])
	{
		position -= right * movementSpeed * deltaTime;
	}
	if (keys[GLFW_KEY_D])
	{
		position += right * movementSpeed * deltaTime;
	}
	if (keys[GLFW_KEY_Q])
	{
		position -= up * movementSpeed * deltaTime;
	}
	if (keys[GLFW_KEY_E])
	{
		position += up * movementSpeed * deltaTime;
	}
	if (keys[GLFW_KEY_R])
	{
		pitch -= turnSpeed * deltaTime;
	}
	if (keys[GLFW_KEY_F])
	{
		pitch += turnSpeed * deltaTime;
	}

}

void Camera::MouseControl(GLfloat xChange, GLfloat yChange)
{
	xChange *= turnSpeed;
	yChange *= turnSpeed;

	yaw += xChange;
	pitch += yChange;

	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}
	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	Update();
}

glm::vec3 Camera::GetCameraPosition()
{
	return position;
}

glm::vec3 Camera::GetCameraDirection()
{
	return glm::normalize(front);
}

glm::mat4 Camera::CalculateViewMatrix()
{
	return glm::lookAt(position, position + front, up);
}

void Camera::Update()
{
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}