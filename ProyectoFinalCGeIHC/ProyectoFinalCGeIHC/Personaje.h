#pragma once

// GLM Mathematics.
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Model.h"

void TerminarJuego();

class Personaje
{
private:
	// Transformaciones.
	glm::vec3 rotacionCabeza = glm::vec3(0.0f);
	glm::vec3 rotacionBrazoL1 = glm::vec3(15.0f, 0.0f, -75.0f);
	glm::vec3 rotacionBrazoL2 = glm::vec3(0.0f, -25.0f, 0.0f);
	glm::vec3 rotacionBrazoR1 = glm::vec3(15.0f, 0.0f, 75.0f);
	glm::vec3 rotacionBrazoR2 = glm::vec3(0.0f, 25.0f, 0.0f);
	glm::vec3 rotacionPiernaL1 = glm::vec3(0.0f);
	glm::vec3 rotacionPiernaL2 = glm::vec3(0.0f);
	glm::vec3 rotacionPiernaR1 = glm::vec3(0.0f);
	glm::vec3 rotacionPiernaR2 = glm::vec3(0.0f);

	float velocidadAnim = 100.0f;
	float tiempoAnim = 0.0f;
	float cicloAnim = 1.0f;

	int accesorio = 0;

public:
	glm::vec3 posicion = glm::vec3(0.0f, 0.92f, 0.0f);
	glm::vec3 posicionAnterior = glm::vec3(0.0f, 0.92f, 0.0f);
	glm::vec3 rotacion = glm::vec3(0.0f);

	bool caminando = false;

