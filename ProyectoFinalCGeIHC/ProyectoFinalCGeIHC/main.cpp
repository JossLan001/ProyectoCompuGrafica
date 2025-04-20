#include <iostream>
#include <cmath>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include "stb_image.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Load Models
#include "SOIL2/SOIL2.h"


// Other includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// Function prototypes
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow *window, double xPos, double yPos);
void DoMovement();
void ReiniciarPose();
void CaminarPoseInicial();
void Caminar();

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Camera
Camera  camera(glm::vec3(0.0f, 0.0f, 3.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;
// Light attributes
glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
bool active;

// Position of the spot light
glm::vec3 spotLightPosition = glm::vec3(0.0f, 0.0f, 0.0f);
// Direction of the spot light
glm::vec3 spotLightDirection = glm::vec3(0.0f, 0.0f, 0.0f);

// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

//Animación Harley

glm::vec3 posicionHarley = glm::vec3(0.0f, 0.92f, 0.0f);
float rotacionXHarley = 0.0f;
float rotacionYHarley = 0.0f;
float rotacionZHarley = 0.0f;

float rotacionXCabezaHarley = 0.0f;
float rotacionYCabezaHarley = 0.0f;
float rotacionZCabezaHarley = 0.0f;

float rotacionXBrazoL1Harley = 0.0f;
float rotacionYBrazoL1Harley = 0.0f;
float rotacionZBrazoL1Harley = 0.0f;

float rotacionXBrazoL2Harley = 0.0f;
float rotacionYBrazoL2Harley = 0.0f;

float rotacionXBrazoR1Harley = 0.0f;
float rotacionYBrazoR1Harley = 0.0f;
float rotacionZBrazoR1Harley = 0.0f;

float rotacionXBrazoR2Harley = 0.0f;
float rotacionYBrazoR2Harley = 0.0f;

float rotacionXPiernaL1Harley = 0.0f;
float rotacionYPiernaL1Harley = 0.0f;
float rotacionZPiernaL1Harley = 0.0f;

float rotacionXPiernaL2Harley = 0.0f;
float rotacionYPiernaL2Harley = 0.0f;

float rotacionXPiernaR1Harley = 0.0f;
float rotacionYPiernaR1Harley = 0.0f;
float rotacionZPiernaR1Harley = 0.0f;

float rotacionXPiernaR2Harley = 0.0f;
float rotacionYPiernaR2Harley = 0.0f;

float velocidadAnim = 100.0f;
float tiempoAnim = 0.0f;
float cicloAnim = 1.0f;

bool caminando = false;

int main()
{
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Proyecto Final", nullptr, nullptr);

	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

	// Set the required callback functions
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MouseCallback);

	// GLFW Options
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Define the viewport dimensions
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);


	//Load Model
	Shader lightingShader("Shaders/lighting.vs", "Shaders/lighting.frag");
	Shader lampShader("Shaders/lamp.vs", "Shaders/lamp.frag");

	//Harley
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

	// Set texture units
	lightingShader.Use();


	glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 1000.0f);

	// Game loop
	while (!glfwWindowShouldClose(window))
	{

		// Calculate deltatime of current frame
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		DoMovement();

		// Clear the colorbuffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	   
		// OpenGL options
		glEnable(GL_DEPTH_TEST);

		// Use cooresponding shader when setting uniforms/drawing objects
		lightingShader.Use();

        glUniform1i(glGetUniformLocation(lightingShader.Program, "diffuse"), 0);
		glUniform1i(glGetUniformLocation(lightingShader.Program, "specular"), 1);

		GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
		glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);


		// Directional light
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"),0.5f, 0.5f, 0.5f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.5f, 0.5f, 0.5f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"),0.0f, 0.0f, 0.0f);


		// Point light 1
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), 0.0f, 0.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.045f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 0.075f);

		// Point light 2
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].position"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].ambient"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].diffuse"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].specular"), 0.0f, 0.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].linear"), 0.045f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].quadratic"), 0.075f);

		// Point light 3
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].position"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].ambient"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].diffuse"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].specular"), 0.0f, 0.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].linear"), 0.045f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].quadratic"), 0.075f);

		// Point light 4
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].position"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].ambient"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].diffuse"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].specular"), 0.0f, 0.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].linear"), 0.045f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].quadratic"), 0.075f);

		// SpotLight
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.position"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.direction"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.ambient"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.diffuse"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.specular"),0.0f, 0.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.linear"), 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.quadratic"), 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(32.0f)));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(40.0f)));

		// Set material properties
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 16.0f);

		// Create camera transformations
		glm::mat4 view;
		view = camera.GetViewMatrix();

		// Get the uniform locations
		GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
		GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");

		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glm::mat4 model(1);
	

		//Carga de modelo 
        view = camera.GetViewMatrix();
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);

		//Agua
		//glEnable(GL_BLEND);//Avtiva la funcionalidad para trabajar el canal alfa
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//model = glm::mat4(1);
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//agua.Draw(lightingShader);
		//glDisable(GL_BLEND); //Desactiva el canal alfa 

		//Harley
		//Cuerpo Harley
		model = glm::mat4(1);
		model = glm::translate(model, posicionHarley);
		model = glm::rotate(model, glm::radians(rotacionXHarley), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotacionYHarley), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotacionZHarley), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		harley_cuerpo.Draw(lightingShader);

		//Cabeza Harley
		model = glm::translate(model, glm::vec3(0.0f, 0.507119f, -0.005981f));
		model = glm::rotate(model, glm::radians(rotacionXCabezaHarley), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotacionYCabezaHarley), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotacionZCabezaHarley), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		harley_cabeza.Draw(lightingShader);

		//Brazo_L_1 Harley
		model = glm::mat4(1);
		model = glm::translate(model, posicionHarley);
		model = glm::rotate(model, glm::radians(rotacionXHarley), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotacionYHarley), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotacionZHarley), glm::vec3(0.0f, 0.0f, 1.0f));

		model = glm::translate(model, glm::vec3(0.107058f, 0.389674f, -0.020696f));
		model = glm::rotate(model, glm::radians(rotacionXBrazoL1Harley), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotacionYBrazoL1Harley), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotacionZBrazoL1Harley), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		harley_brazo_l_1.Draw(lightingShader);

		//Brazo_L_2 Harley
		model = glm::translate(model, glm::vec3(0.249121f, 0.015555f, 0.000215f));
		model = glm::rotate(model, glm::radians(rotacionXBrazoL2Harley), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotacionYBrazoL2Harley), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		harley_brazo_l_2.Draw(lightingShader);

		//Brazo_R_1 Harley
		model = glm::mat4(1);
		model = glm::translate(model, posicionHarley);
		model = glm::rotate(model, glm::radians(rotacionXHarley), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotacionYHarley), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotacionZHarley), glm::vec3(0.0f, 0.0f, 1.0f));

		model = glm::translate(model, glm::vec3(-0.107058, 0.389674, -0.020696));
		model = glm::rotate(model, glm::radians(rotacionXBrazoR1Harley), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotacionYBrazoR1Harley), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotacionZBrazoR1Harley), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		harley_brazo_r_1.Draw(lightingShader);

		//Brazo_R_2 Harley
		model = glm::translate(model, glm::vec3(-0.249121, 0.015555, 0.000215));
		model = glm::rotate(model, glm::radians(rotacionXBrazoR2Harley), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotacionYBrazoR2Harley), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		harley_brazo_r_2.Draw(lightingShader);

		//Pierna_L_1 Harley
		model = glm::mat4(1);
		model = glm::translate(model, posicionHarley);
		model = glm::rotate(model, glm::radians(rotacionXHarley), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotacionYHarley), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotacionZHarley), glm::vec3(0.0f, 0.0f, 1.0f));

		model = glm::rotate(model, glm::radians(rotacionXPiernaL1Harley), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotacionYPiernaL1Harley), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotacionZPiernaL1Harley), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(0.06f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		harley_pierna_l_1.Draw(lightingShader);

		//Pierna_L_2 Harley
		model = glm::translate(model, glm::vec3(0.076131f - 0.06f, -0.413235f, 0.007457f));
		model = glm::rotate(model, glm::radians(rotacionXPiernaL2Harley), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotacionYPiernaL2Harley), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		harley_pierna_l_2.Draw(lightingShader);

		//Pierna_R_1 Harley
		model = glm::mat4(1);
		model = glm::translate(model, posicionHarley);
		model = glm::rotate(model, glm::radians(rotacionXHarley), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotacionYHarley), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotacionZHarley), glm::vec3(0.0f, 0.0f, 1.0f));

		model = glm::translate(model, glm::vec3(-0.06f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotacionXPiernaR1Harley), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotacionYPiernaR1Harley), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotacionZPiernaR1Harley), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		harley_pierna_r_1.Draw(lightingShader);

		//Pierna_R_2 Harley
		model = glm::translate(model, glm::vec3(-0.086131f + 0.06f, -0.413235f, 0.007457f));
		model = glm::rotate(model, glm::radians(rotacionXPiernaR2Harley), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotacionYPiernaR2Harley), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		harley_pierna_r_2.Draw(lightingShader);

		//Reseteo
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glBindVertexArray(0);

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}


	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();



	return 0;
}

