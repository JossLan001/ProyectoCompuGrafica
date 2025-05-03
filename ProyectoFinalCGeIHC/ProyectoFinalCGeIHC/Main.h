#pragma once

#include <iostream>
#include <cmath>

// GLEW.
#include <GL/glew.h>

// GLFW.
#include <GLFW/glfw3.h>

// GLM Mathematics.
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Load Models.
#include "SOIL2/SOIL2.h"

// Other Libs.
#include "stb_image.h"

// Other includes.
#include "Shader.h"
#include "Model.h"
#include "Camera.h"
#include "Personaje.h"

// Deltatime.
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame.
GLfloat lastFrame = 0.0f;  	// Time of last frame.

// Window Dimensions.
const GLuint WIDTH = 1920, HEIGHT = 1080;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Cámara.
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
glm::vec3 posicionCamara = glm::vec3(0.0f);
glm::vec3 objetivoCamara = glm::vec3(0.0f);
glm::vec3 upCamara = glm::vec3(0.0f, 1.0f, 0.0f);
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;
bool camaraEstatica = false;
bool camaraArriba = false;

// Definición de Funciones.
// Teclas y Mouse.
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);

// Modo de Camara.
glm::mat4 ModoCamara();

// Iluminación.
void DibujarLuces(Shader& lightingShader);
void CicloDiaNoche(float deltaTime);

// Controlador de Movimiento.
void MoverHarley();

// Controladores de Animación.
void ChecarMovimiento();
void AnimarHarley();
void AnimarJuego();
void TerminarJuego();

// Ciclo día y noche.
glm::vec3 direccionLuz = glm::vec3(0.0f, -1.0f, 0.0f); // Dirección de la luz.
float angulo = 0.0f; // Ángulo de la luz.
float radianes = 0.0f; // Ángulo convertido a radianes.
float intensidadLuz = 0.0f; // Intensidad de la luz.
float tiempoDia = 0.0f; // Lleva la cuenta del tiempo transcurrido.
const float DURACION_DIA = 180.0f; // Duración de día de 180 segundos.
glm::vec3 colorCielo = glm::vec3(0.0f); // Color actual del cielo.
glm::vec3 colorCieloDia = glm::vec3(0.5f, 0.9f, 1.0f); // Color azul cielo.
glm::vec3 colorCieloNoche = glm::vec3(0.0f, 0.0f, 0.1f); // Color negro.

// Personajes.
Personaje harley;

// Elementos Interactivos.
bool jugando = false;
int juegoActivo = 0;

glm::vec3 posicionStandBateo = glm::vec3(-5.0f, 0.0f, -5.0f); // Puesto donde el jugador inicia la interacción de bateo.
glm::vec3 posicionJaulaBateo = glm::vec3(-5.0f, 0.0f, -17.5f); // Posición de la jaula de bateo.

glm::vec3 posicionStandTopos = glm::vec3(0.0f, 0.0f, 0.0f); // Puesto donde el jugador inicia la interacción de topos.
glm::vec3 posicionMaquinaTopos = glm::vec3(0.0f, 0.0f, 0.0f); // Posición de la maquina de topos.

glm::vec3 posicionStandHachas = glm::vec3(0.0f, 0.0f, 0.0f); // Puesto donde el jugador inicia la interacción de hachas.
glm::vec3 posicionCabinaHachas = glm::vec3(0.0f, 0.0f, 0.0f); // Posición de la cabina de hachas.

glm::vec3 posicionStandBoliche = glm::vec3(0.0f, 0.0f, 0.0f); // Puesto donde el jugador inicia la interacción de boliche.
glm::vec3 posicionPistaBoliche = glm::vec3(0.0f, 0.0f, 0.0f); // Posición de la pista de boliche.

glm::vec3 posicionStandDados = glm::vec3(0.0f, 0.0f, 0.0f); // Puesto donde el jugador inicia la interacción de dados.
glm::vec3 posicionMesaDados = glm::vec3(0.0f, 0.0f, 0.0f); // Posición de la mesa de dados.

glm::vec3 posicionStandDardos = glm::vec3(0.0f, 0.0f, 0.0f); // Puesto donde el jugador inicia la interacción de dardos.
glm::vec3 posicionPuestoDardos = glm::vec3(0.0f, 0.0f, 0.0f); // Posición del puesto de dardos.

glm::vec3 posicionInteraccion = glm::vec3(0.0f); // Guarda la posición donde el personaje insertó el ticket para regresar al terminar la interacción.

