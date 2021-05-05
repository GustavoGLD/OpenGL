//-----------------------------------------------------------
//  O objetivo aqui é fazermos um  outro Triângulo Colorido,
//  mas com as shaders em arquivos externos:
//  fragmentShaders.fs  ---  vertexShader.vs
//  E o nosso leitor dessas shaders:
//  shader_s.cpp
//-----------------------------------------------------------


//-----------------------
//Incluir bibliotecas
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

//---------------------
//incluir cabeçalhos
#include "shader_s.hpp"

//--------------------------
//Cabeçalho das funções
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

//---------------------
//Dimensões da janela
const unsigned int SCR_WIDTH  = 800;
const unsigned int SCR_HEIGHT = 600;

//------------
int main(){

    //------------------------------------
    //Iniciando e configurando o GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    //-------------------------------------------------------
    //Criando janela, configurando e criando contexto nela
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearningShaders by !Gustavo!", NULL, NULL);
    if (window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //----------------------
    //Inicializando GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //-----------------------------------------------------------
    //Criando e compilando o codigo das Shaders nesses arquivos
    Shader ourShaders("vertexShader.vs", "fragmentShader.fs");

    //---------------------------------------------
    //Array dos Vertices e Cores do nosso triângulo colorido
    float vertices[] = {

         //--------------------------
         //vertice inferior direito
         0.5f, -0.5f,  0.0f, //vertice
         1.0f,  0.0f,  0.0f, //cor vermelha
         
         //--------------------------
         //vertice inferior esquerdo
        -0.5f, -0.5f,  0.0f, //vertice
         0.0f,  1.0f,  0.0f, //cor verde
         
         //--------------------------
         //vertice superior
         0.0f,  0.5f,  0.0f, //vertice
         0.0f,  0.0f,  1.0f  //cor azul
    };

    //--------------------------------
    //Criando e configurando Buffers
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //--------------------------
    //Criando nosso RenderLoop
    while (!glfwWindowShouldClose(window)){
        
        //--------------------
        //Configurando Inputs
        processInput(window);
        
        //---------------------
        //Colocando cor de fundo
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //-----------------------------------------------
        //Desenhando triangulo com nosso programa e VAO
        ourShaders.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        //----------------------------
        //Limpando buffers do GLFW
        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    //---------------------------
    //Encerrando nosso programa
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    return 0;

}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