// Moves/alters the camera positions based on user input
void DoMovement()
{

	// Camera controls
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
	{
		camera.ProcessKeyboard(FORWARD, deltaTime);

	}

	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
	{
		camera.ProcessKeyboard(BACKWARD, deltaTime);


	}

	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
	{
		camera.ProcessKeyboard(LEFT, deltaTime);


	}

	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
	{
		camera.ProcessKeyboard(RIGHT, deltaTime);


	}

	if (caminando)
	{
		Caminar();
	}

}

// Is called whenever a key is pressed/released via GLFW
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

	if (keys[GLFW_KEY_SPACE])
	{
		ReiniciarPose();
		CaminarPoseInicial();
		caminando = not caminando;
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
	GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xOffset, yOffset);
}

void ReiniciarPose()
{
	rotacionXHarley = 0.0f;
	rotacionYHarley = 0.0f;
	rotacionZHarley = 0.0f;

	rotacionXCabezaHarley = 0.0f;
	rotacionYCabezaHarley = 0.0f;
	rotacionZCabezaHarley = 0.0f;

	rotacionXBrazoL1Harley = 0.0f;
	rotacionYBrazoL1Harley = 0.0f;
	rotacionZBrazoL1Harley = 0.0f;

	rotacionXBrazoL2Harley = 0.0f;
	rotacionYBrazoL2Harley = 0.0f;

	rotacionXBrazoR1Harley = 0.0f;
	rotacionYBrazoR1Harley = 0.0f;
	rotacionZBrazoR1Harley = 0.0f;

	rotacionXBrazoR2Harley = 0.0f;
	rotacionYBrazoR2Harley = 0.0f;

	rotacionXPiernaL1Harley = 0.0f;
	rotacionYPiernaL1Harley = 0.0f;
	rotacionZPiernaL1Harley = 0.0f;

	rotacionXPiernaL2Harley = 0.0f;
	rotacionYPiernaL2Harley = 0.0f;

	rotacionXPiernaR1Harley = 0.0f;
	rotacionYPiernaR1Harley = 0.0f;
	rotacionZPiernaR1Harley = 0.0f;

	rotacionXPiernaR2Harley = 0.0f;
	rotacionYPiernaR2Harley = 0.0f;

	tiempoAnim = 0.0f;
	cicloAnim = 1.0f;
}

