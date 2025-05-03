#include <iostream>
#include <cmath>

// GLEW.
#include <GL/glew.h>

// GLFW.
#include <GLFW/glfw3.h>

// Other Libs.
#include "stb_image.h"

// GLM Mathematics.
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Load Models.
#include "SOIL2/SOIL2.h"


// Other includes.
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// Definición de Funciones.
// Teclas y Mouse.
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow *window, double xPos, double yPos);

// Modo de Camara.
glm::mat4 ModoCamara();

// Iluminación.
void DibujarLuces(Shader& lightingShader);
void CicloDiaNoche(float deltaTime);

// Dibujo de Harley.
void DibujarHarley(GLuint modelLoc, Shader& lightingShader, Model harley_cuerpo, Model harley_cabeza, Model harley_brazo_l_1, Model harley_brazo_l_2, Model harley_brazo_r_1, Model harley_brazo_r_2, Model harley_pierna_l_1, Model harley_pierna_l_2, Model harley_pierna_r_1, Model harley_pierna_r_2);
void DibujarAccesorio(GLuint modelLoc, Shader& lightingShader, Model bate);

// Controlador de Movimiento.
void MoverHarley();

// Controladores de Animación.
void ChecarMovimiento();
void AnimarHarley();
void AnimarJuego();
void TerminarJuego();

// Animaciones de Caminata.
void ReiniciarPose();
void PoseIdle();
void ComenzarCaminata();
void Caminar();

// Animaciones de Interacción.
void PoseSentada();
void ComenzarBateo();
void Batear();
void ComenzarTopos();
void GolpearTopos();
void ComenzarHachas();
void LanzarHachas();
void ComenzarBoliche();
void JugarBoliche();
void ComenzarDados();
void LanzarDados();
void ComenzarDardos();
void LanzarDardos();

// Window Dimensions.
const GLuint WIDTH = 1920, HEIGHT = 1080;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Cámara.
Camera  camera(glm::vec3(0.0f, 0.0f, 3.0f));
glm::vec3 posicionCamara = glm::vec3(0.0f);
glm::vec3 objetivoCamara = glm::vec3(0.0f);
glm::vec3 upCamara = glm::vec3(0.0f, 1.0f, 0.0f);
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;
bool camaraEstatica = false;
bool camaraArriba = false;

// Light Attributes.
glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
bool active;

// Deltatime.
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame.
GLfloat lastFrame = 0.0f;  	// Time of last frame.

// Elementos Interactivos.
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

// Animación Harley
glm::vec3 posicionHarley = glm::vec3(0.0f, 0.92f, 0.0f);
glm::vec3 posicionHarleyAnterior = glm::vec3(0.0f, 0.92f, 0.0f);
glm::vec3 rotacionHarley = glm::vec3(0.0f);

glm::vec3 rotacionCabezaHarley = glm::vec3(0.0f);
glm::vec3 rotacionBrazoL1Harley = glm::vec3(15.0f, 0.0f, -75.0f);
glm::vec3 rotacionBrazoL2Harley = glm::vec3(0.0f, -25.0f, 0.0f);
glm::vec3 rotacionBrazoR1Harley = glm::vec3(15.0f, 0.0f, 75.0f);
glm::vec3 rotacionBrazoR2Harley = glm::vec3(0.0f, 25.0f, 0.0f);
glm::vec3 rotacionPiernaL1Harley = glm::vec3(0.0f);
glm::vec3 rotacionPiernaL2Harley = glm::vec3(0.0f);
glm::vec3 rotacionPiernaR1Harley = glm::vec3(0.0f);
glm::vec3 rotacionPiernaR2Harley = glm::vec3(0.0f);

float velocidadAnim = 100.0f;
float tiempoAnim = 0.0f;
float cicloAnim = 1.0f;

bool caminando = false;
bool jugando = false;
int juegoActivo = 0;

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

