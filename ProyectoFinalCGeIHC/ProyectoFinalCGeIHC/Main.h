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

//Dibujo de Estructuras
void DibujarEstructura(GLuint modelLoc, Shader& lightingShader, Model estructura, glm::vec3 posicionEstructura, float rotacionEstructura);

// Iluminación.
void DibujarLuces(Shader& lightingShader);
void CicloDiaNoche(float deltaTime);
void RevisarHora();

// Controlador de Movimiento.
void MoverHarley();

// Controladores de Animación.
void ChecarMovimiento();

//Control de Interacciones
void PagarJuego(int juego);
void ComenzarJuego(int juego);
void AnimarJuego(GLuint modelLoc, Shader& lightingShader, Model objetos[]);
void TerminarJuego();

bool caminando = false;

// Lanzamiento de Objetos.
void ReiniciarObjeto();
void LanzarObjeto(glm::vec3 direccionLanzamiento, float velocidadLanzamiento, float gradosRotacion, float tiempoVueloMaximo);
void DibujarObjeto(GLuint modelLoc, Shader& lightingShader, Model objeto);

glm::vec3 posicionObjeto = glm::vec3(0.0f);
glm::vec3 rotacionObjeto = glm::vec3(0.0f);
float tiempoVuelo;

// Ciclo día y noche.
glm::vec3 direccionLuz = glm::vec3(0.0f, -1.0f, 0.0f); // Dirección de la luz.
float angulo = 0.0f; // Ángulo de la luz.
float radianes = 0.0f; // Ángulo convertido a radianes.
float intensidadLuz = 0.0f; // Intensidad de la luz.
float intensidadLuzInversa = 0.0f; // Inversa de la intensidad de la luz.
float tiempoDia = 0.0f; // Lleva la cuenta del tiempo transcurrido.
const float DURACION_DIA = 300.0f; // Duración de día de 180 segundos.
glm::vec3 colorCielo = glm::vec3(0.0f); // Color actual del cielo.
glm::vec3 colorCieloDia = glm::vec3(0.5f, 0.9f, 1.0f); // Color azul cielo.
glm::vec3 colorCieloNoche = glm::vec3(0.0f, 0.0f, 0.1f); // Color negro.
bool esNoche = false;
float luzAutomatica = 0.0f;

//Luces controladas por el usuario.
float luzPrendida = 1.0f;

// Personajes.
Personaje harley;
Personaje purohueso;

// Elementos Interactivos.
float tiempoInteraccion = 0.0f;
float maxTiempoInteraccion = 5.0f;
bool pagando = false;
bool jugando = false;
int juegoActivo = 0;
int accesorioActivo = 0;
glm::vec3 posicionInteraccion = glm::vec3(0.0f); // Guarda la posición donde el personaje insertó el ticket para regresar al terminar la interacción.
glm::vec3 rotacionInteraccion = glm::vec3(0.0f);

//const glm::vec3 posicionStandBateo = glm::vec3(-10.0f, 0.0f, 20.0f); // Puesto donde el jugador inicia la interacción de bateo.
const float rotacionStandBateo = 0.0f;
const glm::vec3 posicionStandTopos = glm::vec3(-16.0f, 0.0f, 23.5f); // Puesto donde el jugador inicia la interacción de topos.
const float rotacionStandTopos = 90.0f;
const glm::vec3 posicionStandHachas = glm::vec3(17.0f, 0.0f, 8.0f); // Puesto donde el jugador inicia la interacción de hachas.
const float rotacionStandHachas = -90.0f;
const glm::vec3 posicionStandBoliche = glm::vec3(-5.0f, 0.0f, 43.0f); // Puesto donde el jugador inicia la interacción de boliche.
const float rotacionStandBoliche = 180.0f;
const glm::vec3 posicionStandDados = glm::vec3(15.0f, 0.0f, 23.5f); // Puesto donde el jugador inicia la interacción de dados.
const float rotacionStandDados = -90.0f;
const glm::vec3 posicionStandDardos = glm::vec3(-14.0f, 0.0f, 40.0f); // Puesto donde el jugador inicia la interacción de dardos.
const float rotacionStandDardos = 90.0f;

