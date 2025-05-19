#pragma once

// GLM Mathematics.
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Model.h"

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

	float cicloAnim = 1.0f;

public:
	glm::vec3 posicion = glm::vec3(0.0f, 0.92f, 0.0f);
	glm::vec3 posicionAnterior = glm::vec3(0.0f, 0.92f, 0.0f);
	glm::vec3 rotacion = glm::vec3(0.0f);

	void Dibujar(GLuint modelLoc, Shader& lightingShader, Model piezas[10], Model accesorio)
	{
		// Cuerpo.
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, this->posicion);
		model = glm::rotate(model, glm::radians(this->rotacion.x), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(this->rotacion.y), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(this->rotacion.z), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		piezas[0].Draw(lightingShader);

		// Cabeza.
		model = glm::translate(model, glm::vec3(0.0f, 0.507119f, -0.005981f));
		model = glm::rotate(model, glm::radians(this->rotacionCabeza.x), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(this->rotacionCabeza.y), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(this->rotacionCabeza.z), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		piezas[1].Draw(lightingShader);

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
		piezas[2].Draw(lightingShader);

		// Brazo_L_2.
		model = glm::translate(model, glm::vec3(0.249121f, 0.015555f, 0.000215f));
		model = glm::rotate(model, glm::radians(this->rotacionBrazoL2.x), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(this->rotacionBrazoL2.y), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		piezas[3].Draw(lightingShader);

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
		piezas[4].Draw(lightingShader);

		// Brazo_R_2.
		model = glm::translate(model, glm::vec3(-0.249121, 0.015555, 0.000215));
		model = glm::rotate(model, glm::radians(this->rotacionBrazoR2.x), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(this->rotacionBrazoR2.y), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		piezas[5].Draw(lightingShader);

		// Accesorio.
		accesorio.Draw(lightingShader);

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
		piezas[6].Draw(lightingShader);

		// Pierna_L_2.
		model = glm::translate(model, glm::vec3(0.076131f - 0.06f, -0.413235f, 0.007457f));
		model = glm::rotate(model, glm::radians(this->rotacionPiernaL2.x), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(this->rotacionPiernaL2.y), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		piezas[7].Draw(lightingShader);

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
		piezas[8].Draw(lightingShader);

		// Pierna_R_2.
		model = glm::translate(model, glm::vec3(-0.086131f + 0.06f, -0.413235f, 0.007457f));
		model = glm::rotate(model, glm::radians(this->rotacionPiernaR2.x), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(this->rotacionPiernaR2.y), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		piezas[9].Draw(lightingShader);
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
	}

	void Caminar(float deltaTime)
	{
		this->rotacionBrazoL1.x += -25.0f / 0.5f * cicloAnim * deltaTime;
		rotacionBrazoL2.y += 15.0f / 0.5f * cicloAnim * deltaTime;

		this->rotacionBrazoR1.x += 25.0f / 0.5f * cicloAnim * deltaTime;
		rotacionBrazoR2.y += 15.0f * cicloAnim * deltaTime;

		this->rotacionPiernaL1.x += 40.0f / 0.5f * cicloAnim * deltaTime;
		rotacionPiernaL2.x += 20.0f * cicloAnim * deltaTime;

		this->rotacionPiernaR1.x += -40.0f / 0.5f * cicloAnim * deltaTime;
		rotacionPiernaR2.x += -20.0f / 0.5f * cicloAnim * deltaTime;

		if (this->rotacionPiernaL1.x >= 10.0f)
		{
			this->cicloAnim = -1.0f;
		}
		if (this->rotacionPiernaL1.x <= -30.0f)
		{
			this->cicloAnim = 1.0f;
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

	void PagarBoleto(float deltaTime)
	{
		if (rotacionBrazoR1.x >= -45.0f)
		{
			this->rotacionBrazoR1.x += -45.0f / 0.2 * deltaTime;
			this->rotacionBrazoR2.y += 25.0f / 0.2 * deltaTime;
		}
	}

	void AlzarBate(float deltaTime)
	{
		if (rotacionBrazoR1.x >= 0.0f)
		{
			this->rotacionBrazoR1.x += -15.0f / 0.33 * deltaTime;
			this->rotacionBrazoR1.y += 90.0f / 0.33 * deltaTime;
			this->rotacionBrazoR1.z += -75.0f / 0.33 * deltaTime;
			this->rotacionBrazoR2.y += 65.0f / 0.33 * deltaTime;

			this->rotacionBrazoL1.x += 30.0f / 0.33 * deltaTime;
			this->rotacionBrazoL2.y += -20.0f / 0.33 * deltaTime;

			this->rotacionPiernaL1.x += 15.0f / 0.33f * deltaTime;

			this->rotacionPiernaR1.x += -15.0f / 0.33f * deltaTime;
			this->rotacionPiernaR2.x += 15.0f / 0.33f * deltaTime;
		}
	}

	void Batear(float deltaTime)
	{
		if (rotacionBrazoR1.y >= -20.0f)
		{
			this->rotacionBrazoR1.y += -110.0f / 0.25 * deltaTime;
			this->rotacionBrazoR2.y += -90.0f / 0.25 * deltaTime;

			this->rotacionBrazoL1.x += -55.0f / 0.25 * deltaTime;
			this->rotacionBrazoL1.z += 25.0f / 0.25 * deltaTime;
			this->rotacionBrazoL2.y += 25.0f / 0.25 * deltaTime;
		}
	}

	void RegresarBate(float deltaTime)
	{
		if (rotacionBrazoR1.y <= 90.0f)
		{
			this->rotacionBrazoR1.y += 110.0f / 0.33 * deltaTime;
			this->rotacionBrazoR2.y += 90.0f / 0.33 * deltaTime;

			this->rotacionBrazoL1.x += 55.0f / 0.33 * deltaTime;
			this->rotacionBrazoL1.z += -25.0f / 0.33 * deltaTime;
			this->rotacionBrazoL2.y += -25.0f / 0.33 * deltaTime;
		}
	}

	void ComenzarTopos()
	{
		ReiniciarPose();

		this->rotacionCabeza.x = 15.0f;

		this->rotacionBrazoL1 = glm::vec3(15.0f, 0.0f, -75.0f);
		this->rotacionBrazoL2.y = -25.0f;

		this->rotacionBrazoR1.x = -30.0f;
		this->rotacionBrazoR1.y = 15.0f;
		this->rotacionBrazoR1.z = 90.0f;
	}

	void AlzarMartillo(float deltaTime)
	{
		if (this->rotacionBrazoR1.x >= -100.0f)
		{
			this->rotacionBrazoR1.x += -70.0f / 0.5f * deltaTime;
			this->rotacionBrazoR1.y += -15.0f / 0.5f * deltaTime;
			this->rotacionBrazoR2.y += 90.0f / 0.5f * deltaTime;
		}
	}

	void GolpearTopo(float deltaTime)
	{
		if (rotacionBrazoR1.x <= -30.0f)
		{
			this->rotacionBrazoR1.x += 70.0f / 0.33f * deltaTime;
			this->rotacionBrazoR1.y += 15.0f / 0.33f * deltaTime;

			this->rotacionBrazoR2.y += -90.0f / 0.33f * deltaTime;
		}
	}

	void AlzarHacha(float deltaTime)
	{
		if (this->rotacionBrazoR1.x >= -130.0f)
		{
			this->rotacionBrazoL1.x += 45.0f / 0.33f * deltaTime;
			this->rotacionBrazoL2.y += -45.0f / 0.33f * deltaTime;

			this->rotacionBrazoR1.x += -130.0f / 0.33f * deltaTime;
			this->rotacionBrazoR1.z += 15.0f / 0.33f * deltaTime;
			this->rotacionBrazoR2.y += 90.0f / 0.33f * deltaTime;

			this->rotacionPiernaL1.x += -15.0f / 0.33f * deltaTime;
			this->rotacionPiernaL2.x += 15.0f / 0.33f * deltaTime;

			this->rotacionPiernaR1.x += 15.0f / 0.33f * deltaTime;
		}
	}

	void LanzarHacha(float deltaTime)
	{
		if (rotacionBrazoR1.x <= 50.0f)
		{
			this->rotacionBrazoR1.x += 180.0f / 0.25 * deltaTime;
			this->rotacionBrazoR1.z += -10.0f / 0.25 * deltaTime;
			this->rotacionBrazoR2.y += -65.0f / 0.25 * deltaTime;

			this->rotacionBrazoL1.x += -55.0f / 0.25 * deltaTime;
		}
	}

	void AlzarBola(float deltaTime)
	{
		if (this->rotacionBrazoR1.x <= 75.0f)
		{
			this->rotacionBrazoL1.x += -35.0f / 0.5f * deltaTime;
			this->rotacionBrazoL2.y += -20.0f / 0.5f * deltaTime;

			this->rotacionBrazoR1.x += 60.0f / 0.5f * deltaTime;

			this->rotacionPiernaL1.x += 15.0f / 0.5f * deltaTime;

			this->rotacionPiernaR1.x += -15.0f / 0.5f * deltaTime;
			this->rotacionPiernaR2.x += 15.0f / 0.5f * deltaTime;
		}
	}

	void LanzarBola(float deltaTime)
	{
		if (rotacionBrazoR1.x >= -130.0f)
		{
			this->rotacionBrazoR1.x += -205.0f / 0.5f * deltaTime;

			this->rotacionBrazoL1.x += 80.0f / 0.5f * deltaTime;
		}
	}

	void ComenzaDados()
	{
		ReiniciarPose();

		this->rotacionBrazoL1 = glm::vec3(15.0f, 0.0f, -75.0f);
		this->rotacionBrazoL2.y = -25.0f;

		this->rotacionBrazoR1 = glm::vec3(-70.0f, 0.0f, 75.0f);
		this->rotacionBrazoR2.y = 120.0f;
	}

	void AgitarDados(float deltaTime)
	{
		this->rotacionBrazoR2.y += -50.0f / 0.25f * cicloAnim * deltaTime;
		if (this->rotacionBrazoR2.y <= 70.0f)
		{
			cicloAnim = -1.0f;
		}
		if (this->rotacionBrazoR2.y >= 120.0f)
		{
			cicloAnim = 1.0f;
		}
	}

	void LanzarDados(float deltaTime)
	{
		if (this->rotacionBrazoR2.y >= 5.0f)
		{
			this->rotacionBrazoR2.y += -70.0f / 0.15f * deltaTime;
		}
	}

	void ComenzarDardos()
	{
		ReiniciarPose();

		this->rotacionBrazoL1 = glm::vec3(15.0f, 0.0f, -75.0f);
		this->rotacionBrazoL2.y = -25.0f;

		this->rotacionBrazoR1.y = 90.0f;
		this->rotacionBrazoR2.y = 120.0f;
	}

	void LanzarDardos(float deltaTime)
	{
		if (rotacionBrazoR1.y <= -20.0f)
		{
			cicloAnim = -1.0f;
		}
		if (rotacionBrazoR1.y >= 90.0f)
		{
			cicloAnim = 1.0f;
		}
		this->rotacionBrazoR1.y += -110.0f / 0.33 * cicloAnim * deltaTime;
		this->rotacionBrazoR2.y += -90.0f / 0.33 * cicloAnim * deltaTime;
	}

};