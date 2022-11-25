#pragma once
#include "glew.h" 
#include <GLFW/glfw3.h> //importowanie biblioteki okienkowej, specjalnie napisananej dla OpenGL
#include "glm.hpp"

#include "Shader_Loader.h"
#include "Render_Utils.h"
float r = 0.0;
float g = 0.0;
float b = 0.0;  

// funkcja renderujaca scene - za ka¿d¹ pêtl¹ renderLoop - to nam tworzy to co zobaczymy na ekranie.
void renderScene(GLFWwindow* window)
{
    //if (glfwGetTime() >= 1) {  // glfwGetTime() -> zwraca wartoœæ float czasu od zainicjalizowania okna lub ustawienia czasu dla okna.
     //   glfwSetTime(0);        // glfwSetTime() -> ustawiamy czas na konkretn¹ wartoœæ i od niego liczony jest nastêpnie czas trwania okna.
    //}
    //float color = glfwGetTime();
    // algorytm têczy wymyslony na bazie wiedzy z: https://www.freestylersupport.com/wiki/tutorial:sequences_ideas:rainbow_tutorial
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
    glClearColor(r, g, b, 1.0f); // RGBa - zmieniamy kolor t³a - zmiennoprzecnkowe wartoœci od 0 do 1 - jasnoœæ jakim œwieci dany kolor
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glfwSwapBuffers(window); // Powinno byc wywolane po kazdej klatce - tutaj dokonujemy zamiany buforów. - double buffering - by unikn¹c migotania.
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void init(GLFWwindow* window) { // Tutaj umieszczamy takie funkcje które wydarz¹ siê tylko raz! - przy uruchomieniu aplikacji!
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    //powy¿sza funkcja - ustawia, ¿e FB-Size_callback - zostanie wywo³ana przy zmianie rozmaiaru okna - WINDOW* - która to informuje OpnegGl o zmianie rozmiaru ekranu za pomoc¹ glViewPort
}

void shutdown(GLFWwindow* window) //Tutaj umieszczamy takie funckje które wydarz¹ siê tylko raz - przy wy³¹czeniu aplikacji.
{
}

//obsluga wejscia
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) //sprawdzamy czy wciœniêto klawisz ESC jeœli tak - zazanczamy ¿e apliakcja powinna zostaæ zamkniêta - a wiêc pêtla siê koñczy.
        glfwSetWindowShouldClose(window, true);
}

// funkcja jest glown¹ pêtl¹ - wykonuje siê dopóki nie zamkniemy okna. jako argument przyjmuje WINDOW* i wykonuje na nim operacje.
void renderLoop(GLFWwindow* window) { //pêtla renderowania. Sprawdza Input - nastêpnie renderuje scene i jak jakieœ wydarzenie mia³o miejsce to na nie reaguje.
    while (!glfwWindowShouldClose(window))
    {
        processInput(window); //przetowrzenie danych wejœcia - obs³uga klawiatura - ESC - (mozliwia równie¿ obs³uga myszy, joysticka i gamepada)

        renderScene(window); // funckja odpowiedzialna za odœwierzenie sceny - jedna pêtla = jedna klatka.
        glfwPollEvents(); //sprawdza czy s¹ jakieœ eventy do obs³u¿enia / zadania do wykonania np>; sprawdza czy rozmiar okna zosta³ zmieniony
    }
}
//}