const glm::vec3 posicionStandBateo = glm::vec3(0.0f, 0.0f, 0.0f);

const glm::vec3 posicionesStands[6] = { posicionStandBateo, posicionStandTopos, posicionStandHachas, posicionStandBoliche, posicionStandDados, posicionStandDardos };

const glm::vec3 posicionJaulaBateo = glm::vec3(-13.0f, 0.0f, 9.0f); // Posición de la jaula de bateo.
const float rotacionJaulaBateo = 0.0f;
const glm::vec3 posicionMaquinaTopos = glm::vec3(-18.0f, 0.0f, 25.5f); // Posición de la maquina de topos.
const float rotacionMaquinaTopos = 90.0f;
const glm::vec3 posicionCabinaHachas = glm::vec3(10.0f, 0.0f, 6.0f); // Posición de la cabina de hachas.
const float rotacionCabinaHachas = 0.0f;
const glm::vec3 posicionPistaBoliche = glm::vec3(0.0f, 0.0f, 65.0f); // Posición de la pista de boliche.
const float rotacionPistaBoliche = 180.0f;
const glm::vec3 posicionMesaDados = glm::vec3(17.0f, 0.0f, 21.0f); // Posición de la mesa de dados.
const float rotacionMesaDados = -90.0f;
const glm::vec3 posicionPuestoDardos = glm::vec3(-17.0f, 0.0f, 37.0f); // Posición del puesto de dardos.
const float rotacionPuestoDardos = 90.0f;