int main()
{
	// Init GLFW.
	glfwInit();
	// Set all the required options for GLFW.
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	// Create a GLFWwindow object that we can use for GLFW's functions.
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Proyecto Final", nullptr, nullptr);

	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

	// Set the required callback functions.
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MouseCallback);

	// GLFW Options.
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions.
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers.
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Define the viewport dimensions.
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);


	// Load Model.
	Shader lightingShader("Shaders/lighting.vs", "Shaders/lighting.frag");
	Shader lampShader("Shaders/lamp.vs", "Shaders/lamp.frag");

	Model suelo((char*)"Modelos/Suelo.obj");

	// Stand Tickets.
	Model stand_tickets((char*)"Modelos/Stand_Tickets.obj");
	
	// Jaula Bateo.
	Model jaula_bateo((char*)"Modelos/Jaula_Bateo.obj");
	Model bate((char*)"Modelos/Bate.obj");

	// Maquina Topos.
	Model maquina_topos((char*)"Modelos/Maquina_Topos.obj");

	// Hachas.
	//Model cabina_hachas((char*)"Modelos/Cabina_Hachas.obj");

	// Boliche.
	//Model pista_boliche((char*)"Modelos/Pista_Boliche.obj");

	// Dados.
	//Model mesa_dados((char*)"Modelos/Mesa_Dados.obj");

	// Dardos.
	//Model puesto_dardos((char*)"Modelos/Puesto_Dardos.obj");

	// Harley.
	Model harley_cuerpo((char*)"Modelos/Harley_Cuerpo.obj");
	Model harley_cabeza((char*)"Modelos/Harley_Cabeza.obj");
	Model harley_brazo_l_1((char*)"Modelos/Harley_Brazo_L_1.obj");
	Model harley_brazo_l_2((char*)"Modelos/Harley_Brazo_L_2.obj");
	Model harley_brazo_r_1((char*)"Modelos/Harley_Brazo_R_1.obj");
	Model harley_brazo_r_2((char*)"Modelos/Harley_Brazo_R_2.obj");
	Model harley_pierna_l_1((char*)"Modelos/Harley_Pierna_L_1.obj");
	Model harley_pierna_l_2((char*)"Modelos/Harley_Pierna_L_2.obj");
	Model harley_pierna_r_1((char*)"Modelos/Harley_Pierna_R_1.obj");
	Model harley_pierna_r_2((char*)"Modelos/Harley_Pierna_R_2.obj");

	// Set texture units.
	lightingShader.Use();


	glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 1000.0f);

	// Game loop.
	while (!glfwWindowShouldClose(window))
	{

		// Calculate deltatime of current frame.
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions.
		glfwPollEvents();
		CicloDiaNoche(deltaTime);
		AnimarHarley();

		// Cambiar el color del cielo.
		glClearColor(colorCielo.r, colorCielo.g, colorCielo.b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	   
		// OpenGL options.
		glEnable(GL_DEPTH_TEST);

		// Use cooresponding shader when setting uniforms/drawing objects.
		lightingShader.Use();

        glUniform1i(glGetUniformLocation(lightingShader.Program, "diffuse"), 0);
		glUniform1i(glGetUniformLocation(lightingShader.Program, "specular"), 1);

		GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
		glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);

		DibujarLuces(lightingShader);

		// Set material properties.
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 16.0f);

		// Create camera transformations.
		glm::mat4 view;
		view = ModoCamara();

		// Get the uniform locations.
		GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
		GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");

		// Pass the matrices to the shader.
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glm::mat4 model(1);

		// Carga de modelo.
        view = camera.GetViewMatrix();
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		suelo.Draw(lightingShader);
		
		// Juego de Bateo.
		model = glm::mat4(1);
		model = glm::translate(model, posicionStandBateo);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		stand_tickets.Draw(lightingShader);

		//glEnable(GL_BLEND); // Activa la funcionalidad para trabajar el canal alfa.
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 1);
		model = glm::mat4(1);
		model = glm::translate(model, posicionJaulaBateo);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		jaula_bateo.Draw(lightingShader);
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		//glDisable(GL_BLEND); // Desactiva el canal alfa.

		// Juego de Topos.
		//model = glm::mat4(1);
		//model = glm::translate(model, posicionStandTopos);
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//stand_tickets.Draw(lightingShader);

		//model = glm::mat4(1);
		//model = glm::translate(model, posicionMaquinaTopos);
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//maquina_topos.Draw(lightingShader);

		// Juego de Hachas.
		//model = glm::mat4(1);
		//model = glm::translate(model, posicionStandHachas);
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//stand_tickets.Draw(lightingShader);

		//model = glm::mat4(1);
		//model = glm::translate(model, posicionCabinaHachas);
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//cabina_hachas.Draw(lightingShader);

		// Juego de Boliche.
		//model = glm::mat4(1);
		//model = glm::translate(model, posicionStandBoliche);
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//stand_tickets.Draw(lightingShader);

		//model = glm::mat4(1);
		//model = glm::translate(model, posicionPistaBoliche);
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//pista_boliche.Draw(lightingShader);

		// Juego de Dados.
		//model = glm::mat4(1);
		//model = glm::translate(model, posicionStandDados);
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//stand_tickets.Draw(lightingShader);

		//model = glm::mat4(1);
		//model = glm::translate(model, posicionMesaDados);
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//mesa_dados.Draw(lightingShader);

		// Juego de Dardos.
		//model = glm::mat4(1);
		//model = glm::translate(model, posicionStandDardos);
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//stand_tickets.Draw(lightingShader);

		//model = glm::mat4(1);
		//model = glm::translate(model, posicionPuestoDardos);
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//puesto_dardos.Draw(lightingShader);

		// Dibuja a Harley
		DibujarHarley(modelLoc, lightingShader, harley_cuerpo, harley_cabeza, harley_brazo_l_1, harley_brazo_l_2, harley_brazo_r_1, harley_brazo_r_2, harley_pierna_l_1, harley_pierna_l_2, harley_pierna_r_1, harley_pierna_r_2);
		if (jugando) {
			DibujarAccesorio(modelLoc, lightingShader, bate);
		}

		// Resetea transparencia como prevención.
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glBindVertexArray(0);

		// Swap the screen buffers.
		glfwSwapBuffers(window);
	}

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();

	return 0;
}