// Is called whenever a key is pressed/released via GLFW.
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}
	}

	if (key == GLFW_KEY_P && action == GLFW_PRESS && not jugando)
	{
		camaraArriba = not camaraArriba;
		posicionCamara = glm::vec3(0.0f, 40.0f, 0.0f);
		objetivoCamara = glm::vec3(0.0f, 0.0f, 0.0f);
		if (camaraArriba) {
			upCamara = glm::vec3(0.0f, 0.0f, -1.0f);
		}
		else {
			upCamara = glm::vec3(0.0f, 1.0f, 0.0f);
		}
		camaraEstatica = !camaraEstatica;
	}

	if (keys[GLFW_KEY_E])
	{
		float apotema = 2.0f; // Rango en el que se puede interactuar con un puesto de tickets.
		if (harley.posicion.x > posicionStandBateo.x - apotema && harley.posicion.x < posicionStandBateo.x + apotema && harley.posicion.z > posicionStandBateo.x - apotema && harley.posicion.z < posicionStandBateo.x + apotema) {
			jugando = true;
			posicionCamara = posicionStandBateo + glm::vec3(2.0f, 4.0f, -4.0f);;
			objetivoCamara = posicionJaulaBateo;
			camaraEstatica = !camaraEstatica;

			posicionInteraccion = harley.posicion;
			harley.posicion = posicionJaulaBateo + glm::vec3(0.0f, 1.02f, 0.0f);
			harley.rotacion = glm::vec3(0.0f, 0.0f, 0.0f);
			harley.ComenzarBateo();
			juegoActivo = 1;
		}
		else if (harley.posicion.x > posicionStandTopos.x - apotema && harley.posicion.x < posicionStandTopos.x + apotema && harley.posicion.z > posicionStandTopos.x - apotema && harley.posicion.z < posicionStandTopos.x + apotema)
		{

		}
		else if (harley.posicion.x > posicionStandHachas.x - apotema && harley.posicion.x < posicionStandHachas.x + apotema && harley.posicion.z > posicionStandHachas.x - apotema && harley.posicion.z < posicionStandHachas.x + apotema)
		{

		}
		else if (harley.posicion.x > posicionStandBoliche.x - apotema && harley.posicion.x < posicionStandBoliche.x + apotema && harley.posicion.z > posicionStandBoliche.x - apotema && harley.posicion.z < posicionStandBoliche.x + apotema)
		{

		}
		else if (harley.posicion.x > posicionStandDados.x - apotema && harley.posicion.x < posicionStandDados.x + apotema && harley.posicion.z > posicionStandDados.x - apotema && harley.posicion.z < posicionStandDados.x + apotema)
		{

		}
		else if (harley.posicion.x > posicionStandDardos.x - apotema && harley.posicion.x < posicionStandDardos.x + apotema && harley.posicion.z > posicionStandDardos.x - apotema && harley.posicion.z < posicionStandDardos.x + apotema)
		{

		}
	}
}

void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left.

	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xOffset, yOffset);
}

glm::mat4 ModoCamara()
{
	camera.target = harley.posicion;
	camera.updateCameraVectors();

	if (camaraEstatica)
	{
		return glm::lookAt(
			posicionCamara,
			objetivoCamara,
			upCamara
		);
	}
	else
	{
		return camera.GetViewMatrix();  // Modo Tercera Persona.
	}
}

