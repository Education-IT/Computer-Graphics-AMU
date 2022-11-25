#include "glew.h"// OpenGL Extenson Wrangler - ładowanie OPENGL - pozwala na wybranie jakie wersje będziemy obsługiwać i jakie rozszerzenie będą dostępne w programie.
#include <GLFW/glfw3.h> //Graphics Library Framework Wrangler/window - Umozliwia Tworzenie okien i obsługe wejścia uzytkownika. (Może być więcej niż 1 okno) - nie etylko klawiatura i mysz ale też pady i joystick.
#include "glm.hpp" // openGl Mathematics - biblioteka matemtyczna - macierze/wektory

#include "Shader_Loader.h"
#include "Render_Utils.h"
#include "ex_2_1a.hpp"



int main(int argc, char ** argv)
{
    // inicjalizacja glfw -> biblioteki od okien.
    glfwInit();  
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);// Ustawinie wersji OpenGL na 3.3 (pierwszy argument funckji mówi jaką opcję/cechę chcemy skonfigorwać, a drugi to INT który określna daną cechę/opcje
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //uzyskamy dostęp do mniejszej ilości funkcji - bez funkcji wsteczenj kompatybilności których to już nie potrebujemy 
    // jeśli nie będziemy miec (lub uzytkownik) w tym przypadku OpenGL w wersji 3.3 - wtedy powstanie błąd!
    // Powyższe funkcje pozwalaja nam na ustwanienie różnych opcji. Nalezy to zrobic przed utworzeniem okna!
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // tworzenie okna za pomocą glfw - //Argumenty(szerokość,wysokość,nazwaOkna, NaKtórym monitorze ma się pokazać - jak standardowo to NULL) funkcja zwraca wskaźnik na GLFWwindow object
    GLFWwindow* window = glfwCreateWindow(500, 500, "Grafika komputerowa - LAB", NULL, NULL); 
    // zwrócony wskaźnik będzie nam potrzebny, żeby cokolwiek móc w tym oknie zrobić.
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); //Następnie mówimy GLFW, aby kontekst naszego okna był głównym kontekstem bieżącego wątku. Przypisujemy dane oknow do danego wątku!

    // ladowanie OpenGL za pomoca glew
    glewInit();
    glViewport(0, 0, 500, 500); // argumenty - 0,0,szerokość, wysokość. Przekazujemy OpenGl'owi jaki jest rozmiar okna na którym będziemy pracować.

    // Poniższe funckje init() renderLooP() i Shutdown() - są to funckje stworzone przez nas - znajduja się w dalszych zadaniach np.: ex_1_1.hpp

    init(window); 

    // uruchomienie glownej petli
    renderLoop(window);

    shutdown(window);
    glfwTerminate(); //ta funckja niszczy wszystkie okna.
    return 0;
}
