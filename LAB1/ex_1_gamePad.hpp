#pragma once
#include "glew.h"
#include <GLFW/glfw3.h>
#include "glm.hpp"

#include "Shader_Loader.h"
#include "Render_Utils.h"

GLuint program; // Shader ID

GLuint quadVAO;
GLuint quadVAO2;

Core::Shader_Loader shaderLoader;
float transA = 0;
float transB = 0;
float rotate = 0;
float scale = 1;
float triger = 0;

float r = 0.0;
float g = 0.0;
float b = 0.0;

void renderScene(GLFWwindow* window)
{
	if (r < 1 && g <= 0 && b <= 0) {
		r = r + 0.0005;
	}
	else if (r >= 1 && g < 1 && b <= 0) {
		g = g + 0.0005;
	}
	else if (r > 0 && g >= 1 && b <= 0) {
		r = r - 0.0005;
	}
	else if (r <= 0 && g >= 1 && b < 1) {
		b = b + 0.0005;
	}
	else if (r <= 0 && g > 0 && b >= 1) {
		g = g - 0.0005;
	}
	else if (r < 1 && g <= 0 && b >= 1) {
		r = r + 0.0005;
	}
	else if (r >= 1 && g <= 0 && b > 0) {
		b = b - 0.0005;
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(r, g, b, 1.0f);

	// Zmienna "time" przechowuje czas ktory uplynal od uruchomienia aplikacji
	float time = glfwGetTime();

	glUseProgram(program);

	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// ! Macierz translation jest definiowana wierszowo dla poprawy czytelnosci. OpenGL i GLM domyslnie stosuje macierze kolumnowe, dlatego musimy ja transponowac !
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	glm::mat4 rotation =
	{scale* cos(rotate),scale*-sin(rotate),0,transA,
	 scale*sin(rotate),scale*cos(rotate),0,transB,
	  0,0,1,0,
	  0,0,0,1 };
	rotation = glm::transpose(rotation);

	glUniformMatrix4fv(glGetUniformLocation(program, "transformation"), 1, GL_FALSE, (float*)&rotation);

	// Uzyj kodu z poprzednich cwiczen do narysowania czworokata
	Core::drawVAOIndexed(quadVAO, 6);
	
	glUseProgram(0);

	glfwSwapBuffers(window);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void init(GLFWwindow* window) {
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	program = shaderLoader.CreateProgram("shaders/shader_1_2.vert", "shaders/shader_1_2.frag");

	//Przekopiuj kod do ladowania z poprzedniego zadania
	const float tab[]{
		0.2f, 0.2f , 0.0f , 1.0f,
		-0.2f , 0.2f , 0.0f , 1.0f,
		-0.2f , -0.2f , 0.0f , 1.0f,
		0.2f, -0.2f, 0.0f, 1.0f
	};

	const unsigned int indx[]{
		0,1,2,
		0,2,3
	};
	quadVAO = Core::initVAOIndexed(tab, indx, 4, 4, 6);
	
	

}

void shutdown(GLFWwindow* window)
{
	shaderLoader.DeleteProgram(program);
}


//obsluga wejscia
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	
	int axesCount;
	const float *axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);
	
	triger = axes[4];
	if (triger == -1) {
		triger = 1;
	}
	else if (triger < 0) {
		triger = 1 + (1 + triger);
	}
	else if(triger == 0){
		triger = 2;
	}
	else {
		triger = 2 + triger;
	}

	transA = transA + 0.001 * axes[0];
	transB = transB - 0.001 * axes[1];
	rotate = rotate - 0.005 * axes[2]*triger;
	

	int buttonCount;
	const unsigned char *buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);
	
	if (GLFW_PRESS == buttons[GLFW_GAMEPAD_BUTTON_A]) {
		if (scale <= 2) {
			scale = scale + 0.005;
		}
	}
	if (GLFW_PRESS == buttons[GLFW_GAMEPAD_BUTTON_B]) {
		if (scale >= 0) {
			scale = scale - 0.005;
		}
	}
	if (GLFW_PRESS == buttons[GLFW_GAMEPAD_BUTTON_Y])
		glfwSetWindowShouldClose(window, true);


}

// funkcja jest glowna petla
void renderLoop(GLFWwindow* window) {
	while (!glfwWindowShouldClose(window))
	{	

		processInput(window);

		renderScene(window);
		glfwPollEvents();
	}
}
//}