float apotema = 2.0f; // Rango en el que se puede interactuar con un puesto de tickets.

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
		// Bateo.
		if (harley.posicion.x > posicionStandBateo.x - apotema && harley.posicion.x < posicionStandBateo.x + apotema && harley.posicion.z > posicionStandBateo.z - apotema && harley.posicion.z < posicionStandBateo.z + apotema) {
			PagarJuego(1);
		}
		// Topos.
		else if (harley.posicion.x > posicionStandTopos.x - apotema && harley.posicion.x < posicionStandTopos.x + apotema && harley.posicion.z > posicionStandTopos.z - apotema && harley.posicion.z < posicionStandTopos.z + apotema)
		{
			PagarJuego(2);
		}
		// Hachas.
		else if (harley.posicion.x > posicionStandHachas.x - apotema && harley.posicion.x < posicionStandHachas.x + apotema && harley.posicion.z > posicionStandHachas.z - apotema && harley.posicion.z < posicionStandHachas.z + apotema)
		{
			PagarJuego(3);
		}
		// Boliche.
		else if (harley.posicion.x > posicionStandBoliche.x - apotema && harley.posicion.x < posicionStandBoliche.x + apotema && harley.posicion.z > posicionStandBoliche.z - apotema && harley.posicion.z < posicionStandBoliche.z + apotema)
		{
			PagarJuego(4);
		}
		// Dados.
		else if (harley.posicion.x > posicionStandDados.x - apotema && harley.posicion.x < posicionStandDados.x + apotema && harley.posicion.z > posicionStandDados.z - apotema && harley.posicion.z < posicionStandDados.z + apotema)
		{
			PagarJuego(5);
		}
		// Dardos.
		else if (harley.posicion.x > posicionStandDardos.x - apotema && harley.posicion.x < posicionStandDardos.x + apotema && harley.posicion.z > posicionStandDardos.z - apotema && harley.posicion.z < posicionStandDardos.z + apotema)
		{
			PagarJuego(6);
		}
	}

	if (keys[GLFW_KEY_L])
	{
		if (luzPrendida == 1.0f)
		{
			luzPrendida = 0.0f;
		}
		else
		{
			luzPrendida = 1.0f;
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

void DibujarEstructura(GLuint modelLoc, Shader& lightingShader, Model estructura, glm::vec3 posicionEstructura, float rotacionEstructura)
{
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, posicionEstructura);
	model = glm::rotate(model, glm::radians(rotacionEstructura), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	estructura.Draw(lightingShader);
}

void DibujarLuces(Shader& lightingShader)
{
	// Directional light.
	glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), direccionLuz.x, direccionLuz.y, direccionLuz.z);
	glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"), 0.25 + intensidadLuz * 0.25, 0.25 + intensidadLuz * 0.25, 0.25 + intensidadLuz * 0.25);
	glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.25 + intensidadLuz * 0.25, 0.25 + intensidadLuz * 0.25, 0.25 + intensidadLuz * 0.25);
	glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"), intensidadLuz * 0.25f, intensidadLuz * 0.25f, intensidadLuz * 0.25f);


	// Point light 1.
	glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), posicionJaulaBateo.x, posicionJaulaBateo.y, posicionJaulaBateo.z);
	glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), 0.0f, 0.0f, 1.0f * luzPrendida * intensidadLuzInversa);
	glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), 0.0f, 0.0f, 1.0f * luzPrendida * intensidadLuzInversa);
	glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), 0.0f, 0.0f, 1.0f * luzPrendida * intensidadLuzInversa);
	glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
	glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.027f);
	glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 0.028f);

	// Point light 2.
	glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].position"), posicionPistaBoliche.x, posicionPistaBoliche.y + 10.0f, posicionPistaBoliche.z);
	glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].ambient"), 0.0f, 0.0f, 1.0f * luzPrendida * intensidadLuzInversa);
	glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].diffuse"), 0.0f, 0.0f, 1.0f * luzPrendida * intensidadLuzInversa);
	glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].specular"), 0.0f, 0.0f, 1.0f * luzPrendida * intensidadLuzInversa);
	glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].constant"), 1.0f);
	glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].linear"), 0.022f);
	glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].quadratic"), 0.0019f);

	// Point light 3.
	glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].position"), 20.0f, 2.0f, 0.0f);
	glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].ambient"), luzPrendida * luzAutomatica, luzPrendida * luzAutomatica, luzPrendida * luzAutomatica);
	glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].diffuse"), luzPrendida * luzAutomatica, luzPrendida * luzAutomatica, luzPrendida * luzAutomatica);
	glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].specular"), 0.0f, 0.0f, 0.0f);
	glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].constant"), 1.0f);
	glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].linear"), 0.045f);
	glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].quadratic"), 0.075f);

	// Point light 4.
	glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].position"), -20.0f, 2.0f, 0.0f);
	glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].ambient"), luzPrendida * luzAutomatica, luzPrendida * luzAutomatica, luzPrendida * luzAutomatica);
	glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].diffuse"), luzPrendida * luzAutomatica, luzPrendida * luzAutomatica, luzPrendida * luzAutomatica);
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
	intensidadLuzInversa = glm::clamp(sin(radianes), 0.0f, 1.0f);  // 0.0 en noche, 1.0 en mediodía.
	intensidadLuz = 1.0 - intensidadLuzInversa;
	esNoche = intensidadLuz < 0.5f;  // Por ejemplo, cuando la luz es débil.

	// Calcula la mezcla entre día y noche.
	colorCielo = glm::mix(colorCieloNoche, colorCieloDia, intensidadLuz);
}

void RevisarHora()
{
	if (esNoche) {
		luzAutomatica = 1.0f;
	}
	else
	{
		luzAutomatica = 0.0f;
	}
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

	if (caminando)
	{
		harley.Caminar(deltaTime);
	}

}

void ChecarMovimiento()
{
	if (harley.posicion != harley.posicionAnterior)
	{
		// Está caminando.
		if (not caminando && not jugando)
		{
			harley.ComenzarCaminata();
			caminando = true;
		}
	}
	else
	{
		// Está quieta.
		if (caminando && not jugando)
		{
			harley.PoseIdle();
			caminando = false;
		}
	}
	harley.posicionAnterior = harley.posicion;
}

