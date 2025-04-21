#pragma once

// Std. Includes
#include <vector>

// GL Includes
#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

// Default camera values
const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 6.0f;
const GLfloat SENSITIVTY = 0.25f;
const GLfloat ZOOM = 45.0f;

// An orbital camera class that rotates around a target point
class Camera
{
public:
	glm::vec3 target = glm::vec3(0.0f); // Punto central de la órbita
	float distanceToTarget = 10.0f;     // Distancia de la cámara al objetivo

	// Constructor with vectors
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = YAW, GLfloat pitch = PITCH)
		: front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVTY), zoom(ZOOM)
	{
		this->target = glm::vec3(0.0f);
		this->distanceToTarget = glm::length(position - target);
		this->worldUp = up;
		this->yaw = yaw;
		this->pitch = pitch;
		this->updateCameraVectors();
	}

	// Constructor with scalar values
	Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch)
		: front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVTY), zoom(ZOOM)
	{
		this->target = glm::vec3(0.0f);
		this->position = glm::vec3(posX, posY, posZ);
		this->distanceToTarget = glm::length(position - target);
		this->worldUp = glm::vec3(upX, upY, upZ);
		this->yaw = yaw;
		this->pitch = pitch;
		this->updateCameraVectors();
	}

	glm::mat4 GetViewMatrix()
	{
		return glm::lookAt(this->position, target, this->up);
	}

	void ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime)
	{
		// Movimiento del objetivo (opcional)
		GLfloat velocity = this->movementSpeed * deltaTime;

		if (direction == FORWARD)
			target += this->front * velocity;
		if (direction == BACKWARD)
			target -= this->front * velocity;
		if (direction == LEFT)
			target -= this->right * velocity;
		if (direction == RIGHT)
			target += this->right * velocity;

		updateCameraVectors();
	}

	void ProcessMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch = true)
	{
		xOffset *= this->mouseSensitivity;
		yOffset *= this->mouseSensitivity;

		this->yaw += xOffset;
		this->pitch -= yOffset;

		// Limita pitch
		if (constrainPitch)
		{
			if (this->pitch > 89.0f)
				this->pitch = 89.0f;
			if (this->pitch < -89.0f)
				this->pitch = -89.0f;
		}

		updateCameraVectors();
	}

	void ProcessMouseScroll(GLfloat yOffset)
	{
		distanceToTarget -= yOffset;
		if (distanceToTarget < 2.0f)
			distanceToTarget = 2.0f;
		if (distanceToTarget > 80.0f)
			distanceToTarget = 80.0f;

		updateCameraVectors();
	}

	void updateCameraVectors()
	{
		// Conversión esférica a cartesianas para rotar alrededor del objetivo
		float x = distanceToTarget * cos(glm::radians(pitch)) * cos(glm::radians(yaw));
		float y = distanceToTarget * sin(glm::radians(pitch));
		float z = distanceToTarget * cos(glm::radians(pitch)) * sin(glm::radians(yaw));

		position = target + glm::vec3(x, y, z);
		front = glm::normalize(target - position);
		right = glm::normalize(glm::cross(front, worldUp));
		up = glm::normalize(glm::cross(right, front));
	}

	GLfloat GetZoom() { return this->zoom; }
	glm::vec3 GetPosition() { return this->position; }
	glm::vec3 GetFront() { return this->front; }

private:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	GLfloat yaw;
	GLfloat pitch;

	GLfloat movementSpeed;
	GLfloat mouseSensitivity;
	GLfloat zoom;

};
