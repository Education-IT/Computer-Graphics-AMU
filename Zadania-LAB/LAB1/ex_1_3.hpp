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

// W tym programie b�dziemy korzysta� z indeksownia
// Poniewa� tworzenie r�nego rodzaju kszta�t�w b�dzie bardzo nieefektywne stosujac same punkty. Poniewa� punkty b�d� si� niejednokrotnie powiela�! REDUNDANCJA DANCYH/PAMI�CI!
// Dlatego te� zdecydowanie lepiej r�wnie� utworzy� specjaln� tablic� ideks�w - pokazuj�c� jakie punkty tworz� jeden tr�jk�t :) mocno to oszcz�dza ilo�� zajmowanego miesjca w pami�ci. Indeksujemy nasze punkty od 0!


void renderScene(GLFWwindow* window)
{
    glClearColor(0.0f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    
    glUseProgram(program); // Aktywowanie shadera
    //wywolaj funkcje drawVAOIndexed na quadVAO 
    Core::drawVAOIndexed(quadVAO, 6);//argumemty(ID VAO , ileWierchDoNarysowania=ilo�� Indeks�w)
    Core::drawVAOIndexed(rombVAO, 6);
    glUseProgram(0); // Wylaczenie shadera

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
        0,1,3, //indeksujemy nasze punkty od zera!
        1,2,3
    };
    quadVAO = Core::initVAOIndexed(tab,indx,4,4,6); //argumenty(tablicaWierzch , tablicaIndeks�w, Ilo��Wierz w 1Tablicy, 4(liczby okre�laj�ce punkt/wierzch) , ilo��Indeks�w w 2Tablicy) UWAGA! - je�li chodzi o ilo�� wierzcho�k�w to jest to zawsze ilo�� dos�ownych wiechrzo�k�w jakie widzi komputer! Czyli Prostok�t - dla komputera dwa tr�jk�ty - kazdy po 3 wierzcho�ki - razem maj� 6 wierzcho�k�w!

    const float rombTab[]{
        0.0f, 0.7f, 0.0f, 1.0f,
        -0.5f, 0.5f , 0.0f, 1.0f,
        0.0f, 0.3f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.0f, 1.0f
    };

    const unsigned int rombIndex[] = { // Kolejno�� punkt�w w tablicy jest r�wnie� istotna!
        0,1,2,    //Dzi�ki tej kolejno�ci OpenGL okre�la orientacj� �cian!
        2,3,0     //Domy�lnie punkty powinny by� zorientowane w kierunku przeciwnym do ruchu wskaz�wek zegara!
    };//indeksujemy nasze punkty od zera!
    rombVAO = Core::initVAOIndexed(rombTab, rombIndex, 4, 4, 6);

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