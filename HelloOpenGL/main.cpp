#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

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
    GLFWwindow*  window = glfwCreateWindow(800, 600, "AprendaOpenGL", NULL, NULL);


    //Se a criação da janela deu erro (retornou nulo)
    if (window == NULL){

        //Exibe a mensagem do erro
        std::cout << "Failed to create GLFW window" << std::endl;

        //Finaliza GLFW e o programa
        glfwTerminate();
        return -1;
    }

    //Modificar buffers das dimensões da tela (usar glViewPort)
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //Criar contexto OpenGL na janela em que acabamos de criar
    //Assim o GLAD será inicializado nessa janela
    glfwMakeContextCurrent(window);

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
        
        //Atualizar a verificação de input do GLFW
        glfwPollEvents();
    }

    //Finalizar GLFW e fechar o programa
    glfwTerminate();
    return 0;
}

//Função sobre quando a janela for redimensionada
void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    
    //dois primeiros parâmetros: deslocar tudo que ta dentro da janela
    //dois ultimos parâmetros: distorcer o tamanho de tudo que ta dentro da janela
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
