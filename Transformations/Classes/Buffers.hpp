#ifndef BUFFERS_H
#define BUFFERS_H

#include "../Libs/glad/glad.h"
#include <GLFW/glfw3.h>
#include "../Libs/stb_image.h"
#include "shader_s.hpp"
#include <iostream>

class Buffers{
public:
    unsigned int VAO, VBO, EBO;

    inline void SettingUpBuffers(){

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

    }
};

#endif