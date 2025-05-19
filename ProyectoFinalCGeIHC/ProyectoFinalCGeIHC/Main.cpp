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
	Model skydome((char*)"Modelos/Skydome.obj");
	Model reja((char*)"Modelos/Reja.obj");

	// Comida.
	Model puesto_comida((char*)"Modelos/Puesto_Comida.obj");
	Model mesa_picnic((char*)"Modelos/Mesa_Picnic.obj");

	// Stand Tickets.
	Model stand_tickets((char*)"Modelos/Stand_Tickets.obj");
	Model token_mano((char*)"Modelos/Token_Mano.obj");
	Model ticket((char*)"Modelos/Ticket.obj");

	// Jaula Bateo.
	Model jaula_bateo((char*)"Modelos/Jaula_Bateo.obj");
	Model bate_mano((char*)"Modelos/Bate_Mano.obj");
	Model pelota((char*)"Modelos/Pelota.obj");
	Model mr_freeze((char*)"Modelos/Mr_Freeze.obj");
	Model mr_freeze_casco((char*)"Modelos/Mr_Freeze_Casco.obj");

	// Maquina Topos.
	Model maquina_topos((char*)"Modelos/Maquina_Topos.obj");
	Model topo((char*)"Modelos/Topo.obj");
	Model martillo_mano((char*)"Modelos/Martillo_Mano.obj");

	// Hachas.
	Model cabina_hachas((char*)"Modelos/Cabina_Hachas.obj");
	Model hacha_mano((char*)"Modelos/Hacha_Mano.obj");
	Model hacha((char*)"Modelos/Hacha.obj");

	// Boliche.
	Model pista_boliche((char*)"Modelos/Pista_Boliche.obj");
	Model bola_boliche_mano((char*)"Modelos/Bola_Boliche_Mano.obj");
	Model bola_boliche((char*)"Modelos/Bola_Boliche.obj");
	Model bolo((char*)"Modelos/Bolo.obj");

	// Dados.
	Model mesa_dados((char*)"Modelos/Mesa_Dados.obj");
	Model dados_mano((char*)"Modelos/Dados_Mano.obj");
	Model dado((char*)"Modelos/Dado.obj");
	Model dados((char*)"Modelos/Dados.obj");

	// Dardos.
	Model puesto_dardos((char*)"Modelos/Puesto_Dardos.obj");
	Model dardos_mano((char*)"Modelos/Dardos_Mano.obj");
	Model dardo((char*)"Modelos/Dardo.obj");
	Model globo((char*)"Modelos/Globo.obj");

	// Objetos Lanzables.
	Model objetos[] = { vacio, pelota, vacio, hacha, bola_boliche, dado, dardo };

	// Objetos en Mano.
	Model accesorios[] = { vacio, bate_mano, martillo_mano, hacha_mano, bola_boliche_mano, dados_mano, dardos_mano, token_mano };

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
	purohueso.ComenzarToposGuadania();

	// Set texture units.
	lightingShader.Use();

	glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 5000.0f);

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

		// Cielo.
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), colorCielo.r, colorCielo.g, colorCielo.b, 1.0f);
		skydome.Draw(lightingShader);

		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);

		// Comida.
		DibujarEstructura(modelLoc, lightingShader, puesto_comida, glm::vec3(2.0f, 0.0f, 17.0f), 90.0f);
		DibujarEstructura(modelLoc, lightingShader, puesto_comida, glm::vec3(2.0f, 0.0f, 23.0f), 90.0f);
		DibujarEstructura(modelLoc, lightingShader, puesto_comida, glm::vec3(2.0f, 0.0f, 29.0f), 90.0f);
		DibujarEstructura(modelLoc, lightingShader, puesto_comida, glm::vec3(-2.0f, 0.0f, 17.0f), -90.0f);
		DibujarEstructura(modelLoc, lightingShader, puesto_comida, glm::vec3(-2.0f, 0.0f, 23.0f), -90.0f);
		DibujarEstructura(modelLoc, lightingShader, puesto_comida, glm::vec3(-2.0f, 0.0f, 29.0f), -90.0f);

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
		DibujarMaquinaTopos(modelLoc, lightingShader, maquina_topos, topo, posicionMaquinaTopos, rotacionMaquinaTopos); // Juego de Topos.
		DibujarMaquinaTopos(modelLoc, lightingShader, maquina_topos, topo, posicionMaquinaTopos + glm::vec3(0.0f, 0.0f, 1.5f), rotacionMaquinaTopos);
		DibujarMaquinaTopos(modelLoc, lightingShader, maquina_topos, topo, posicionMaquinaTopos + glm::vec3(0.0f, 0.0f, 3.0f), rotacionMaquinaTopos);
		DibujarMaquinaTopos(modelLoc, lightingShader, maquina_topos, topo, posicionMaquinaTopos + glm::vec3(0.0f, 0.0f, 4.5f), rotacionMaquinaTopos);
		DibujarMaquinaTopos(modelLoc, lightingShader, maquina_topos, topo, posicionMaquinaTopos + glm::vec3(0.0f, 0.0f, 6.0f), rotacionMaquinaTopos);
		AnimarTopos();

		// Pista de Boliche.
		model = glm::mat4(1);
		model = glm::translate(model, posicionPistaBoliche);
		model = glm::rotate(model, glm::radians(rotacionPistaBoliche), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		pista_boliche.Draw(lightingShader);

		// Bolos.
		// Bolo 1.
		model = glm::mat4(1);
		model = glm::translate(model, posicionPistaBoliche);
		model = glm::rotate(model, glm::radians(rotacionPistaBoliche), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-0.9f, 1.62f, -8.95f) + posicionBolo1);
		model = glm::rotate(model, glm::radians(rotacionBolos), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		bolo.Draw(lightingShader);

		// Bolo 2.
		model = glm::mat4(1);
		model = glm::translate(model, posicionPistaBoliche);
		model = glm::rotate(model, glm::radians(rotacionPistaBoliche), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-1.05f, 1.62f, -9.1f) + posicionBolo2);
		model = glm::rotate(model, glm::radians(rotacionBolos), glm::vec3(1.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		bolo.Draw(lightingShader);

		// Bolo 3.
		model = glm::mat4(1);
		model = glm::translate(model, posicionPistaBoliche);
		model = glm::rotate(model, glm::radians(rotacionPistaBoliche), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-0.75f, 1.62f, -9.1f) + posicionBolo3);
		model = glm::rotate(model, glm::radians(rotacionBolos), glm::vec3(1.0f, 0.0f, -1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		bolo.Draw(lightingShader);

		// Bolo 4.
		model = glm::mat4(1);
		model = glm::translate(model, posicionPistaBoliche);
		model = glm::rotate(model, glm::radians(rotacionPistaBoliche), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-0.9f, 1.62f, -9.25f) + posicionBolo4);
		model = glm::rotate(model, glm::radians(rotacionBolos), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		bolo.Draw(lightingShader);

		// Bolo 5.
		model = glm::mat4(1);
		model = glm::translate(model, posicionPistaBoliche);
		model = glm::rotate(model, glm::radians(rotacionPistaBoliche), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-1.20f, 1.62f, -9.25f) + posicionBolo5);
		model = glm::rotate(model, glm::radians(rotacionBolos), glm::vec3(1.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		bolo.Draw(lightingShader);

		// Bolo 6.
		model = glm::mat4(1);
		model = glm::translate(model, posicionPistaBoliche);
		model = glm::rotate(model, glm::radians(rotacionPistaBoliche), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-0.6f, 1.62f, -9.25f) + posicionBolo6);
		model = glm::rotate(model, glm::radians(rotacionBolos), glm::vec3(1.0f, 0.0f, -1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		bolo.Draw(lightingShader);

		// Bolo 7.
		model = glm::mat4(1);
		model = glm::translate(model, posicionPistaBoliche);
		model = glm::rotate(model, glm::radians(rotacionPistaBoliche), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-1.05f, 1.62f, -9.4f) + posicionBolo7);
		model = glm::rotate(model, glm::radians(rotacionBolos), glm::vec3(1.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		bolo.Draw(lightingShader);

		// Bolo 8.
		model = glm::mat4(1);
		model = glm::translate(model, posicionPistaBoliche);
		model = glm::rotate(model, glm::radians(rotacionPistaBoliche), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-0.75f, 1.62f, -9.4f) + posicionBolo8);
		model = glm::rotate(model, glm::radians(rotacionBolos), glm::vec3(1.0f, 0.0f, -1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		bolo.Draw(lightingShader);

		// Bolo 9.
		model = glm::mat4(1);
		model = glm::translate(model, posicionPistaBoliche);
		model = glm::rotate(model, glm::radians(rotacionPistaBoliche), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-1.35f, 1.62f, -9.4f) + posicionBolo9);
		model = glm::rotate(model, glm::radians(rotacionBolos), glm::vec3(1.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		bolo.Draw(lightingShader);

		// Bolo 10.
		model = glm::mat4(1);
		model = glm::translate(model, posicionPistaBoliche);
		model = glm::rotate(model, glm::radians(rotacionPistaBoliche), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-0.45f, 1.62f, -9.4f) + posicionBolo10);
		model = glm::rotate(model, glm::radians(rotacionBolos), glm::vec3(1.0f, 0.0f, -1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		bolo.Draw(lightingShader);

		// Mesa de Dados.
		model = glm::mat4(1);
		model = glm::translate(model, posicionMesaDados);
		model = glm::rotate(model, glm::radians(rotacionMesaDados), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		mesa_dados.Draw(lightingShader);

		// Dados en la mesa.
		model = glm::translate(model, glm::vec3(0.0f, 0.85f, 0.0f));
		model = glm::scale(model, escalaDados);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		dados.Draw(lightingShader);

		// Puesto Dardos.
		model = glm::mat4(1);
		model = glm::translate(model, posicionPuestoDardos);
		model = glm::rotate(model, glm::radians(rotacionPuestoDardos), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		puesto_dardos.Draw(lightingShader);

		// Globo 1.
		model = glm::mat4(1);
		model = glm::translate(model, posicionPuestoDardos);
		model = glm::rotate(model, glm::radians(rotacionPuestoDardos), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, 1.3f, -0.9f));
		model = glm::scale(model, escalaGlobo1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		globo.Draw(lightingShader);

		// Globo 2.
		model = glm::mat4(1);
		model = glm::translate(model, posicionPuestoDardos);
		model = glm::rotate(model, glm::radians(rotacionPuestoDardos), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-0.375f, 1.3f, -0.9f));
		model = glm::scale(model, escalaGlobo2);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		globo.Draw(lightingShader);

		// Globo 3.
		model = glm::mat4(1);
		model = glm::translate(model, posicionPuestoDardos);
		model = glm::rotate(model, glm::radians(rotacionPuestoDardos), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.375f, 1.3f, -0.9f));
		model = glm::scale(model, escalaGlobo3);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		globo.Draw(lightingShader);

		// Globo 4.
		model = glm::mat4(1);
		model = glm::translate(model, posicionPuestoDardos);
		model = glm::rotate(model, glm::radians(rotacionPuestoDardos), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-0.75f, 1.3f, -0.9f));
		model = glm::scale(model, escalaGlobo4);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		globo.Draw(lightingShader);

		// Globo 5.
		model = glm::mat4(1);
		model = glm::translate(model, posicionPuestoDardos);
		model = glm::rotate(model, glm::radians(rotacionPuestoDardos), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.75f, 1.3f, -0.9f));
		model = glm::scale(model, escalaGlobo5);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		globo.Draw(lightingShader);

		// Mr Freeze.
		DibujarEstructura(modelLoc, lightingShader, mr_freeze, posicionJaulaBateo + glm::vec3(0.0f, 0.1f, -4.0f), rotacionJaulaBateo);

		// Casco Mr Freeze.
		glEnable(GL_BLEND); // Activa la funcionalidad para trabajar el canal alfa.
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 0.1f);
		DibujarEstructura(modelLoc, lightingShader, mr_freeze_casco, posicionMrFreeze, rotacionMrFreeze);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		glDisable(GL_BLEND); // Desactiva el canal alfa.

		// Elementos con Transparencia.
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 1);
		DibujarEstructura(modelLoc, lightingShader, reja, glm::vec3(0.0f), 0.0f);	// Reja.
		DibujarEstructura(modelLoc, lightingShader, jaula_bateo, posicionJaulaBateo, rotacionJaulaBateo); // Juego de Bateo.
		DibujarEstructura(modelLoc, lightingShader, cabina_hachas, posicionCabinaHachas, rotacionCabinaHachas); // Cabina de Hachas.	
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);

		// Dibuja a Harley.
		harley.Dibujar(modelLoc, lightingShader, piezas_harley, accesorios[accesorioActivo]);
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
		purohueso.UsarGuadania(deltaTime);

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