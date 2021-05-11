//-----------------------------
//Esse é o código Principal
//-----------------------------

//------------
//Inclusões
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "shader_s.hpp"
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

//--------------------
//Tamanho da Janela
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


int main()
{   

    //----------------------------------------------
    #pragma region Criando e Configurando a Janela

    //--------------------------------------
    // Inicializando e configurando OpenGL
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    //-------------------------------------------------------------------
    //Criando Janela, tratando erros e criando contexto com a janela
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //-----------------------------------------------------------------
    //Ligando e configurando o GLAD de acordo o Sistema Operacional
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    #pragma endregion

    #pragma region Gerando e Configurando Buffers

    //---------------------------------------------------
    //Ler e compilar Shader; criar programa de Shaders
    Shader ourShader("vertexShader.vs", "fragmentShader.fs");

    //-----------------------------------------------------
    //Informação dos Vértices do Triângulo
    //A posição, cor e coordenada corresponde na textura
    float vertices[] = {
        //Posições           //Cores            //Coordenada da Textura
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
       -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
       -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };

    //------------------------------------------------------------------
    //Um quadrado é formado por 2 Triângulos.
    //Definindo os 2 Triângulos com os vértices declarados anteriormente
    unsigned int indices[] = {  
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    //--------------------------------------
    //Declarando e Gerando VAO, VBO e EBO
    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    //---------------------------
    //Primeiramente, ligar a VAO
    glBindVertexArray(VAO);

    //---------------------------------------------------------------
    //Declando VBO de Arrays; Anexando o array Vértices que criamos
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //-----------------------------------------------------------------
    //Declarando EBO de Arrays; Anexando o array Índices que criamos
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //----------------------------------------------------
    //O Primeiro índice da VAO é referente as Posições
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //----------------------------------------------------
    //O Segundo índice da VAO é referente as Cores
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //--------------------------------------------------------------------------------
    //O Terceiro índice da VAO é referente as Posições correspondetes na Textura
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    #pragma endregion

    //-------------------------------------------
    //Definindo, gerando, e ligando a Textura
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    //------------------------------------
    //Definindo o Wrapping da Textura
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    //-----------------------------------------------------------
    //Definindo o Filtro da Textura (pontual, bilinear, etc)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //-----------------------------------------------------------------------
    //Carregando a Imagem em *data, guardando Informações e tratando erros
    int width, height, nrChannels;
    unsigned char *data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
    if (data) {

        //-------------------------------------------------------------------
        //Gerando a Textura com a Imagem carregada
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

        //-------------------------------------------------------------------
        //Gerando MipMaps 
        glGenerateMipmap(GL_TEXTURE_2D);

    }
    else { std::cout << "Failed to load texture" << std::endl; }

    //-----------------------------------------------------------
    //Apagar o data* com a imagem, depois de criada a textura
    stbi_image_free(data);


    while (!glfwWindowShouldClose(window))
    {
        //-----------------------------------
        //Processando Input
        processInput(window);

        //--------------------------------------------------------------------
        //Configurando a Cor de Fundo
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //-------------------------------------------------------------------
        //Ligando a Textura, ShaderProgram, VAO e rederizando o Retangulo
        glBindTexture(GL_TEXTURE_2D, texture);
        ourShader.use();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        //-------------------------------------------------------------------
        //Lipando buffer do GLFW
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //----------------------------------------------------------------------
    //Deletando VAO, VBO e EBO para fechar o programa (opcional)
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    //----------------------------------------------------------------------
    //Fechando o GLFW e finalizando o programa
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