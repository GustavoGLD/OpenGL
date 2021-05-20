#ifndef MAIN_HPP
#define MAIN_HPP

#include "../Libs/glad/glad.h"
#include "../Libs/glm/glm.hpp"
#include "../Libs/glm/gtc/matrix_transform.hpp"
#include "../Libs/glm/gtc/type_ptr.hpp"
#include <GLFW/glfw3.h>
#include <iostream>

#include "../Classes/Buffers.hpp"
#include "../Classes/Textures.hpp"
#include "../Classes/Render.hpp"

class Main : public Buffers, public Textures, public Render{
private:
    Shader ourShader;

public:
    inline void Start(){
        //---------------------------------------------------
        //Ler e compilar Shader; criar programa de Shaders
        ourShader.newShader("Classes/Shaders/vertexShader.vs", "Classes/Shaders/fragmentShader.fs");

        SettingUpBuffers();
        SettingUpTextures();

    }

    inline void Update(){
        //-------------------------------------------------------------------
        //Ligando a Textura, ShaderProgram, VAO e rederizando o Retangulo
        glBindTexture(GL_TEXTURE_2D, texture);
        glUseProgram(ourShader.ID);
        RenderOurImage(ourShader, VAO,  1,  1);
        RenderOurImage(ourShader, VAO, -1,  1);
        RenderOurImage(ourShader, VAO,  1, -1);
        RenderOurImage(ourShader, VAO, -1, -1);

    }

    inline void Finish(){
        //----------------------------------------------------------------------
        //Deletando VAO, VBO e EBO para fechar o programa (opcional)
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }

};

#endif