void PagarJuego(int juego)
{
	posicionInteraccion = harley.posicion;
	rotacionInteraccion = harley.rotacion;
	camaraEstatica = true;
	pagando = true;
	tiempoInteraccion = 0.0f;
	juegoActivo = juego;
	accesorioActivo = 7;

	switch (juego)
	{
	case 1:	// Bateo.
		harley.posicion = posicionStandBateo + glm::vec3(0.0f, 0.92f, 1.0f);
		harley.rotacion = glm::vec3(0.0f, rotacionStandBateo - 180.0f, 0.0f);

		posicionCamara = harley.posicion + glm::vec3(1.5f, 0.8f, 1.0f);
		objetivoCamara = posicionStandBateo + glm::vec3(0.0f, 1.4f, 0.0f);
		break;
	case 2:	// Topos.
		harley.posicion = posicionStandTopos + glm::vec3(1.0f, 0.92f, 0.0f);
		harley.rotacion = glm::vec3(0.0f, rotacionStandTopos - 180.0f, 0.0f);

		posicionCamara = harley.posicion + glm::vec3(1.5f, 0.8f, -1.0f);
		objetivoCamara = posicionStandTopos + glm::vec3(0.0f, 1.4f, 0.0f);
		break;
	case 3:	// Hachas.
		harley.posicion = posicionStandHachas + glm::vec3(-1.0f, 0.92f, 0.0f);
		harley.rotacion = glm::vec3(0.0f, rotacionStandHachas - 180.0f, 0.0f);

		posicionCamara = harley.posicion + glm::vec3(-1.0f, 0.8f, 1.5f);
		objetivoCamara = posicionStandHachas + glm::vec3(0.0f, 1.4f, 0.0f);
		break;
	case 4:	// Boliche.
		harley.posicion = posicionStandBoliche + glm::vec3(0.0f, 0.92f, -1.0f);
		harley.rotacion = glm::vec3(0.0f, rotacionStandBoliche - 180.0f, 0.0f);

		posicionCamara = harley.posicion + glm::vec3(-1.5f, 0.8f, -1.0f);
		objetivoCamara = posicionStandBoliche + glm::vec3(0.0f, 1.4f, 0.0f);
		break;
	case 5:	// Dados.
		harley.posicion = posicionStandDados + glm::vec3(-1.0f, 0.92f, 0.0f);
		harley.rotacion = glm::vec3(0.0f, rotacionStandDados - 180.0f, 0.0f);

		posicionCamara = harley.posicion + glm::vec3(-1.5f, 0.8f, 1.0f);
		objetivoCamara = posicionStandDados + glm::vec3(0.0f, 1.4f, 0.0f);
		break;
	case 6:	// Dardos.
		harley.posicion = posicionStandDardos + glm::vec3(1.0f, 0.92f, 0.0f);
		harley.rotacion = glm::vec3(0.0f, rotacionStandDardos - 180.0f, 0.0f);

		posicionCamara = harley.posicion + glm::vec3(1.5f, 0.8f, 1.0f);
		objetivoCamara = posicionStandDardos + glm::vec3(0.0f, 1.4f, 0.0f);
		break;
	default:
		break;
	harley.PoseIdle();
	}
}

void AnimarPago()
{
	tiempoInteraccion += deltaTime;
	harley.PagarBoleto(deltaTime);

	if (tiempoInteraccion >= 1.15f)
	{
		jugando = true;
		pagando = false;
		ComenzarJuego(juegoActivo);
	}
}

