#pragma once
#include "glew.h"
#include <GLFW/glfw3.h>
#include "glm.hpp"

#include "Shader_Loader.h"
#include "Render_Utils.h"

GLuint program; // Shader ID

GLuint quadVAO;
GLuint rombVAO;

Core::Shader_Loader shaderLoader;

// W tym programie bêdziemy korzystaæ z indeksownia
// Poniewa¿ tworzenie ró¿nego rodzaju kszta³tów bêdzie bardzo nieefektywne stosujac same punkty. Poniewa¿ punkty bêd¹ siê niejednokrotnie powielaæ! REDUNDANCJA DANCYH/PAMIÊCI!
// Dlatego te¿ zdecydowanie lepiej równie¿ utworzyæ specjaln¹ tablciê ideksów - pokazuj¹c¹ jakie punkty tworz¹ jeden trójk¹t :) mocno to oszczêdza iloœæ zajmowanego miesjca w pamiêci.


void renderScene(GLFWwindow* window)
{
    glClearColor(0.0f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Aktywowanie shadera
    glUseProgram(program);

    //wywolaj funkcje drawVAOIndexed na quadVAO 
    Core::drawVAOIndexed(quadVAO, 6);
    Core::drawVAOIndexed(rombVAO, 6);
    // Wylaczenie shadera
    glUseProgram(0);

    glfwSwapBuffers(window);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void init(GLFWwindow* window) {
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    program = shaderLoader.CreateProgram("shaders/shader_1_1.vert", "shaders/shader_1_1.frag");

    //Stworz czworokat przy uzyciu 4 wierzcholkow i 6 indeksow (typ: const int []) zaladuj go do za pomoca initVAOIndexed do quadVAO
    const float tab[]{
        0.8f , 0.0f , 0.0f , 1.0f,
        -0.8f , 0.0f , 0.0f , 1.0f,
        -0.8f , -0.8f, 0.0f , 1.0f,
        0.8f , -0.8f, 0.0f, 1.0f
    };

    const unsigned int indx[]{
        0,1,3,
        1,2,3
    };
    quadVAO = Core::initVAOIndexed(tab,indx,6,4,6);

    const float rombTab[]{
        0.0f, 0.7f, 0.0f, 1.0f,
        -0.5f, 0.5f , 0.0f, 1.0f,
        0.0f, 0.3f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.0f, 1.0f
    };

    const unsigned int rombIndex[] = {
        0,1,2,
        2,3,0
    };
    rombVAO = Core::initVAOIndexed(rombTab, rombIndex, 6, 4, 6);

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