// Is called whenever a key is pressed/released via GLFW.
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
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
		if (posicionHarley.x > posicionStandBateo.x - apotema && posicionHarley.x < posicionStandBateo.x + apotema && posicionHarley.z > posicionStandBateo.x - apotema && posicionHarley.z < posicionStandBateo.x + apotema) {
			jugando = true;
			posicionCamara = posicionStandBateo + glm::vec3(2.0f, 4.0f, -4.0f);;
			objetivoCamara = posicionJaulaBateo;
			camaraEstatica = !camaraEstatica;

			posicionInteraccion = posicionHarley;
			posicionHarley = posicionJaulaBateo + glm::vec3(0.0f, 1.02f, 0.0f);
			rotacionHarley = glm::vec3(0.0f, 0.0f, 0.0f);
			ComenzarBateo();
			juegoActivo = 1;
		}
		else if (posicionHarley.x > posicionStandTopos.x - apotema && posicionHarley.x < posicionStandTopos.x + apotema && posicionHarley.z > posicionStandTopos.x - apotema && posicionHarley.z < posicionStandTopos.x + apotema)
		{

		}
		else if (posicionHarley.x > posicionStandHachas.x - apotema && posicionHarley.x < posicionStandHachas.x + apotema && posicionHarley.z > posicionStandHachas.x - apotema && posicionHarley.z < posicionStandHachas.x + apotema)
		{

		}
		else if (posicionHarley.x > posicionStandBoliche.x - apotema && posicionHarley.x < posicionStandBoliche.x + apotema && posicionHarley.z > posicionStandBoliche.x - apotema && posicionHarley.z < posicionStandBoliche.x + apotema)
		{

		}
		else if (posicionHarley.x > posicionStandDados.x - apotema && posicionHarley.x < posicionStandDados.x + apotema && posicionHarley.z > posicionStandDados.x - apotema && posicionHarley.z < posicionStandDados.x + apotema)
		{

		}
		else if (posicionHarley.x > posicionStandDardos.x - apotema && posicionHarley.x < posicionStandDardos.x + apotema && posicionHarley.z > posicionStandDardos.x - apotema && posicionHarley.z < posicionStandDardos.x + apotema)
		{

		}
	}
}

