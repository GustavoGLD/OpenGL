#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

//Dimensões da tela
constexpr unsigned int SCR_WIDTH = 800;
constexpr unsigned int SCR_HEIGHT = 600;

//Nome da janela
constexpr const char* WINDOW_TITLE = "HelloOpenGL by !Gustavo!";

int main(){
    //Iniciar GLFW
    glfwInit();

    //Maior e menor versão do OpenGL para criar contextos. Somente OpenGL 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    //Definir perfil como perfil-principal.
    //Ou seja, descartar algumas coisas opcionais como compatibilidade com hardware antigo
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Caso esse programa esteja em um dispositivo Apple
    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    //Criar a Janela
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, WINDOW_TITLE, NULL, NULL);

    //Se a criação da janela deu erro (retornou nulo)
    if (window == NULL){

        //Exibe a mensagem do erro
        std::cout << "Failed to create GLFW window" << std::endl;

        //Finaliza GLFW e o programa
        glfwTerminate();
        return -1;
    }

    //Criar contexto OpenGL na janela em que acabamos de criar
    glfwMakeContextCurrent(window);

    //Modificar buffers das dimensões da tela (usar glViewPort)
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //Carregar o GLAD, seguindo o sistema operacional em que está
    //Se a função retornar FALSE, o GLAD não foi carregado
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){

        //Exigir mensagem com o erro e finalizar programa
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //Enquanto o comando da Janela fecha não foi acionado
    while (!glfwWindowShouldClose(window)){

        //Nossa função de carregar input
        processInput(window);

        //Definir cor de fundo
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        //Limpar tela para a cor de fundo
        glClear(GL_COLOR_BUFFER_BIT);

        //Limpar buffers do GLFW
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //Finalizar GLFW e fechar o programa
    glfwTerminate();
    return 0;
}

//Função sobre as dimensões da tela
void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

//Nossa função de carregar input
void processInput(GLFWwindow* window){

    //Se o botão de fechar for clicado
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){

        //Acionamos o comando que a Janela deve fechar
        glfwSetWindowShouldClose(window, true);
    }
} 