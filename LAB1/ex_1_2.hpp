#pragma once
#include "glew.h"
#include <GLFW/glfw3.h>
#include "glm.hpp"

#include "Shader_Loader.h"
#include "Render_Utils.h"

GLuint program; // Shader ID        //! Gdy używasz SHADERA - i rysujesz jakieś trójkąty!
                                    //! Gdy używasz SHADERA - i rysujesz jakieś trójkąty!
GLuint triangleVAO;                 //! Gdy używasz SHADERA - i rysujesz jakieś trójkąty!
GLuint triangle2VAO;                                    //! Gdy używasz SHADERA - i rysujesz jakieś trójkąty!
Core::Shader_Loader shaderLoader;   //! Gdy używasz SHADERA - i rysujesz jakieś trójkąty!


void renderScene(GLFWwindow* window)
{
    glClearColor(1.0f, 0.27f, 0.54f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Aktywowanie shadera !!!!!!!!!! WAŻNE !!!!!!!!!!!!! WAŻNE !!!!!!!!!!!! WAŻNE !!!!!!!!!!
    glUseProgram(program);

    //wywolaj funkcje Core::drawVAO z render utils z parametrem wejściowym GLuint triangleVAO 
    Core::drawVAO(triangleVAO, 3);
    Core::drawVAO(triangle2VAO, 3);
    // Wylaczenie shadera !!!!!!!!!! WAŻNE !!!!!!!!!!!!! WAŻNE !!!!!!!!!!!! WAŻNE !!!!!!!!!!
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

    //stworz tablice wierzcholkow i zaladuj je do GPU za pomoca funkcji initVAO, wynik zapisz w triangleVAO
    const float tab[] = {
        -0.2f , 0.8f , 0.0f , 1.0f,
        0.2f , 0.0f , 0.0f , 1.0f,
        0.8f , 0.0f , 0.0f , 1.0f
    };
    triangleVAO = Core::initVAO(tab, 3, 4);

    const float tab2[] = {
    -0.3f, 0.0f, 0.0f, 1.0f,
    -0.6f , 0.0f, 0.0f, 1.0f,
    -0.45f, -0.6f, 0.0f,1.0f
    };
    triangle2VAO = Core::initVAO(tab2, 3, 4);
    
}

void shutdown(GLFWwindow* window)
{
    shaderLoader.DeleteProgram(program); //GDY COŚ RYSUJESZ! Potem należy to usunąć gdy progrm będzie zmierzał ku końcowi!
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