void MouseCallback(GLFWwindow *window, double xPos, double yPos)
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
    camera.target = posicionHarley;
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

void DibujarHarley(GLuint modelLoc, Shader& lightingShader, Model harley_cuerpo, Model harley_cabeza, Model harley_brazo_l_1, Model harley_brazo_l_2, Model harley_brazo_r_1, Model harley_brazo_r_2, Model harley_pierna_l_1, Model harley_pierna_l_2, Model harley_pierna_r_1, Model harley_pierna_r_2)
{
	glm::mat4 model = glm::mat4(1.0f);
	// Harley.
	// Cuerpo Harley.
	model = glm::mat4(1);
	model = glm::translate(model, posicionHarley);
	model = glm::rotate(model, glm::radians(rotacionHarley.x), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotacionHarley.y), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotacionHarley.z), glm::vec3(0.0f, 0.0f, 1.0f));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	harley_cuerpo.Draw(lightingShader);

	// Cabeza Harley.
	model = glm::translate(model, glm::vec3(0.0f, 0.507119f, -0.005981f));
	model = glm::rotate(model, glm::radians(rotacionCabezaHarley.x), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotacionCabezaHarley.y), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotacionCabezaHarley.z), glm::vec3(0.0f, 0.0f, 1.0f));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	harley_cabeza.Draw(lightingShader);

	// Brazo_L_1 Harley.
	model = glm::mat4(1);
	model = glm::translate(model, posicionHarley);
	model = glm::rotate(model, glm::radians(rotacionHarley.x), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotacionHarley.y), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotacionHarley.z), glm::vec3(0.0f, 0.0f, 1.0f));

	model = glm::translate(model, glm::vec3(0.107058f, 0.389674f, -0.020696f));
	model = glm::rotate(model, glm::radians(rotacionBrazoL1Harley.x), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotacionBrazoL1Harley.y), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotacionBrazoL1Harley.z), glm::vec3(0.0f, 0.0f, 1.0f));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	harley_brazo_l_1.Draw(lightingShader);

	// Brazo_L_2 Harley.
	model = glm::translate(model, glm::vec3(0.249121f, 0.015555f, 0.000215f));
	model = glm::rotate(model, glm::radians(rotacionBrazoL2Harley.x), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotacionBrazoL2Harley.y), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	harley_brazo_l_2.Draw(lightingShader);

	// Brazo_R_1 Harley.
	model = glm::mat4(1);
	model = glm::translate(model, posicionHarley);
	model = glm::rotate(model, glm::radians(rotacionHarley.x), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotacionHarley.y), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotacionHarley.z), glm::vec3(0.0f, 0.0f, 1.0f));

	model = glm::translate(model, glm::vec3(-0.107058, 0.389674, -0.020696));
	model = glm::rotate(model, glm::radians(rotacionBrazoR1Harley.x), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotacionBrazoR1Harley.y), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotacionBrazoR1Harley.z), glm::vec3(0.0f, 0.0f, 1.0f));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	harley_brazo_r_1.Draw(lightingShader);

	// Brazo_R_2 Harley.
	model = glm::translate(model, glm::vec3(-0.249121, 0.015555, 0.000215));
	model = glm::rotate(model, glm::radians(rotacionBrazoR2Harley.x), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotacionBrazoR2Harley.y), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	harley_brazo_r_2.Draw(lightingShader);

	// Pierna_L_1 Harley.
	model = glm::mat4(1);
	model = glm::translate(model, posicionHarley);
	model = glm::rotate(model, glm::radians(rotacionHarley.x), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotacionHarley.y), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotacionHarley.z), glm::vec3(0.0f, 0.0f, 1.0f));

	model = glm::rotate(model, glm::radians(rotacionPiernaL1Harley.x), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotacionPiernaL1Harley.y), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotacionPiernaL1Harley.z), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(0.06f, 0.0f, 0.0f));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	harley_pierna_l_1.Draw(lightingShader);

	// Pierna_L_2 Harley.
	model = glm::translate(model, glm::vec3(0.076131f - 0.06f, -0.413235f, 0.007457f));
	model = glm::rotate(model, glm::radians(rotacionPiernaL2Harley.x), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotacionPiernaL2Harley.y), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	harley_pierna_l_2.Draw(lightingShader);

	// Pierna_R_1 Harley.
	model = glm::mat4(1);
	model = glm::translate(model, posicionHarley);
	model = glm::rotate(model, glm::radians(rotacionHarley.x), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotacionHarley.y), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotacionHarley.z), glm::vec3(0.0f, 0.0f, 1.0f));

	model = glm::translate(model, glm::vec3(-0.06f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotacionPiernaR1Harley.x), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotacionPiernaR1Harley.y), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotacionPiernaR1Harley.z), glm::vec3(0.0f, 0.0f, 1.0f));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	harley_pierna_r_1.Draw(lightingShader);

	// Pierna_R_2 Harley.
	model = glm::translate(model, glm::vec3(-0.086131f + 0.06f, -0.413235f, 0.007457f));
	model = glm::rotate(model, glm::radians(rotacionPiernaR2Harley.x), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotacionPiernaR2Harley.y), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	harley_pierna_r_2.Draw(lightingShader);
}

