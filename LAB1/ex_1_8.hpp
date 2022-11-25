#pragma once
#include "glew.h"
#include <GLFW/glfw3.h>
#include "glm.hpp"

#include "ext.hpp"
#include <vector>

#include "Shader_Loader.h"
#include "Render_Utils.h"

GLuint program; // Shader ID

GLuint quadVAO;

Core::Shader_Loader shaderLoader;

float xx, yy = 0.0f;
glm::vec3 quadPos;


void renderScene(GLFWwindow* window)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

    glUseProgram(program);
    
    glm::vec3 quadPos(xx, yy, 0.0f); //wekor okreœlaj¹cy pozycje kwadrata
    glm::mat4 transformation(1.0f);
    glm::mat4 tran = glm::translate(transformation, quadPos);

    glUniformMatrix4fv(glGetUniformLocation(program, "transformation"), 1, GL_FALSE, (float*)&tran);
    Core::drawVAOIndexed(quadVAO, 6);
    
    glUseProgram(0);

    glfwSwapBuffers(window);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) //ca³y czas sprawdza jaka jest pozycja kursora.
{ //ODKOMENTUJ ABY DZIA£A£O POD¥¯ANIE KWADRATA ZA MYSZK¥!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //xx = (2 * float(xpos) / 500) - 1;    // specjalna funckja aby pracowaæ w kostce -1|1 
    //yy = -((2 * float(ypos) / 500) - 1);  
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) //uruchamia siê tylko gdy klikniemy lewy przycisk myszy.
{
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    
    printf("%f,%f\n", xpos, ypos);
    
    //ODKOMENTUJ ¯EBY DZIA£A£O POJAWIANIE SIE KWADRATA W MIEJSCU KLIKNIÊCIA!!!!!!!!!!!!!!!!!!!!!!!!!
  /*
    if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {
        xx = (2*float(xpos)/500)-1; // specjalna funckja aby pracowaæ w kostce -1|1 
        yy = -((2*float(ypos)/500)-1);
    }
  */ 
}


void init(GLFWwindow* window) {
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback); // bêdziemy sprawdzaæ gdzie w danym momencie znajdujê siê kursor myszy.
    glfwSetMouseButtonCallback(window, mouse_button_callback); // bêdziemy obs³ugiwaæ klikniêcia mysz¹
    glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE); // W³¹czamy mo¿liwoœc obs³ugi przycisków myszy
    program = shaderLoader.CreateProgram("shaders/shader_1_2.vert", "shaders/shader_1_2.frag");

    float points[] = {
        -0.1,-0.1,0.0,1.0,
         0.1,-0.1,0.0,1.0,
         0.1, 0.1,0.0,1.0,
        -0.1, 0.1,0.0,1.0,
    };
    unsigned int indices[] = {
        0,1,3,
        1,2,3,
    };

    quadVAO = Core::initVAOIndexed(points, indices, 4, 4, 6);

    //Przekopiuj kod do ladowania z poprzedniego zadania
}

void shutdown(GLFWwindow* window)
{
    shaderLoader.DeleteProgram(program); //!!!!!
}

//obsluga wejscia
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
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