void CaminarPoseInicial()
{
	rotacionXHarley = 2.0f;

	rotacionXCabezaHarley = -5.0f;

	rotacionXBrazoL1Harley = 35.0f;
	rotacionZBrazoL1Harley = -75.0f;

	rotacionYBrazoL2Harley = -43.0f;

	rotacionXBrazoR1Harley = 10.0f;
	rotacionZBrazoR1Harley = 75.0f;

	rotacionYBrazoR2Harley = 30.0f;

	rotacionXPiernaL1Harley = -30.0f;

	rotacionXPiernaL2Harley = 15.0f;

	rotacionXPiernaR1Harley = 10.0f;

	rotacionXPiernaR2Harley = 35.0f;

}

void Caminar()
{
	tiempoAnim += deltaTime;
	
	rotacionXBrazoL1Harley += -50.0f * cicloAnim * deltaTime;
	rotacionYBrazoL2Harley += 30.0f * cicloAnim * deltaTime;

	rotacionXBrazoR1Harley += 50.0f * cicloAnim * deltaTime;
	rotacionYBrazoR2Harley += 30.0f * cicloAnim * deltaTime;

	rotacionXPiernaL1Harley += 80.0f * cicloAnim * deltaTime;
	rotacionXPiernaL2Harley += 40.0f * cicloAnim * deltaTime;

	rotacionXPiernaR1Harley += -80.0f * cicloAnim * deltaTime;
	rotacionXPiernaR2Harley += -40.0f * cicloAnim * deltaTime;

	if (tiempoAnim >= 0.5f)
	{
		cicloAnim = cicloAnim * -1.0f;
		tiempoAnim = 0.0f;
	}
}