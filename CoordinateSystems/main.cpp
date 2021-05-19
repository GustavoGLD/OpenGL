#include "Classes/Window.hpp"
int main(){
    Window window;
    window.CreateWindow();
    window.RenderingLoop();
    window.DestroyWindow();
    return 0;
}