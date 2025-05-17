// Other includes.
#include "Main.h"

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

	Model vacio((char*)"Modelos/Vacio.obj");

	// Elementos de Entorno.
	Model suelo((char*)"Modelos/Suelo.obj");
	Model reja((char*)"Modelos/Reja.obj");

	// Comida.
	Model puesto_comida((char*)"Modelos/Puesto_Comida.obj");
	Model mesa_picnic((char*)"Modelos/Mesa_Picnic.obj");

	// Stand Tickets.
	Model stand_tickets((char*)"Modelos/Stand_Tickets.obj");
	Model token((char*)"Modelos/Token.obj");
	Model ticket((char*)"Modelos/Ticket.obj");

	// Jaula Bateo.
	Model jaula_bateo((char*)"Modelos/Jaula_Bateo.obj");
	Model bate((char*)"Modelos/Bate.obj");
	Model pelota((char*)"Modelos/Pelota.obj");

	// Maquina Topos.
	Model maquina_topos((char*)"Modelos/Maquina_Topos.obj");
	Model martillo((char*)"Modelos/Martillo.obj");

	// Hachas.
	Model cabina_hachas((char*)"Modelos/Cabina_Hachas.obj");
	Model hacha((char*)"Modelos/Hacha.obj");

	// Boliche.
	Model pista_boliche((char*)"Modelos/Pista_Boliche.obj");
	Model bola_boliche((char*)"Modelos/Bola_Boliche.obj");
	Model bolo((char*)"Modelos/Bolo.obj");

	// Dados.
	Model mesa_dados((char*)"Modelos/Mesa_Dados.obj");
	Model dado((char*)"Modelos/Dado.obj");

	// Dardos.
	Model puesto_dardos((char*)"Modelos/Puesto_Dardos.obj");
	Model dardo((char*)"Modelos/Dardo.obj");
	Model globo((char*)"Modelos/Globo.obj");

	//Objetos Lanzables
	Model objetos[] = { vacio, bate, martillo, hacha, bola_boliche, dado, dardo, token };

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

	Model piezas_harley[10] = { harley_cuerpo, harley_cabeza, harley_brazo_l_1, harley_brazo_l_2, harley_brazo_r_1, harley_brazo_r_2, harley_pierna_l_1, harley_pierna_l_2, harley_pierna_r_1, harley_pierna_r_2 };

	// Puro Hueso.
	Model purohueso_cuerpo((char*)"Modelos/PuroHueso_Cuerpo.obj");
	Model purohueso_cabeza((char*)"Modelos/PuroHueso_Cabeza.obj");
	Model purohueso_brazo_l_1((char*)"Modelos/PuroHueso_Brazo_L_1.obj");
	Model purohueso_brazo_l_2((char*)"Modelos/PuroHueso_Brazo_L_2.obj");
	Model purohueso_brazo_r_1((char*)"Modelos/PuroHueso_Brazo_R_1.obj");
	Model purohueso_brazo_r_2((char*)"Modelos/PuroHueso_Brazo_R_2.obj");

	Model piezas_purohueso[10] = { purohueso_cuerpo, purohueso_cabeza, purohueso_brazo_l_1, purohueso_brazo_l_2, purohueso_brazo_r_1, purohueso_brazo_r_2, vacio, vacio, vacio, vacio };

	purohueso.posicion = posicionMaquinaTopos + glm::vec3(1.0f, 0.92f, 6.0f);
	purohueso.rotacion.y = rotacionMaquinaTopos + 180.f;
	purohueso.ComenzarBateo();

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
		RevisarHora();

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

		//glEnable(GL_BLEND); // Activa la funcionalidad para trabajar el canal alfa.
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//glDisable(GL_BLEND); // Desactiva el canal alfa.

		// Suelo.
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		suelo.Draw(lightingShader);

		// Comida.
		DibujarEstructura(modelLoc, lightingShader, puesto_comida, glm::vec3(2.0f, 0.0f, 17.0f), 90.0f);
		DibujarEstructura(modelLoc, lightingShader, puesto_comida, glm::vec3(2.0f, 0.0f, 23.0f), 90.0f);
		DibujarEstructura(modelLoc, lightingShader, puesto_comida, glm::vec3(2.0f, 0.0f, 90.0f), 90.0f);
		DibujarEstructura(modelLoc, lightingShader, puesto_comida, glm::vec3(-2.0f, 0.0f, 17.0f), -90.0f);
		DibujarEstructura(modelLoc, lightingShader, puesto_comida, glm::vec3(-2.0f, 0.0f, 23.0f), -90.0f);
		DibujarEstructura(modelLoc, lightingShader, puesto_comida, glm::vec3(-2.0f, 0.0f, 90.0f), -90.0f);

		DibujarEstructura(modelLoc, lightingShader, puesto_comida, glm::vec3(17.0f, 0.0f, 30.0f), -90.0f);
		DibujarEstructura(modelLoc, lightingShader, puesto_comida, glm::vec3(17.0f, 0.0f, 36.0f), -90.0f);
		DibujarEstructura(modelLoc, lightingShader, puesto_comida, glm::vec3(17.0f, 0.0f, 42.0f), -90.0f);

		DibujarEstructura(modelLoc, lightingShader, mesa_picnic, glm::vec3(12.0f, 0.0f, 30.0f), -90.0f);
		DibujarEstructura(modelLoc, lightingShader, mesa_picnic, glm::vec3(12.0f, 0.0f, 33.0f), -90.0f);
		DibujarEstructura(modelLoc, lightingShader, mesa_picnic, glm::vec3(12.0f, 0.0f, 36.0f), -90.0f);
		DibujarEstructura(modelLoc, lightingShader, mesa_picnic, glm::vec3(12.0f, 0.0f, 39.0f), -90.0f);
		DibujarEstructura(modelLoc, lightingShader, mesa_picnic, glm::vec3(12.0f, 0.0f, 42.0f), -90.0f);

		// Puestos de Interacción.
		DibujarEstructura(modelLoc, lightingShader, stand_tickets, posicionStandBateo, rotacionStandBateo);
		DibujarEstructura(modelLoc, lightingShader, stand_tickets, posicionStandTopos, rotacionStandTopos);
		DibujarEstructura(modelLoc, lightingShader, stand_tickets, posicionStandHachas, rotacionStandHachas);
		DibujarEstructura(modelLoc, lightingShader, stand_tickets, posicionStandBoliche, rotacionStandBoliche);
		DibujarEstructura(modelLoc, lightingShader, stand_tickets, posicionStandDados, rotacionStandDados);
		DibujarEstructura(modelLoc, lightingShader, stand_tickets, posicionStandDardos, rotacionStandDardos);

		// Juegos Interactivos.
		DibujarEstructura(modelLoc, lightingShader, maquina_topos, posicionMaquinaTopos, rotacionMaquinaTopos); // Juego de Topos.
		DibujarEstructura(modelLoc, lightingShader, maquina_topos, posicionMaquinaTopos + glm::vec3(0.0f, 0.0f, 1.5f), rotacionMaquinaTopos);
		DibujarEstructura(modelLoc, lightingShader, maquina_topos, posicionMaquinaTopos + glm::vec3(0.0f, 0.0f, 3.0f), rotacionMaquinaTopos);
		DibujarEstructura(modelLoc, lightingShader, maquina_topos, posicionMaquinaTopos + glm::vec3(0.0f, 0.0f, 4.5f), rotacionMaquinaTopos);
		DibujarEstructura(modelLoc, lightingShader, maquina_topos, posicionMaquinaTopos + glm::vec3(0.0f, 0.0f, 6.0f), rotacionMaquinaTopos);

		DibujarEstructura(modelLoc, lightingShader, pista_boliche, posicionPistaBoliche, rotacionPistaBoliche); // Juego de Boliche.
		DibujarEstructura(modelLoc, lightingShader, mesa_dados, posicionMesaDados, rotacionMesaDados); // Juego de Dados.
		DibujarEstructura(modelLoc, lightingShader, puesto_dardos, posicionPuestoDardos, rotacionPuestoDardos); // Juego de Dardos.

		// Elementos con Transparencia.
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 1);
		DibujarEstructura(modelLoc, lightingShader, reja, glm::vec3(0.0f), 0.0f);
		DibujarEstructura(modelLoc, lightingShader, jaula_bateo, posicionJaulaBateo, rotacionJaulaBateo); // Juego de Bateo.
		DibujarEstructura(modelLoc, lightingShader, cabina_hachas, posicionCabinaHachas, rotacionCabinaHachas); // Juego de Hachas.	
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);

		// Dibuja a Harley.
		harley.Dibujar(modelLoc, lightingShader, piezas_harley, objetos[accesorioActivo]);
		// Anima a Harley.
		if (not jugando && not pagando)
		{
			MoverHarley();
			ChecarMovimiento();
		}
		else if (jugando)
		{
			AnimarJuego(modelLoc, lightingShader, objetos);
		}
		else if (pagando)
		{
			AnimarPago();
		}

		// Dibuja a Puro Hueso.
		purohueso.Dibujar(modelLoc, lightingShader, piezas_purohueso, vacio);
		//purohueso.Batear(deltaTime);

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