void ComenzarJuego(int juego)
{
	tiempoInteraccion = 0.0f;
	jugando = true;
	accesorioActivo = juegoActivo;
	switch (juego)
	{
	case 1:	// Bateo.
		maxTiempoInteraccion = 10.0f;
		harley.posicion = posicionJaulaBateo + glm::vec3(0.0f, 1.02f, 6.0f);
		harley.rotacion = glm::vec3(0.0f, rotacionJaulaBateo + 180.0f, 0.0f);
		harley.PoseIdle();

		posicionCamara = harley.posicion + glm::vec3(-1.0f, 0.5f, 3.0f);
		objetivoCamara = harley.posicion;
		break;
	case 2:	// Topos.
		maxTiempoInteraccion = 8.0f;
		harley.posicion = posicionMaquinaTopos + glm::vec3(1.0f, 0.92f, 0.0f);
		harley.rotacion = glm::vec3(0.0f, rotacionMaquinaTopos + 180.0f, 0.0f);
		harley.ComenzarTopos();

		posicionCamara = harley.posicion + glm::vec3(0.0f, 0.6f, -1.5f);
		objetivoCamara = posicionMaquinaTopos + glm::vec3(0.0f, 0.9f, 0.0f);
		break;
	case 3:	// Hachas.
		maxTiempoInteraccion = 3.5f;
		harley.posicion = posicionCabinaHachas + glm::vec3(0.0f, 0.92f, 0.0f);
		harley.rotacion = glm::vec3(0.0f, rotacionCabinaHachas + 180.0f, 0.0f);
		harley.PoseIdle();

		posicionCamara = harley.posicion + glm::vec3(-0.5f, 0.6f, 1.5f);
		objetivoCamara = posicionCabinaHachas + glm::vec3(-0.3f, 1.5f, 0.0f);
		break;
	case 4:	// Boliche.
		maxTiempoInteraccion = 3.0f;
		harley.posicion = posicionPistaBoliche + glm::vec3(0.95f, 2.5f, -6.4f);
		harley.rotacion = glm::vec3(0.0f, rotacionPistaBoliche + 180.0f, 0.0f);
		harley.PoseIdle();

		posicionCamara = harley.posicion + glm::vec3(-1.0f, 0.6f, -3.0f);
		objetivoCamara = harley.posicion + glm::vec3(3.0f, -0.5f, 16.0f);
		break;
	case 5:	// Dados.
		maxTiempoInteraccion = 3.0f;
		harley.posicion = posicionMesaDados + glm::vec3(-1.5f, 0.92f, 0.0f);
		harley.rotacion = glm::vec3(0.0f, rotacionMesaDados + 180.0f, 0.0f);
		harley.ComenzarDados();

		posicionCamara = harley.posicion + glm::vec3(-0.8f, 0.7f, 0.4f);
		objetivoCamara = posicionMesaDados + glm::vec3(0.0f, 1.0f, 0.0f);
		break;
	case 6:	// Dardos.
		maxTiempoInteraccion = 3.0f;
		harley.posicion = posicionPuestoDardos + glm::vec3(1.5f, 0.92f, 0.0f);
		harley.rotacion = glm::vec3(0.0f, rotacionPuestoDardos + 180.0f, 0.0f);
		harley.ComenzarDardos();

		posicionCamara = harley.posicion + glm::vec3(0.5f, 0.5f, -0.35f);
		objetivoCamara = posicionPuestoDardos + glm::vec3(0.0f, 1.5f, 0.0f);
		break;
	default:
		break;
	}
	ReiniciarObjeto();
}

