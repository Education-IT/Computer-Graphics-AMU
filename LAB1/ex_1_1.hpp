#pragma once
#include "glew.h" 
#include <GLFW/glfw3.h> //importowanie biblioteki okienkowej, specjalnie napisananej dla OpenGL
#include "glm.hpp"

#include "Shader_Loader.h"
#include "Render_Utils.h"
float r = 0.0;
float g = 0.0;
float b = 0.0;  

// funkcja renderujaca scene - za ka�d� p�tl� renderLoop - to nam tworzy to co zobaczymy na ekranie.
void renderScene(GLFWwindow* window)
{
    //if (glfwGetTime() >= 1) {  // glfwGetTime() -> zwraca warto�� float czasu od zainicjalizowania okna lub ustawienia czasu dla okna.
     //   glfwSetTime(0);        // glfwSetTime() -> ustawiamy czas na konkretn� warto�� i od niego liczony jest nast�pnie czas trwania okna.
    //}
    //float color = glfwGetTime();
    // algorytm t�czy wymyslony na bazie wiedzy z: https://www.freestylersupport.com/wiki/tutorial:sequences_ideas:rainbow_tutorial
    if (r < 1 && g <=0  && b <=0 ) {
        r = r + 0.0025;
    }
    else if (r >= 1 && g < 1 && b <= 0) {
        g = g + 0.0025;
    }
    else if (r > 0 && g >= 1 && b <= 0) {
        r = r - 0.0025;
    }
    else if( r <= 0 && g >=1 && b < 1){
        b = b + 0.0025;
    }
    else if (r <= 0 && g > 0  && b >= 1) {
        g = g - 0.0025;
    }
    else if (r < 1 && g <= 0 && b >= 1) {
        r = r + 0.0025;
    }
    else if (r >= 1 && g <= 0 && b > 0) {
        b = b - 0.0025;
    }
    
    // ZADANIE: Przesledz kod i komentarze
    // ZADANIE: Zmien kolor tla sceny, przyjmujac zmiennoprzecinkowy standard RGBA
    glClearColor(r, g, b, 1.0f); // RGBa - zmieniamy kolor t�a - zmiennoprzecnkowe warto�ci od 0 do 1 - jasno�� jakim �wieci dany kolor
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glfwSwapBuffers(window); // Powinno byc wywolane po kazdej klatce - tutaj dokonujemy zamiany bufor�w. - double buffering - by unikn�c migotania.
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void init(GLFWwindow* window) { // Tutaj umieszczamy takie funkcje kt�re wydarz� si� tylko raz! - przy uruchomieniu aplikacji!
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    //powy�sza funkcja - ustawia, �e FB-Size_callback - zostanie wywo�ana przy zmianie rozmaiaru okna - WINDOW* - kt�ra to informuje OpnegGl o zmianie rozmiaru ekranu za pomoc� glViewPort
}

void shutdown(GLFWwindow* window) //Tutaj umieszczamy takie funckje kt�re wydarz� si� tylko raz - przy wy��czeniu aplikacji.
{
}

//obsluga wejscia
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) //sprawdzamy czy wci�ni�to klawisz ESC je�li tak - zazanczamy �e apliakcja powinna zosta� zamkni�ta - a wi�c p�tla si� ko�czy.
        glfwSetWindowShouldClose(window, true);
}

// funkcja jest glown� p�tl� - wykonuje si� dop�ki nie zamkniemy okna. jako argument przyjmuje WINDOW* i wykonuje na nim operacje.
void renderLoop(GLFWwindow* window) { //p�tla renderowania. Sprawdza Input - nast�pnie renderuje scene i jak jakie� wydarzenie mia�o miejsce to na nie reaguje.
    while (!glfwWindowShouldClose(window))
    {
        processInput(window); //przetowrzenie danych wej�cia - obs�uga klawiatura - ESC - (mozliwia r�wnie� obs�uga myszy, joysticka i gamepada)

        renderScene(window); // funckja odpowiedzialna za od�wierzenie sceny - jedna p�tla = jedna klatka.
        glfwPollEvents(); //sprawdza czy s� jakie� eventy do obs�u�enia / zadania do wykonania np>; sprawdza czy rozmiar okna zosta� zmieniony
    }
}
//}