	void Dibujar(GLuint modelLoc, Shader& lightingShader, Model cuerpo, Model cabeza, Model brazo_l_1, Model brazo_l_2, Model brazo_r_1, Model brazo_r_2, Model pierna_l_1, Model pierna_l_2, Model pierna_r_1, Model pierna_r_2)
	{
		// Cuerpo.
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, this->posicion);
		model = glm::rotate(model, glm::radians(this->rotacion.x), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(this->rotacion.y), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(this->rotacion.z), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		cuerpo.Draw(lightingShader);

		// Cabeza.
		model = glm::translate(model, glm::vec3(0.0f, 0.507119f, -0.005981f));
		model = glm::rotate(model, glm::radians(this->rotacionCabeza.x), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(this->rotacionCabeza.y), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(this->rotacionCabeza.z), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		cabeza.Draw(lightingShader);

		// Brazo_L_1.
		model = glm::mat4(1);
		model = glm::translate(model, this->posicion);
		model = glm::rotate(model, glm::radians(this->rotacion.x), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(this->rotacion.y), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(this->rotacion.z), glm::vec3(0.0f, 0.0f, 1.0f));

		model = glm::translate(model, glm::vec3(0.107058f, 0.389674f, -0.020696f));
		model = glm::rotate(model, glm::radians(this->rotacionBrazoL1.x), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(this->rotacionBrazoL1.y), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(this->rotacionBrazoL1.z), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		brazo_l_1.Draw(lightingShader);

		// Brazo_L_2.
		model = glm::translate(model, glm::vec3(0.249121f, 0.015555f, 0.000215f));
		model = glm::rotate(model, glm::radians(this->rotacionBrazoL2.x), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(this->rotacionBrazoL2.y), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		brazo_l_2.Draw(lightingShader);

		// Brazo_R_1.
		model = glm::mat4(1);
		model = glm::translate(model, this->posicion);
		model = glm::rotate(model, glm::radians(this->rotacion.x), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(this->rotacion.y), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(this->rotacion.z), glm::vec3(0.0f, 0.0f, 1.0f));

		model = glm::translate(model, glm::vec3(-0.107058, 0.389674, -0.020696));
		model = glm::rotate(model, glm::radians(this->rotacionBrazoR1.x), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(this->rotacionBrazoR1.y), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(this->rotacionBrazoR1.z), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		brazo_r_1.Draw(lightingShader);

		// Brazo_R_2.
		model = glm::translate(model, glm::vec3(-0.249121, 0.015555, 0.000215));
		model = glm::rotate(model, glm::radians(this->rotacionBrazoR2.x), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(this->rotacionBrazoR2.y), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		brazo_r_2.Draw(lightingShader);

		// Pierna_L_1.
		model = glm::mat4(1);
		model = glm::translate(model, this->posicion);
		model = glm::rotate(model, glm::radians(this->rotacion.x), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(this->rotacion.y), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(this->rotacion.z), glm::vec3(0.0f, 0.0f, 1.0f));

		model = glm::translate(model, glm::vec3(0.06f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(this->rotacionPiernaL1.x), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(this->rotacionPiernaL1.y), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(this->rotacionPiernaL1.z), glm::vec3(0.0f, 0.0f, 1.0f));
		
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		pierna_l_1.Draw(lightingShader);

		// Pierna_L_2.
		model = glm::translate(model, glm::vec3(0.076131f - 0.06f, -0.413235f, 0.007457f));
		model = glm::rotate(model, glm::radians(this->rotacionPiernaL2.x), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(this->rotacionPiernaL2.y), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		pierna_l_2.Draw(lightingShader);

		// Pierna_R_1.
		model = glm::mat4(1);
		model = glm::translate(model, this->posicion);
		model = glm::rotate(model, glm::radians(this->rotacion.x), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(this->rotacion.y), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(this->rotacion.z), glm::vec3(0.0f, 0.0f, 1.0f));

		model = glm::translate(model, glm::vec3(-0.06f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(this->rotacionPiernaR1.x), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(this->rotacionPiernaR1.y), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(this->rotacionPiernaR1.z), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		pierna_r_1.Draw(lightingShader);

		// Pierna_R_2.
		model = glm::translate(model, glm::vec3(-0.086131f + 0.06f, -0.413235f, 0.007457f));
		model = glm::rotate(model, glm::radians(this->rotacionPiernaR2.x), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(this->rotacionPiernaR2.y), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		pierna_r_2.Draw(lightingShader);
	}

	void DibujarAccesorio(GLuint modelLoc, Shader& lightingShader, Model bate) {
		glm::mat4 model = glm::mat4(1.0f);
		// Transformaciones Brazo_R_1.
		model = glm::mat4(1);
		model = glm::translate(model, this->posicion);
		model = glm::rotate(model, glm::radians(this->rotacion.x), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(this->rotacion.y), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(this->rotacion.z), glm::vec3(0.0f, 0.0f, 1.0f));

		model = glm::translate(model, glm::vec3(-0.107058, 0.389674, -0.020696));
		model = glm::rotate(model, glm::radians(this->rotacionBrazoR1.x), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(this->rotacionBrazoR1.y), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(this->rotacionBrazoR1.z), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		// Transformaciones Brazo_R_2.
		model = glm::translate(model, glm::vec3(-0.249121, 0.015555, 0.000215));
		model = glm::rotate(model, glm::radians(this->rotacionBrazoR2.x), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(this->rotacionBrazoR2.y), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		// Accesorio.
		model = glm::translate(model, glm::vec3(-0.35, 0.0, 0.0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		switch (this->accesorio)
		{
		case 1:
			bate.Draw(lightingShader);
		default:
			break;
		}
	}

	void ReiniciarPose()
	{
		this->rotacionCabeza = glm::vec3(0.0f, 0.0f, 0.0f);

		this->rotacionBrazoL1 = glm::vec3(0.0f, 0.0f, 0.0f);

		this->rotacionBrazoL2 = glm::vec3(0.0f, 0.0f, 0.0f);

		this->rotacionBrazoR1 = glm::vec3(0.0f, 0.0f, 0.0f);

		this->rotacionBrazoR2 = glm::vec3(0.0f, 0.0f, 0.0f);

		this->rotacionPiernaL1 = glm::vec3(0.0f, 0.0f, 0.0f);

		this->rotacionPiernaL2 = glm::vec3(0.0f, 0.0f, 0.0f);

		this->rotacionPiernaR1 = glm::vec3(0.0f, 0.0f, 0.0f);

		this->rotacionPiernaR2 = glm::vec3(0.0f, 0.0f, 0.0f);

		this->tiempoAnim = 0.0f;
		this->cicloAnim = 1.0f;
	}

	void PoseIdle()
	{
		ReiniciarPose();

		this->rotacionBrazoL1 = glm::vec3(15.0f, 0.0f, -75.0f);
		this->rotacionBrazoL2.y = -25.0f;

		this->rotacionBrazoR1 = glm::vec3(15.0f, 0.0f, 75.0f);
		this->rotacionBrazoR2.y = 25.0f;
	}

	void ComenzarCaminata()
	{
		ReiniciarPose();

		this->rotacionBrazoL1.x = 35.0f;
		this->rotacionBrazoL1.z = -75.0f;

		this->rotacionBrazoL2.y = -43.0f;

		this->rotacionBrazoR1.x = 10.0f;
		this->rotacionBrazoR1.z = 75.0f;

		this->rotacionBrazoR2.y = 30.0f;

		this->rotacionPiernaL1.x = -30.0f;

		this->rotacionPiernaL2.x = 15.0f;

		this->rotacionPiernaR1.x = 10.0f;

		this->rotacionPiernaR2.x = 35.0f;

		this->caminando = true;

	}

	void Caminar(float deltaTime)
	{
		this->tiempoAnim += deltaTime;

		this->rotacionBrazoL1.x += -50.0f * cicloAnim * deltaTime;
		rotacionBrazoL2.y += 30.0f * cicloAnim * deltaTime;

		this->rotacionBrazoR1.x += 50.0f * cicloAnim * deltaTime;
		rotacionBrazoR2.y += 30.0f * cicloAnim * deltaTime;

		this->rotacionPiernaL1.x += 80.0f * cicloAnim * deltaTime;
		rotacionPiernaL2.x += 40.0f * cicloAnim * deltaTime;

		this->rotacionPiernaR1.x += -80.0f * cicloAnim * deltaTime;
		rotacionPiernaR2.x += -40.0f * cicloAnim * deltaTime;

		if (this->tiempoAnim >= 0.5f)
		{
			this->cicloAnim = cicloAnim * -1.0f;
			this->tiempoAnim = 0.0f;
		}
	}

	void PoseSentada()
	{
		ReiniciarPose();

		this->rotacionPiernaL1.x = -90.0f;
		this->rotacionPiernaL2.x = 90.0f;

		this->rotacionPiernaR1.x = -90.0f;
		this->rotacionPiernaR2.x = 90.0f;
	}

	void ComenzarBateo()
	{
		ReiniciarPose();

		this->rotacionBrazoL1.z = -70.0f;

		this->rotacionBrazoR1.x = -180.0f;
	}

	void Batear(float deltaTime)
	{
		this->tiempoAnim += deltaTime;

		this->rotacion.y += 20.0f * cicloAnim * deltaTime;
		this->rotacionBrazoR1.y += -50.0f * cicloAnim * deltaTime;

		if (this->tiempoAnim >= 2.0f) {
			TerminarJuego();
		}
	}

	void ComenzarTopos()
	{

	}

	void GolpearTopos(float deltaTime)
	{

	}

	void ComenzarHachas()
	{

	}

	void LanzarHachas(float deltaTime)
	{

	}

	void ComenzarBoliche()
	{

	}

	void JugarBoliche(float deltaTime)
	{

	}

	void ComenzarDados()
	{

	}

	void LanzarDados(float deltaTime)
	{

	}

	void ComenzarDardos()
	{

	}

	void LanzarDardos(float deltaTime)
	{

	}
};