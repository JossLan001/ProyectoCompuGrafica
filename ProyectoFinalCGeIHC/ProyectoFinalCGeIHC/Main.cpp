// Other includes.
#include "Main.h"

Personaje test;

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

	// Carga de modelos.
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

		// Dibujo de modelos.
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
		harley.Dibujar(modelLoc, lightingShader, harley_cuerpo, harley_cabeza, harley_brazo_l_1, harley_brazo_l_2, harley_brazo_r_1, harley_brazo_r_2, harley_pierna_l_1, harley_pierna_l_2, harley_pierna_r_1, harley_pierna_r_2);
		if (jugando) {
			harley.DibujarAccesorio(modelLoc, lightingShader, bate);
		}

		test.Dibujar(modelLoc, lightingShader, harley_cuerpo, harley_cabeza, harley_brazo_l_1, harley_brazo_l_2, harley_brazo_r_1, harley_brazo_r_2, harley_pierna_l_1, harley_pierna_l_2, harley_pierna_r_1, harley_pierna_r_2);
		test.Caminar(deltaTime);

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