void DibujarAccesorio(GLuint modelLoc, Shader& lightingShader, Model bate) {
	glm::mat4 model = glm::mat4(1.0f);
	// Transformaciones Brazo_R_1 Harley.
	model = glm::mat4(1);
	model = glm::translate(model, posicionHarley);
	model = glm::rotate(model, glm::radians(rotacionHarley.x), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotacionHarley.y), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotacionHarley.z), glm::vec3(0.0f, 0.0f, 1.0f));

	model = glm::translate(model, glm::vec3(-0.107058, 0.389674, -0.020696));
	model = glm::rotate(model, glm::radians(rotacionBrazoR1Harley.x), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotacionBrazoR1Harley.y), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotacionBrazoR1Harley.z), glm::vec3(0.0f, 0.0f, 1.0f));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	// Transformaciones Brazo_R_2 Harley.
	model = glm::translate(model, glm::vec3(-0.249121, 0.015555, 0.000215));
	model = glm::rotate(model, glm::radians(rotacionBrazoR2Harley.x), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotacionBrazoR2Harley.y), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	// Accesorio.
	model = glm::translate(model, glm::vec3(-0.35, 0.0, 0.0));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	switch (juegoActivo)
	{
	case 1:
		bate.Draw(lightingShader);
	case 2:
		break;
	default:
		break;
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
		posicionHarley += movimiento * speed;

		// Calcular ángulo en Y desde la dirección del movimiento.
		float angle = glm::degrees(atan2(movimiento.x, movimiento.z));
		rotacionHarley.y = angle;
	}

	if (caminando)
	{
		Caminar();
	}

}

void ChecarMovimiento()
{
	if (posicionHarley != posicionHarleyAnterior)
	{
		// Está caminando.
		if (!caminando && not jugando)
		{
			ComenzarCaminata();
		}
	}
	else
	{
		// Está quieta.
		if (caminando && not jugando)
		{
			PoseIdle();
			caminando = false;
		}
	}
	posicionHarleyAnterior = posicionHarley;
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
		Batear();
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
	PoseIdle();
	posicionHarley = posicionInteraccion;
}