void AnimarJuego(GLuint modelLoc, Shader& lightingShader, Model objetos[])
{
	tiempoInteraccion += deltaTime;
	switch (juegoActivo)
	{
	case 1:
		if (tiempoInteraccion >= 0.0f && tiempoInteraccion < 1.0f)
		{
			harley.AlzarBate(deltaTime);
		}
		if (tiempoInteraccion >= 1.0f && tiempoInteraccion < 2.5f)
		{
			harley.Batear(deltaTime);
		}
		if (tiempoInteraccion >= 2.5f && tiempoInteraccion < 3.5f)
		{
			harley.RegresarBate(deltaTime);
		}
		if (tiempoInteraccion >= 3.5f && tiempoInteraccion < 5.0f)
		{
			harley.Batear(deltaTime);
		}
		if (tiempoInteraccion >= 5.0f && tiempoInteraccion < 6.0f)
		{
			harley.RegresarBate(deltaTime);
		}
		if (tiempoInteraccion >= 6.0f && tiempoInteraccion < 7.5f)
		{
			harley.Batear(deltaTime);
		}
		if (tiempoInteraccion >= 7.5f && tiempoInteraccion < 8.5f)
		{
			harley.RegresarBate(deltaTime);
		}
		if (tiempoInteraccion >= 8.5f && tiempoInteraccion < 10.0f)
		{
			harley.Batear(deltaTime);
		}
		break;
	case 2:
		if (tiempoInteraccion >= 0.0f && tiempoInteraccion < 0.75f)
		{
			harley.AlzarMartillo(deltaTime);
		}
		if (tiempoInteraccion >= 1.25f && tiempoInteraccion < 1.75f)
		{
			harley.GolpearTopo(deltaTime);
		}
		if (tiempoInteraccion >= 2.75f && tiempoInteraccion < 3.5f)
		{
			harley.AlzarMartillo(deltaTime);
		}
		if (tiempoInteraccion >= 4.0f && tiempoInteraccion < 4.5f)
		{
			harley.GolpearTopo(deltaTime);
		}
		if (tiempoInteraccion >= 5.5f && tiempoInteraccion < 6.25f)
		{
			harley.AlzarMartillo(deltaTime);
		}
		if (tiempoInteraccion >= 6.75f && tiempoInteraccion < 7.25f)
		{
			harley.GolpearTopo(deltaTime);
		}
		break;
	case 3:
		if (tiempoInteraccion < 0.75f)
		{
			harley.AlzarHacha(deltaTime);
		}
		if (tiempoInteraccion >= 1.0f)
		{
			harley.LanzarHacha(deltaTime);
		}
		if (tiempoInteraccion >= 1.25f)
		{
			accesorioActivo = 0;
			LanzarObjeto(glm::vec3(0.0f, 0.0f, -1.0f), 6.0f, -840.f, 0.9f);
			DibujarObjeto(modelLoc, lightingShader, objetos[3]);
		}
		break;
	case 4:
		if (tiempoInteraccion < 0.5f)
		{
			harley.AlzarBola(deltaTime);
		}
		if (tiempoInteraccion >= 1.25f)
		{
			harley.LanzarBola(deltaTime);
		}
		break;
	case 5:
		harley.LanzarDados(deltaTime);
		break;
	case 6:
		harley.LanzarDardos(deltaTime);
		break;
	default:
		break;
	}
	if (tiempoInteraccion >= maxTiempoInteraccion) {
		TerminarJuego();
	}
}

void TerminarJuego()
{
	accesorioActivo = 0;
	camaraEstatica = false;
	jugando = false;
	harley.posicion = posicionInteraccion;
	harley.rotacion = rotacionInteraccion;
	harley.PoseIdle();
}

void ReiniciarObjeto()
{
	posicionObjeto = harley.posicion + glm::vec3(0.0f, 0.5f, 0.0f);
	rotacionObjeto = harley.rotacion;
	tiempoVuelo = 0.0f;
}

void LanzarObjeto(glm::vec3 direccionLanzamiento, float velocidadLanzamiento, float gradosRotacion, float tiempoVueloMaximo)
{
	tiempoVuelo += deltaTime;
	if (tiempoVuelo < tiempoVueloMaximo)
	{
		posicionObjeto.x += direccionLanzamiento.x * velocidadLanzamiento * deltaTime;
		posicionObjeto.y += direccionLanzamiento.y * velocidadLanzamiento * deltaTime;
		posicionObjeto.z += direccionLanzamiento.z * velocidadLanzamiento * deltaTime;

		rotacionObjeto.x += gradosRotacion * deltaTime;
	}
}

void DibujarObjeto(GLuint modelLoc, Shader& lightingShader, Model objeto)
{
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, posicionObjeto);
	model = glm::rotate(model, glm::radians(rotacionObjeto.x), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotacionObjeto.y), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotacionObjeto.z), glm::vec3(0.0f, 0.0f, 1.0f));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	objeto.Draw(lightingShader);
}