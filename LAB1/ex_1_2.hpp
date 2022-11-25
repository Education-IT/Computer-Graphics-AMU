#pragma once
#include "glew.h"
#include <GLFW/glfw3.h>
#include "glm.hpp"

#include "Shader_Loader.h"
#include "Render_Utils.h"
// GL uinit = opengl UnsignedINT!!!
GLuint program; // Shader ID        //! Gdy używasz SHADERA - i rysujesz jakieś trójkąty!
                                    //! Gdy używasz SHADERA - i rysujesz jakieś trójkąty!
GLuint triangleVAO;       // <----  identyfikator VAO w pamięci karty graficznej          
GLuint triangle2VAO;                //! Gdy używasz SHADERA - i rysujesz jakieś trójkąty!
Core::Shader_Loader shaderLoader;   //! Gdy używasz SHADERA - i rysujesz jakieś trójkąty!


void renderScene(GLFWwindow* window)
{
    glClearColor(1.0f, 0.27f, 0.54f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   
    glUseProgram(program); // Aktywowanie konkretnego shadera !!!!!!!!!! WAŻNE !!!!!!!!!!!!! WAŻNE !!!!!!!!!!!! WAŻNE !!!!!!!!!!
    //wywolaj funkcje Core::drawVAO z render utils z parametrem wejściowym GLuint triangleVAO 
    Core::drawVAO(triangleVAO, 3); //argumenty(uint VAO , LiczbaWierzchołków do narysowania)
    Core::drawVAO(triangle2VAO, 3);
    glUseProgram(0); // Wylaczenie danego shadera !!!!!!!!!! WAŻNE !!!!!!!!!!!!! WAŻNE !!!!!!!!!!!! WAŻNE !!!!!!!!!!

    glfwSwapBuffers(window); //Zamiana buforów - zawsze na końcu funkcji renderScene!
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void init(GLFWwindow* window) {
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    program = shaderLoader.CreateProgram("shaders/shader_1_1.vert", "shaders/shader_1_1.frag"); //podpięcie z jakich SHADERÓW będziemy korzystać! w tym programie.

    //stworz tablice wierzcholkow i zaladuj je do GPU za pomoca funkcji initVAO, wynik zapisz w triangleVAO
    const float tab[] = { //Kolejność punktów w tablicy jest również istotna! Dzięki tej kolejności OpenGL określa orientację ścian! Domyślnie punkty powinny być zorientowane w kierunku przeciwnym do ruchu wskazówek zegara!
        -0.2f , 0.8f , 0.0f , 1.0f,
        0.2f , 0.0f , 0.0f , 1.0f,
        0.8f , 0.0f , 0.0f , 1.0f
    };
    triangleVAO = Core::initVAO(tab, 3, 4); //argumenty(tablicaWierz , liczba wierzch, 4 (ile liczb określa jeden punkt/wierzch)) - funkcja zwraca zmienną typu GLunit która jest identyfikatorem VAO w pamięci karty graficznej. Należy przypisać wynik tej funckji do zmiennej globalnej triangleVAO,

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