void ReiniciarPose()
{
	rotacionCabezaHarley = glm::vec3(0.0f, 0.0f, 0.0f);

	rotacionBrazoL1Harley = glm::vec3(0.0f, 0.0f, 0.0f);

	rotacionBrazoL2Harley = glm::vec3(0.0f, 0.0f, 0.0f);

	rotacionBrazoR1Harley = glm::vec3(0.0f, 0.0f, 0.0f);

	rotacionBrazoR2Harley = glm::vec3(0.0f, 0.0f, 0.0f);

	rotacionPiernaL1Harley = glm::vec3(0.0f, 0.0f, 0.0f);

	rotacionPiernaL2Harley = glm::vec3(0.0f, 0.0f, 0.0f);

	rotacionPiernaR1Harley = glm::vec3(0.0f, 0.0f, 0.0f);

	rotacionPiernaR2Harley = glm::vec3(0.0f, 0.0f, 0.0f);

	tiempoAnim = 0.0f;
	cicloAnim = 1.0f;
}

void PoseIdle()
{
	ReiniciarPose();

	rotacionBrazoL1Harley = glm::vec3(15.0f, 0.0f, -75.0f);
	rotacionBrazoL2Harley.y = -25.0f;

	rotacionBrazoR1Harley = glm::vec3(15.0f, 0.0f, 75.0f);
	rotacionBrazoR2Harley.y = 25.0f;
}

void ComenzarCaminata()
{
	ReiniciarPose();

	rotacionBrazoL1Harley.x = 35.0f;
	rotacionBrazoL1Harley.z = -75.0f;

	rotacionBrazoL2Harley.y = -43.0f;

	rotacionBrazoR1Harley.x = 10.0f;
	rotacionBrazoR1Harley.z = 75.0f;

	rotacionBrazoR2Harley.y = 30.0f;

	rotacionPiernaL1Harley.x = -30.0f;

	rotacionPiernaL2Harley.x = 15.0f;

	rotacionPiernaR1Harley.x = 10.0f;

	rotacionPiernaR2Harley.x = 35.0f;

	caminando = true;

}

void Caminar()
{
	tiempoAnim += deltaTime;

	rotacionBrazoL1Harley.x += -50.0f * cicloAnim * deltaTime;
	rotacionBrazoL2Harley.y += 30.0f * cicloAnim * deltaTime;

	rotacionBrazoR1Harley.x += 50.0f * cicloAnim * deltaTime;
	rotacionBrazoR2Harley.y += 30.0f * cicloAnim * deltaTime;

	rotacionPiernaL1Harley.x += 80.0f * cicloAnim * deltaTime;
	rotacionPiernaL2Harley.x += 40.0f * cicloAnim * deltaTime;

	rotacionPiernaR1Harley.x += -80.0f * cicloAnim * deltaTime;
	rotacionPiernaR2Harley.x += -40.0f * cicloAnim * deltaTime;

	if (tiempoAnim >= 0.5f)
	{
		cicloAnim = cicloAnim * -1.0f;
		tiempoAnim = 0.0f;
	}
}

void PoseSentada()
{
	ReiniciarPose();

	rotacionPiernaL1Harley.x = -90.0f;
	rotacionPiernaL2Harley.x = 90.0f;

	rotacionPiernaR1Harley.x = -90.0f;
	rotacionPiernaR2Harley.x = 90.0f;
}

void ComenzarBateo()
{
	ReiniciarPose();

	rotacionBrazoL1Harley.z = -70.0f;

	rotacionBrazoR1Harley.x = -180.0f;
}

void Batear()
{
	tiempoAnim += deltaTime;

	rotacionHarley.y += 20.0f * cicloAnim * deltaTime;
	rotacionBrazoR1Harley.y += -50.0f * cicloAnim * deltaTime;

	if (tiempoAnim >= 2.0f) {
		TerminarJuego();
	}
}

void ComenzarTopos()
{

}

void GolpearTopos()
{

}

void ComenzarHachas()
{

}

void LanzarHachas()
{

}

void ComenzarBoliche()
{

}

void JugarBoliche()
{

}

void ComenzarDados()
{

}

void LanzarDados()
{

}

void ComenzarDardos()
{

}

void LanzarDardos()
{

}