void DibujarLuces(Shader& lightingShader)
{
	// Directional light.
	glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), direccionLuz.x, direccionLuz.y, direccionLuz.z);
	glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"), 0.25 + intensidadLuz * 0.25, 0.25 + intensidadLuz * 0.25, 0.25 + intensidadLuz * 0.25);
	glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.25 + intensidadLuz * 0.25, 0.25 + intensidadLuz * 0.25, 0.25 + intensidadLuz * 0.25);
	glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"), intensidadLuz * 0.25f, intensidadLuz * 0.25f, intensidadLuz * 0.25f);


	// Point light 1.
	glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), 0.0f, 0.0f, 0.0f);
	glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), 0.0f, 0.0f, 0.0f);
	glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), 0.0f, 0.0f, 0.0f);
	glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), 0.0f, 0.0f, 0.0f);
	glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
	glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.045f);
	glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 0.075f);

	// Point light 2.
	glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].position"), 0.0f, 0.0f, 0.0f);
	glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].ambient"), 0.0f, 0.0f, 0.0f);
	glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].diffuse"), 0.0f, 0.0f, 0.0f);
	glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].specular"), 0.0f, 0.0f, 0.0f);
	glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].constant"), 1.0f);
	glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].linear"), 0.045f);
	glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].quadratic"), 0.075f);

	// Point light 3.
	glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].position"), 0.0f, 0.0f, 0.0f);
	glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].ambient"), 0.0f, 0.0f, 0.0f);
	glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].diffuse"), 0.0f, 0.0f, 0.0f);
	glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].specular"), 0.0f, 0.0f, 0.0f);
	glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].constant"), 1.0f);
	glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].linear"), 0.045f);
	glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].quadratic"), 0.075f);

	// Point light 4.
	glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].position"), 0.0f, 0.0f, 0.0f);
	glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].ambient"), 0.0f, 0.0f, 0.0f);
	glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].diffuse"), 0.0f, 0.0f, 0.0f);
	glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].specular"), 0.0f, 0.0f, 0.0f);
	glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].constant"), 1.0f);
	glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].linear"), 0.045f);
	glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].quadratic"), 0.075f);

	// SpotLight.
	glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.position"), 0.0f, 0.0f, 0.0f);
	glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.direction"), 0.0f, 0.0f, 0.0f);
	glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.ambient"), 0.0f, 0.0f, 0.0f);
	glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.diffuse"), 0.0f, 0.0f, 0.0f);
	glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.specular"), 0.0f, 0.0f, 0.0f);
	glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.constant"), 1.0f);
	glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.linear"), 0.0f);
	glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.quadratic"), 0.0f);
	glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(32.0f)));
	glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(40.0f)));
}

void CicloDiaNoche(float deltaTime)
{
	// Ciclo de día y noche.
	tiempoDia += deltaTime; // Avanza el ciclo.

	// Si se completa el ciclo, reiniciar.
	if (tiempoDia >= DURACION_DIA)
	{
		tiempoDia = 0.0f;
	}

	// Calcula el ángulo actual del ciclo (0 a 360 grados).
	angulo = (tiempoDia / DURACION_DIA) * 360.0f;

	// Convierte a radianes.
	radianes = glm::radians(angulo);

	// Simula la dirección de la luz (sol girando alrededor del escenario).
	direccionLuz.x = cos(radianes);
	direccionLuz.y = sin(radianes);

	// Calcula la intensidad de la luz en función del "altura" del sol.
	intensidadLuz = glm::clamp(sin(radianes), 0.0f, 1.0f);  // 0.0 en noche, 1.0 en mediodía.
	intensidadLuz = 1.0 - intensidadLuz;

	// Calcula la mezcla entre día y noche.
	colorCielo = glm::mix(colorCieloNoche, colorCieloDia, intensidadLuz);
}

void MoverHarley()
{
	glm::vec3 front = camera.GetFront();
	front.y = 0.0f;
	front = glm::normalize(front);

	glm::vec3 right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));

	float speed = 2.5f * deltaTime;
	glm::vec3 movimiento(0.0f);

	if (keys[GLFW_KEY_W])
		movimiento += front;

	if (keys[GLFW_KEY_S])
		movimiento -= front;

	if (keys[GLFW_KEY_A])
		movimiento -= right;

	if (keys[GLFW_KEY_D])
		movimiento += right;

	if (glm::length(movimiento) > 0.0f)
	{
		movimiento = glm::normalize(movimiento);
		harley.posicion += movimiento * speed;

		// Calcular ángulo en Y desde la dirección del movimiento.
		float angle = glm::degrees(atan2(movimiento.x, movimiento.z));
		harley.rotacion.y = angle;
	}

	if (harley.caminando)
	{
		harley.Caminar(deltaTime);
	}

}

void ChecarMovimiento()
{
	if (harley.posicion != harley.posicionAnterior)
	{
		// Está caminando.
		if (not harley.caminando && not jugando)
		{
			harley.ComenzarCaminata();
		}
	}
	else
	{
		// Está quieta.
		if (harley.caminando && not jugando)
		{
			harley.PoseIdle();
			harley.caminando = false;
		}
	}
	harley.posicionAnterior = harley.posicion;
}

void AnimarHarley()
{
	if (not jugando) {
		ChecarMovimiento();
		MoverHarley();
	}
	else {
		AnimarJuego();
	}
}

void AnimarJuego()
{
	switch (juegoActivo)
	{
	case 1:
		harley.Batear(deltaTime);
	case 2:
		break;
	default:
		break;
	}
}

void TerminarJuego()
{
	camaraEstatica = false;
	jugando = false;
	harley.PoseIdle();
	harley.posicion = posicionInteraccion;
}